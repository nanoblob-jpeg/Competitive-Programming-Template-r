//  yosupo: https://judge.yosupo.jp/submission/304249
//  point get
//  774ms, 52.75Mb
//  n = q = 5e5
//  range get
//  918ms, 52.77Mb
//  n = q = 5e5
//
class segtree{
public:
    array<int, 2> def{1, 0};
    int MMOD = 998244353;
    vector<int> seg;
    vector<array<int, 2>> lazy;
    int boundl, boundr;
    segtree(int length):seg(4*length), lazy(4*length, def){
        boundl = 0, boundr = length-1;
    }
    // bounds are then indexed by offsets to these
    segtree(int lbound, int rbound) : segtree(rbound-lbound+1){
        boundl = lbound, boundr = rbound;
    }
    segtree(vector<int> &val):segtree(val.size()){
        for(int i{}; i < val.size(); ++i)
            add(i, i, val[i]);
    }

    void update(int v, array<int, 2> val, int l, int r, int lq, int rq){
        if(l > r || lq > r || rq < l)
            return;
        else if(lq <= l && r <= rq){
            incr(seg[v], lazy[v], val, l, r);
        }else{
            int mid = l + (r-l)/2;
            push(lazy[v], v, l, mid, r);
            update(v*2, val, l, mid, lq, rq);
            update(v*2+1, val, mid+1, r, lq, rq);
            seg[v] = (seg[v*2] + seg[v*2+1])%MMOD;
        }
    }
    int query(int v, int l, int r, int lq, int rq){
        if(l > r || lq > r || rq < l)
            return 0;
        else if(lq <= l && r <= rq)
            return seg[v];
        else{
            int mid = l + (r-l)/2;
            push(lazy[v], v, l, mid, r);
            return (query(v*2, l, mid, lq, rq) + query(v*2+1, mid+1, r, lq, rq))%MMOD;
        }
    }

    // [l, r], 0 indexed
    void update(int l, int r, array<int, 2> val){
        update(1, val, boundl, boundr, l, r);
    }
    void mult(int l, int r, int val){
        update(1, {val, 0}, boundl, boundr, l, r);
    }
    void add(int l, int r, int val){
        update(1, {1, val}, boundl, boundr, l, r);
    }
    // [l, r], 0 indexed
    int query(int l, int r){
        return query(1, boundl, boundr, l, r);
    }

    // for when we reach a need to lazy update
    inline void incr(int& val, array<int, 2>& lazy, array<int, 2> newVal, int l, int r){
        val *= newVal[0];
        val %= MMOD;
        val += (r-l+1)*newVal[1];
        val %= MMOD;
        lazy[0] *= newVal[0];
        lazy[0] %= MMOD;
        lazy[1] *= newVal[0];
        lazy[1] += newVal[1];
        lazy[1] %= MMOD;
    }
    // for pushing lazy
    inline void push(array<int, 2>& lazy, int v, int l, int mid, int r){
        if(lazy != def){
            update(v*2, lazy, l, mid, l, mid);
            update(v*2+1, lazy, mid+1, r, mid+1, r);
            lazy = def;
            seg[v] = (seg[v*2] + seg[v*2+1])%MMOD;
        }
    }
};
