/* This file is automatically generated by tool/opcode.pl.
 * ANY CHANGES WILL BE LOST!
 */
/* forward decl */
XSLATE(noop);
XSLATE(move_sa_to_sb);
XSLATE_w_var(store_to_lvar);
XSLATE_w_var(load_lvar_to_sb);
XSLATE(push);
XSLATE(pop);
XSLATE(pushmark);
XSLATE(nil);
XSLATE_w_sv(literal);
XSLATE_w_int(literal_i);
XSLATE_w_key(fetch_s); /* fetch a field from the top */
XSLATE(fetch_field); /* fetch a field from a variable (bin operator) */
XSLATE_w_key(fetch_field_s); /* fetch a field from a variable (for literal) */
XSLATE(print);
XSLATE_w_sv(print_s);
XSLATE(print_raw);
XSLATE_w_sv(print_raw_s);
XSLATE(include);
XSLATE_w_sv(include_s);
XSLATE_w_var(for_start);
XSLATE_goto(for_next);
XSLATE_w_int(fetch_iter);
XSLATE(add);
XSLATE(sub);
XSLATE(mul);
XSLATE(div);
XSLATE(mod);
XSLATE_w_sv(concat);
XSLATE(filt);
XSLATE_goto(and);
XSLATE_goto(or);
XSLATE_goto(dor);
XSLATE(not);
XSLATE(eq);
XSLATE(ne);
XSLATE(lt);
XSLATE(le);
XSLATE(gt);
XSLATE(ge);
XSLATE_w_key(function);
XSLATE(call);
XSLATE_goto(goto);

enum tx_opcode_t {
    TXOP_noop, /* 0 */
    TXOP_move_sa_to_sb, /* 1 */
    TXOP_store_to_lvar, /* 2 */
    TXOP_load_lvar_to_sb, /* 3 */
    TXOP_push, /* 4 */
    TXOP_pop, /* 5 */
    TXOP_pushmark, /* 6 */
    TXOP_nil, /* 7 */
    TXOP_literal, /* 8 */
    TXOP_literal_i, /* 9 */
    TXOP_fetch_s, /* 10 */
    TXOP_fetch_field, /* 11 */
    TXOP_fetch_field_s, /* 12 */
    TXOP_print, /* 13 */
    TXOP_print_s, /* 14 */
    TXOP_print_raw, /* 15 */
    TXOP_print_raw_s, /* 16 */
    TXOP_include, /* 17 */
    TXOP_include_s, /* 18 */
    TXOP_for_start, /* 19 */
    TXOP_for_next, /* 20 */
    TXOP_fetch_iter, /* 21 */
    TXOP_add, /* 22 */
    TXOP_sub, /* 23 */
    TXOP_mul, /* 24 */
    TXOP_div, /* 25 */
    TXOP_mod, /* 26 */
    TXOP_concat, /* 27 */
    TXOP_filt, /* 28 */
    TXOP_and, /* 29 */
    TXOP_or, /* 30 */
    TXOP_dor, /* 31 */
    TXOP_not, /* 32 */
    TXOP_eq, /* 33 */
    TXOP_ne, /* 34 */
    TXOP_lt, /* 35 */
    TXOP_le, /* 36 */
    TXOP_gt, /* 37 */
    TXOP_ge, /* 38 */
    TXOP_function, /* 39 */
    TXOP_call, /* 40 */
    TXOP_goto, /* 41 */
    TXOP_last
}; /* enum tx_opcode_t */

static const tx_exec_t tx_opcode[] = {
    TXCODE_noop,
    TXCODE_move_sa_to_sb,
    TXCODE_store_to_lvar,
    TXCODE_load_lvar_to_sb,
    TXCODE_push,
    TXCODE_pop,
    TXCODE_pushmark,
    TXCODE_nil,
    TXCODE_literal,
    TXCODE_literal_i,
    TXCODE_fetch_s,
    TXCODE_fetch_field,
    TXCODE_fetch_field_s,
    TXCODE_print,
    TXCODE_print_s,
    TXCODE_print_raw,
    TXCODE_print_raw_s,
    TXCODE_include,
    TXCODE_include_s,
    TXCODE_for_start,
    TXCODE_for_next,
    TXCODE_fetch_iter,
    TXCODE_add,
    TXCODE_sub,
    TXCODE_mul,
    TXCODE_div,
    TXCODE_mod,
    TXCODE_concat,
    TXCODE_filt,
    TXCODE_and,
    TXCODE_or,
    TXCODE_dor,
    TXCODE_not,
    TXCODE_eq,
    TXCODE_ne,
    TXCODE_lt,
    TXCODE_le,
    TXCODE_gt,
    TXCODE_ge,
    TXCODE_function,
    TXCODE_call,
    TXCODE_goto,
    NULL
}; /* tx_opcode[] */

