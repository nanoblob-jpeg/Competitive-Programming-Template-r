//! test start 3t_pre_decl
template <typename T, typename L, typename R>
struct SegOp;
//! test end 3t_pre_decl
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