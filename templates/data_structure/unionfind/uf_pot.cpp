//  yosupo: https://judge.yosupo.jp/submission/306032
//  57ms, 13.41Mb
//  n = q = 2e5
//
template<typename T, int UMOD = 998244353>
class UF{
public:
    vector<int> uf, sizes, depth;
    vector<T> wf;
    vector<vector<int>> adj;
    T wdef = 0;
    UF(int n):uf(n), wf(n, wdef), sizes(n, 1), adj(n), depth(n){
        iota(uf.begin(), uf.end(), 0);
    }

    // recalculate depth
    void calc(int v, int p){
        depth[v] = depth[p]+1;
        for(auto& a : adj[v])
            calc(a, v);
    }

    // adding edge u -> v with weight w such that u+w = v
    int merge(int u, int v, int w){
        pair<int, T> x = find(u);
        pair<int, T> y = find(v);
        if(x.first != y.first){
            T amt = connect(x.second, w, y.second);
            if(sizes[x.first] > sizes[y.first]){
                swap(x, y);
                amt = inv(amt);
            }
            wf[x.first] = amt;
            adj[y.first].push_back(x.first);
            calc(x.first, y.first);

            sizes[y.first] += sizes[x.first];
            uf[x.first] = y.first;
            return 1;
        }else{
            // test for inconsistency
            if(path(u, v) != w)
                return -1;
        }
        return 0;
    }

    // inverse
    inline T inv(T a){
        return ((-a)%UMOD+UMOD)%UMOD;
    }

    inline T comb(T a, T b){
        // this is for joining two weights end to end
        return (a+b)%UMOD;
    }

    inline T connect(T a, T b, T c){
        // this is for connecting between two trees
        // a = [x...y], c = [z...w], b = [x..yz..w]
        //
        return comb(comb(b, inv(a)), c);
    }

    // log(n) finding
    pair<int, T> find(int v){
        if(uf[v] == v){
            return {v, wdef};
        }
        pair<int, T> ret = find(uf[v]);
        return {ret.first, comb(wf[v], ret.second)};
    }

    T path(int u, int v){
        int wu = wdef, wv = wdef;
        while(depth[u] > depth[v]){
            wu = comb(wu, wf[u]);
            u = uf[u];
        }
        while(depth[v] > depth[u]){
            wv = comb(wv, wf[v]);
            v = uf[v];
        }
        while(u != v && uf[u] != u){
            wu = comb(wu, wf[u]);
            u = uf[u];
            wv = comb(wv, wf[v]);
            v = uf[v];
        }
        if(u == v)
            return comb(wu, inv(wv));
        else
            return -1;
    }
};