static const U8 tx_oparg[] = {
    0U, /* noop */
    0U, /* move_sa_to_sb */
    TXCODE_W_VAR, /* store_to_lvar */
    TXCODE_W_VAR, /* load_lvar_to_sb */
    0U, /* push */
    0U, /* pop */
    0U, /* pushmark */
    0U, /* nil */
    TXCODE_W_SV, /* literal */
    TXCODE_W_INT, /* literal_i */
    TXCODE_W_KEY, /* fetch_s */
    0U, /* fetch_field */
    TXCODE_W_KEY, /* fetch_field_s */
    0U, /* print */
    TXCODE_W_SV, /* print_s */
    0U, /* print_raw */
    TXCODE_W_SV, /* print_raw_s */
    0U, /* include */
    TXCODE_W_SV, /* include_s */
    TXCODE_W_VAR, /* for_start */
    TXCODE_GOTO, /* for_next */
    TXCODE_W_INT, /* fetch_iter */
    0U, /* add */
    0U, /* sub */
    0U, /* mul */
    0U, /* div */
    0U, /* mod */
    TXCODE_W_SV, /* concat */
    0U, /* filt */
    TXCODE_GOTO, /* and */
    TXCODE_GOTO, /* or */
    TXCODE_GOTO, /* dor */
    0U, /* not */
    0U, /* eq */
    0U, /* ne */
    0U, /* lt */
    0U, /* le */
    0U, /* gt */
    0U, /* ge */
    TXCODE_W_KEY, /* function */
    0U, /* call */
    TXCODE_GOTO, /* goto */
}; /* tx_oparg[] */

static void
tx_init_ops(pTHX_ HV* const ops) {
    (void)hv_stores(ops, STRINGIFY(noop), newSViv(TXOP_noop));
    (void)hv_stores(ops, STRINGIFY(move_sa_to_sb), newSViv(TXOP_move_sa_to_sb));
    (void)hv_stores(ops, STRINGIFY(store_to_lvar), newSViv(TXOP_store_to_lvar));
    (void)hv_stores(ops, STRINGIFY(load_lvar_to_sb), newSViv(TXOP_load_lvar_to_sb));
    (void)hv_stores(ops, STRINGIFY(push), newSViv(TXOP_push));
    (void)hv_stores(ops, STRINGIFY(pop), newSViv(TXOP_pop));
    (void)hv_stores(ops, STRINGIFY(pushmark), newSViv(TXOP_pushmark));
    (void)hv_stores(ops, STRINGIFY(nil), newSViv(TXOP_nil));
    (void)hv_stores(ops, STRINGIFY(literal), newSViv(TXOP_literal));
    (void)hv_stores(ops, STRINGIFY(literal_i), newSViv(TXOP_literal_i));
    (void)hv_stores(ops, STRINGIFY(fetch_s), newSViv(TXOP_fetch_s));
    (void)hv_stores(ops, STRINGIFY(fetch_field), newSViv(TXOP_fetch_field));
    (void)hv_stores(ops, STRINGIFY(fetch_field_s), newSViv(TXOP_fetch_field_s));
    (void)hv_stores(ops, STRINGIFY(print), newSViv(TXOP_print));
    (void)hv_stores(ops, STRINGIFY(print_s), newSViv(TXOP_print_s));
    (void)hv_stores(ops, STRINGIFY(print_raw), newSViv(TXOP_print_raw));
    (void)hv_stores(ops, STRINGIFY(print_raw_s), newSViv(TXOP_print_raw_s));
    (void)hv_stores(ops, STRINGIFY(include), newSViv(TXOP_include));
    (void)hv_stores(ops, STRINGIFY(include_s), newSViv(TXOP_include_s));
    (void)hv_stores(ops, STRINGIFY(for_start), newSViv(TXOP_for_start));
    (void)hv_stores(ops, STRINGIFY(for_next), newSViv(TXOP_for_next));
    (void)hv_stores(ops, STRINGIFY(fetch_iter), newSViv(TXOP_fetch_iter));
    (void)hv_stores(ops, STRINGIFY(add), newSViv(TXOP_add));
    (void)hv_stores(ops, STRINGIFY(sub), newSViv(TXOP_sub));
    (void)hv_stores(ops, STRINGIFY(mul), newSViv(TXOP_mul));
    (void)hv_stores(ops, STRINGIFY(div), newSViv(TXOP_div));
    (void)hv_stores(ops, STRINGIFY(mod), newSViv(TXOP_mod));
    (void)hv_stores(ops, STRINGIFY(concat), newSViv(TXOP_concat));
    (void)hv_stores(ops, STRINGIFY(filt), newSViv(TXOP_filt));
    (void)hv_stores(ops, STRINGIFY(and), newSViv(TXOP_and));
    (void)hv_stores(ops, STRINGIFY(or), newSViv(TXOP_or));
    (void)hv_stores(ops, STRINGIFY(dor), newSViv(TXOP_dor));
    (void)hv_stores(ops, STRINGIFY(not), newSViv(TXOP_not));
    (void)hv_stores(ops, STRINGIFY(eq), newSViv(TXOP_eq));
    (void)hv_stores(ops, STRINGIFY(ne), newSViv(TXOP_ne));
    (void)hv_stores(ops, STRINGIFY(lt), newSViv(TXOP_lt));
    (void)hv_stores(ops, STRINGIFY(le), newSViv(TXOP_le));
    (void)hv_stores(ops, STRINGIFY(gt), newSViv(TXOP_gt));
    (void)hv_stores(ops, STRINGIFY(ge), newSViv(TXOP_ge));
    (void)hv_stores(ops, STRINGIFY(function), newSViv(TXOP_function));
    (void)hv_stores(ops, STRINGIFY(call), newSViv(TXOP_call));
    (void)hv_stores(ops, STRINGIFY(goto), newSViv(TXOP_goto));
} /* tx_register_ops() */
