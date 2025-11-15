//! test start 3t_pre_decl
template <typename T, typename L, typename R>
struct SegOp;
//! test end 3t_pre_decl
//! test start 1t_pre_decl
template <typename T>
struct SegOp;
//! test end 1t_pre_decl
//! test start 3t_sum_op_leaf
template <typename T, typename L, typename R>
struct SegOp{
    static constexpr T identity = 0;
    static constexpr R returnIdentity = 0;
    static T updateCombine(const T& a, const T& b){
        return a+b;
    }
    static T leafCombine(const T& a, const L& b){
        return a+b;
    }
    static R queryCombine(const R& a, const R& b){
        return a+b;
    }
    static R getVal(const T& val){
        return val;
    }
};
//! test end 3t_sum_op_leaf
//! test start 3t_func_op_leaf
template <typename T, typename L, typename R>
struct SegOp{
    static T identity;
    static R returnIdentity;
    static T updateCombine(const T& a, const T& c){
        int m = (a.m * c.m)%MOD;
        int b = ((a.b * c.m)%MOD + c.b)%MOD;
        return T(m, b);
    }
    static T leafCombine(const T& a, const L& b){
        return b;
    }
    static R queryCombine(const R& a, const R& c){
        int m = (a.m * c.m)%MOD;
        int b = ((a.b * c.m)%MOD + c.b)%MOD;
        return T(m, b);
    }
    static R getVal(const T& val){
        return val;
    }
};
template<>
Func SegOp<Func, Func, Func>::identity = Func();
template<>
Func SegOp<Func, Func, Func>::returnIdentity = Func();
//! test end 3t_func_op_leaf
//! test start 1t_func_op_leaf
template <typename T>
struct SegOp{
    static T identity;
    static T combine(const T& a, const T& c){
        int m = (a.m * c.m)%MOD;
        int b = ((a.b * c.m)%MOD + c.b)%MOD;
        return T(m, b);
    }
    static T leafCombine(const T& a, const T& b){
        return b;
    }
};
template<>
Func SegOp<Func>::identity = Func();
//! test end 1t_func_op_leaf
//! test start 3t_path_freq_pr_leaf
int added = -1;
int removed = -1;
template <typename T, typename L, typename R>
struct SegOp{
    static T identity;
    static constexpr R returnIdentity = 0;
    static void updateCombine(T& a, const T& left, const T& right, const L& val){
        if(removed != -1)
            a[removed]--;
        if(added != -1)
            a[added]++;
    }
    static void leafCombine(T& a, const L& b){
        if(a.size()){
            removed = (*a.begin()).first;
            a.clear();
        }
        a[b]++;
        added = b;
    }
    static R queryCombine(const R& a, const R& b){
        return a+b;
    }
    static R getVal(T& val, int q){
        if(val.count(q))
            return val[q];
        return 0;
    }
};

template<>
map<int, int> SegOp<map<int, int>, int, int>::identity = map<int, int>();
//! test end 3t_path_freq_pr_leaf