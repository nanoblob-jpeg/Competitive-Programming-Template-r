template <typename T>
class segtree{
public:
    vector<T> seg, lazy;
    int boundl, boundr;
    segtree(int length): seg(4*length), lazy(4*length, def){
        boundl = 0, boundr = length-1;
    }
    // bounds are then indexed by offsets to these
    segtree(int lbound, int rbound) : seg(4*(rbound-lbound+1)), lazy(4*(rbound-lbound+1), def){
        boundl = lbound, boundr = rbound;
    }
    segtree(vector<T> &val){
        seg = vector<T>(4*val.size());
        lazy = vector<T>(4*val.size(), def);
        boundl = 0, boundr = val.size()-1;
        for(int i{}; i < val.size(); ++i)
            update(i, i, val[i]);
    }

    void update(int v, int val, int l, int r, int lq, int rq){
        if(l > r || lq > r || rq < l)
            return;
        else if(lq <= l && r <= rq){
            incr(seg[v], lazy[v], val, l, r);
        }else{
            int mid = l + (r-l)/2;
            push(lazy[v], v, l, mid, r);
            update(v*2, val, l, mid, lq, rq);
            update(v*2+1, val, mid+1, r, lq, rq);
            seg[v] = comb(seg[v*2], seg[v*2+1]);
        }
    }
    T query(int v, int l, int r, int lq, int rq){
        if(l > r || lq > r || rq < l)
            return def;
        else if(lq <= l && r <= rq)
            return seg[v];
        else{
            int mid = l + (r-l)/2;
            push(lazy[v], v, l, mid, r);
            return comb(query(v*2, l, mid, lq, rq), query(v*2+1, mid+1, r, lq, rq));
        }
    }

    // [l, r], 0 indexed
    void update(int l, int r, int val){
        update(1, val, boundl, boundr, l, r);
    }
    // [l, r], 0 indexed
    T query(int l, int r){
        return query(1, boundl, boundr, l, r);
    }

    T def{};
    // combining any two values
    inline T comb(T f, T s){
        return f+s;
    }
    // for when we reach a need to lazy update
    inline void incr(T& val, T& lazy, T newVal, int l, int r){
        val += (r-l+1)*newVal;
        lazy += newVal;
    }
    // for pushing lazy
    inline void push(T& lazy, int v, int l, int mid, int r){
        if(lazy != def){
            update(v*2, lazy, l, mid, l, mid);
            update(v*2+1, lazy, mid+1, r, mid+1, r);
            lazy = def;
            seg[v] = comb(seg[v*2], seg[v*2+1]);
        }
    }
};
