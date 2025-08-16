//  yosupo: https://judge.yosupo.jp/submission/307857
//  344ms, 26.74Mb
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

    void update(int v, T val){
        if(v < boundl || v >= boundl+ol)
            assert(false);
        v += len - boundl;
        seg[v] = Op::leafCombine(seg[v], val);
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
const int MOD = 998244353;
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
struct Func{
    int m, b;
    Func(int x = 1, int y = 0):m(x),b(y){}
};
// defining Func identity = value, hence
// the Func before SegOp
template<>
Func SegOp<Func>::identity = Func();