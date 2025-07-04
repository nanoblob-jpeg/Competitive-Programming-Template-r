template <typename T>
class segtree{
public:
    vector<T> seg;
    int len, boundl, ol;
    segtree(int length, int lbound = 0):ol(length), boundl(lbound){
        len = 1;
        while(len < length) len *= 2;
        seg = vector<T>(len*2, def);
    }
    segtree(vector<T> &val) : segtree(val.size()){
        for(int i{}; i < val.size(); ++i)
            update(i, val[i]);
    }

    void update(int v, int val){
        if(v < boundl || v >= boundl+ol)
            assert(false);
        v += len - boundl;
        seg[v] = comb(seg[v], val);
        for(v>>=1; v; v >>= 1){
            seg[v] = comb(seg[v<<1], seg[v<<1 | 1]);
        }
    }

    // [l, r], 0 indexed
    T query(int l, int r){
        T lret = def, rret = def;
        l += len-boundl;
        r += len-boundl+1;
        while(l < r){
            if(l&1) lret = comb(lret, seg[l++]);
            if(r&1) rret = comb(seg[--r], rret);
            l >>= 1;
            r >>= 1;
        }
        return comb(lret, rret);
    }

    T def{-1000000000};
    // combining any two values
    inline T comb(T f, T s){
        return max(f, s);
    }
};
