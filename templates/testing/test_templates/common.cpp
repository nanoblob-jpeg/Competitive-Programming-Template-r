//! test start uf_no_temp_decl
UF uf(n);
//! test end uf_no_temp_decl
//! test start bit_int_pr_decl
bit<int> ds(a);
//! test end bit_int_pr_decl
//! test start seg_pr_decl
segtree<int> ds(a);
//! test end seg_pr_decl
//! test start seg_pr_func_decl
segtree<Func> ds(a);
//! test end seg_pr_func_decl
//! test start seg_pr_freq_decl
segtree<map<int, int>, int, int> ds(n);
//! test end seg_pr_freq_decl