//  yosupo: https://judge.yosupo.jp/submission/309930
//  154ms, 16.28Mb
//  n = q = 5e5
//! stats end
// forward decl
template <typename T, typename L, typename R>
struct SegOp;

//! test start ds
template <typename T, typename L = T, typename R = T, template <typename, typename, typename> class Comb = SegOp>
class segtree{
public:
    using Op = Comb<T, L, R>;
    vector<T> seg;
    int len, boundl, ol;
    segtree(int length, int lbound = 0):ol(length), boundl(lbound){
        len = 1;
        while(len < length) len *= 2;
        seg = vector<T>(len*2, Op::identity);
    }
    segtree(vector<T> &val) : segtree(val.size()){
        for(int i{}; i < val.size(); ++i)
            update(i, val[i]);
    }

    void update(int v, L val){
        if(v < boundl || v >= boundl+ol)
            assert(false);
        v += len - boundl;
        seg[v] = Op::leafCombine(seg[v], val);
        for(v>>=1; v; v >>= 1){
            seg[v] = Op::updateCombine(seg[v<<1], seg[v<<1 | 1]);
        }
    }

    // [l, r], 0 indexed
    R query(int l, int r){
        if(l < boundl || r >= boundl+ol)
            assert(false);
        R lret = Op::returnIdentity, rret = Op::returnIdentity;
        l += len-boundl;
        r += len-boundl+1;
        while(l < r){
            if(l&1) lret = Op::queryCombine(lret, Op::getVal(seg[l++]));
            if(r&1) rret = Op::queryCombine(Op::getVal(seg[--r]), rret);
            l >>= 1;
            r >>= 1;
        }
        return Op::queryCombine(lret, rret);
    }
};
//! test end ds

template <typename T, typename L, typename R>
struct SegOp{
    static constexpr T identity = -1e9;
    static constexpr R returnIdentity = -1e9;
    static T updateCombine(const T& a, const T& b){
        return max(a, b);
    }
    static T leafCombine(const T& a, const L& b){
        return max(a, b);
    }
    static R queryCombine(const R& a, const R& b){
        return max(a, b);
    }
    static R getVal(const T& val){
        return val;
    }
};
