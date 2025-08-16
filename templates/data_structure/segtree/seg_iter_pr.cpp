//  yosupo: https://judge.yosupo.jp/submission/307853
//  158ms, 16.23Mb
//  n = q = 5e5
//
// forward decl
template <typename T>
struct SegOp;

template <typename T, template <typename> class Comb = SegOp>
class segtree{
public:
    using Op = Comb<T>;
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

    void update(int v, int val){
        if(v < boundl || v >= boundl+ol)
            assert(false);
        v += len - boundl;
        seg[v] = Op::combine(seg[v], val);
        for(v>>=1; v; v >>= 1){
            seg[v] = Op::combine(seg[v<<1], seg[v<<1 | 1]);
        }
    }

    // [l, r], 0 indexed
    T query(int l, int r){
        T lret = Op::identity, rret = Op::identity;
        l += len-boundl;
        r += len-boundl+1;
        while(l < r){
            if(l&1) lret = Op::combine(lret, seg[l++]);
            if(r&1) rret = Op::combine(seg[--r], rret);
            l >>= 1;
            r >>= 1;
        }
        return Op::combine(lret, rret);
    }
};

template <typename T>
struct SegOp{
    static constexpr T identity = -1e9;
    static T combine(const T& a, const T& b){
        return max(a, b);
    }
};
