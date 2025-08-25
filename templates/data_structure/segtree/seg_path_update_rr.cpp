template <typename T, typename L, typename R>
struct SegOp;

template <typename T, typename L = T, typename R = T, template <typename, typename, typename> class Comb = SegOp>
class segtree{
public:
    using Op = Comb<T, L, R>;
    vector<T> seg;
    vector<L> lazy;
    int boundl, boundr;
    segtree(int length): seg(4*length, Op::identity), lazy(4*length, Op::lazyIdentity){
        boundl = 0, boundr = length-1;
    }
    // bounds are then indexed by offsets to these
    segtree(int lbound, int rbound) : segtree(rbound-lbound+1){
        boundl = lbound, boundr = rbound;
    }
    segtree(vector<T> &val) : segtree(val.size()){
        build(1, boundl, boundr, val);
    }
    void build(int v, int l, int r, vector<T> &val){
        if(l > r)
            return;
        if(l == r){
            seg[v] = val[l];
            return;
        }
        int mid = l + (r-l)/2;
        build(v*2, l, mid, val);
        build(v*2+1, mid+1, r, val);
        Op::combine(seg[v], seg[v*2], seg[v*2+1]);
    }

    void update(int v, L val, int l, int r, int lq, int rq){
        if(l > r || lq > r || rq < l)
            return;
        else if(lq <= l && r <= rq){
            Op::lazy(seg[v], lazy[v], val, l, r);
        }else{
            int mid = l + (r-l)/2;
            push(lazy[v], v, l, mid, r);
            update(v*2, val, l, mid, lq, rq);
            update(v*2+1, val, mid+1, r, lq, rq);
            Op::combine(seg[v], seg[v*2], seg[v*2+1]);
        }
    }
    R query(int v, int l, int r, int lq, int rq){
        if(l > r || lq > r || rq < l)
            return Op::returnIdentity;
        else if(lq <= l && r <= rq)
            return Op::getVal(seg[v]);
        else{
            int mid = l + (r-l)/2;
            push(lazy[v], v, l, mid, r);
            return Op::combineQuery(query(v*2, l, mid, lq, rq), query(v*2+1, mid+1, r, lq, rq));
        }
    }

    inline void push(L& lazy, int v, int l, int mid, int r){
        if(lazy != Op::lazyIdentity){
            update(v*2, lazy, l, mid, l, mid);
            update(v*2+1, lazy, mid+1, r, mid+1, r);
            lazy = Op::lazyIdentity;
            Op::combine(seg[v], seg[v*2], seg[v*2+1]);
        }
    }

    // [l, r], 0 indexed
    void update(int l, int r, L val){
        update(1, val, boundl, boundr, l, r);
    }
    // [l, r], 0 indexed
    T query(int l, int r){
        return query(1, boundl, boundr, l, r);
    }
};

// T = stored data type
// L = lazy value data type
// R = query return value data type
template <typename T, typename L, typename R>
struct SegOp{
    static constexpr T identity = 0;
    static constexpr L lazyIdentity = 0;
    static constexpr R returnIdentity = 0;
    // combining any two stored values
    static void combine(T& a, T& left, T& right){
        a = left+right;
    }
    // combining any two return values
    static R combineQuery(R&& f, R&& s){
        return f+s;
    }
    // for when we reach a need to lazy update
    // leaf updates use this with l == r
    // values should update lazy as well (probably)
    static void lazy(T& val, L& lazy, L& newVal, int l, int r){
        val += (r-l+1)*newVal;
        lazy += newVal;
    }
    // for when we query and need to get value out of a node
    static R getVal(T& val){
        return val;
    }
};