//  yosupo: https://judge.yosupo.jp/submission/309938
//  4373ms, 439.97Mb
//  n = q = 2e5
//
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
        Op::leafCombine(seg[v], val);
        for(v>>=1; v; v >>= 1){
            Op::updateCombine(seg[v], seg[v<<1], seg[(v<<1)|1], val);
        }
    }

    // [l, r], 0 indexed
    R query(int l, int r, int q){
        if(l < boundl || r >= boundl+ol)
            assert(false);
        R lret = Op::returnIdentity, rret = Op::returnIdentity;
        l += len-boundl;
        r += len-boundl+1;
        while(l < r){
            if(l&1) lret = Op::queryCombine(lret, Op::getVal(seg[l++], q));
            if(r&1) rret = Op::queryCombine(Op::getVal(seg[--r], q), rret);
            l >>= 1;
            r >>= 1;
        }
        return Op::queryCombine(lret, rret);
    }
};

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
//! test end ds