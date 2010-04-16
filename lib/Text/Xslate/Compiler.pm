package Text::Xslate::Compiler;
use 5.010;
use Mouse;
use warnings FATAL => 'all';

use Text::Xslate;

use constant _DUMP_CODE => !!$ENV{XSLATE_DUMP_CODE};

extends qw(Text::Xslate::Parser);

sub compile_str {
    my($self, $str) = @_;

    return Text::Xslate->new( $self->_compile_str($str) );
}

sub _compile_str {
    my($self, $str) = @_;

    my $ast = $self->parse($str);

    my @code = $self->_compile_ast($ast);

    $self->_optimize(\@code);

    print $self->_dump(\@code) if _DUMP_CODE;
    return \@code;
}

sub _compile_ast {
    my($self, $ast) = @_;
    my @code;

    return unless defined $ast;

    confess("Not an ARRAY reference: $ast") if ref($ast) ne 'ARRAY';
    foreach my $node(@{$ast}) {
        my $generator = $self->can('_generate_' . $node->arity)
            || Carp::croak("Cannot generate codes for " . $node->dump);

        push @code, $self->$generator($node);
    }

    return @code;
}

sub _generate_command {
    my($self, $node) = @_;

    my @code;

    my $proc = $node->id;
    foreach my $arg(@{ $node->args }){
        if($arg->arity eq 'literal'){
            my $value = $self->_literal_to_value($arg);
            push @code, [ $proc . '_s' => $value ];
        }
        else {
            push @code,
                $self->_generate_expr($arg),
                [ $proc => () ];
        }
    }
    return @code;
}

sub _generate_for {
    my($self, $node) = @_;
    my $expr     = $node->first;
    my $iter_var = $node->second;
    my $block    = $node->third;

    my @code;

    push @code, $self->_generate_expr($expr);

    my $for_start = scalar @code;
    push @code, [ for_start => $iter_var->scope_depth - 1, $iter_var->id ];

    push @code, $self->_compile_ast($block);

    push @code,
        [ literal  => $iter_var->scope_depth - 1, $iter_var->id ],
        [ for_next => -(scalar(@code) - $for_start) ];
    return @code;
}


sub _generate_if {
    my($self, $node) = @_;

    my @expr  = $self->_generate_expr($node->first);
    my @then  = $self->_compile_ast($node->second);

    my $other = $node->third;
    my @else = blessed($other)
        ? $self->_generate_if($other)
        : $self->_compile_ast($other);

    my @code = (
        @expr,
        [ and    => scalar(@then) + 2, 'if' ],
        @then,
        [ pc_inc => scalar(@else) + 1 ],
        @else,
    );
    return @code;
}

sub _generate_expr {
    my($self, $node) = @_;
    my @ast = ($node);

    return $self->_compile_ast(\@ast);
}

sub _generate_variable {
    my($self, $node) = @_;

    if(defined(my $id = $node->scope_depth)) {
        return [ fetch_iter => $id - 1, $node->id ];
    }
    else {
        return [ fetch => $self->_variable_to_value($node) ];
    }
}

sub _generate_literal {
    my($self, $node) = @_;

    return [ literal => $self->_literal_to_value($node) ];
}

sub _generate_unary {
    my($self, $node) = @_;

    given($node->id) {
        when('!') {
            return
                $self->_generate_expr($node->first),
                [ not => () ];
        }
        default {
            Carp::croak("Unary operator $_ is not yet implemented");
        }
    }
}

my %bin = (
    '==' => 'eq',
    '!=' => 'ne',
    '<'  => 'lt',
    '<=' => 'le',
    '>'  => 'gt',
    '>=' => 'ge',

    '+'  => 'add',
    '-'  => 'sub',
    '*'  => 'mul',
    '/'  => 'div',
    '%'  => 'mod',
);
my %bin_r = (
    '&&' => 'and',
    '||' => 'or',
);
sub _generate_binary {
    my($self, $node) = @_;

    given($node->id) {
        when('.') {
            return
                $self->_generate_expr($node->first),
                [ fetch_field => $node->second->id ],
        }
        when(%bin) {
            return
                $self->_generate_expr($node->first),
                [ push      => () ],
                $self->_generate_expr($node->second),
                [ pop_to_sb => () ],
                [ $bin{$_}  => () ];
        }
        when(%bin_r) {
            my @right = $self->_generate_expr($node->second);
            return
                $self->_generate_expr($node->first),
                [ $bin_r{$_} => scalar(@right) + 1 ],
                @right;
        }
        default {
            Carp::croak("Binary operator $_ is not yet implemented");
        }
    }
    return;
}

sub _generate_ternary { # the conditional operator
    my($self, $node) = @_;

    my @expr = $self->_generate_expr($node->first);
    my @then = $self->_generate_expr($node->second);

    my @else = $self->_generate_expr($node->third);

    my @code = (
        @expr,
        [ and    => scalar(@then) + 2, 'ternary' ],
        @then,
        [ pc_inc => scalar(@else) + 1 ],
        @else,
    );
    return @code;
}

sub _variable_to_value {
    my($self, $arg) = @_;

    my $name = $arg->value;
    $name =~ s/\$//;
    return $name;
}


sub _literal_to_value {
    my($self, $arg) = @_;

    my $value = $arg->value // return undef;

    if($value =~ s/"(.+)"/$1/){
        $value =~ s/\\n/\n/g;
        $value =~ s/\\t/\t/g;
        $value =~ s/\\(.)/$1/g;
    }
    elsif($value =~ s/'(.+)'/$1/) {
        $value =~ s/\\(['\\])/$1/g; # ' for poor editors
    }
    return $value;
}

sub _optimize {
    my($self, $code_ref) = @_;

    for(my $i = 0; $i < @{$code_ref}; $i++) {
        if($code_ref->[$i][0] eq 'print_raw_s') {
            # merge a list of print_raw_s into single command
            for(my $j = $i + 1;
                $j < @{$code_ref} && $code_ref->[$j][0] eq 'print_raw_s';
                $j++) {
                my($op) = splice @{$code_ref}, $j, 1;
                $code_ref->[$i][1] .= $op->[1];
            }
        }
    }
    return;
}


sub _dump { # as xslate assembly
    my($self, $code_ref) = @_;

    my $as = '';
    $as .= "# xslate opcode version $Text::Xslate::VERSION\n";
    foreach my $op(@{$code_ref}) {
        my($opname, $arg, $comment) = @{$op};
        $as .= $opname;
        if(defined $arg) {
            $as .= " ";

            if(Scalar::Util::looks_like_number($arg)){
                $as .= $arg;
            }
            else {
                $arg =~ s/\n/\\n/g;
                $arg =~ s/\\/\\\\/;
                $as .= qq{"$arg"};
            }
        }
        if(defined $comment) {
            $as .= " # $comment";
        }
        $as .= "\n";
    }
    return $as;
}

no Mouse;
__PACKAGE__->meta->make_immutable;