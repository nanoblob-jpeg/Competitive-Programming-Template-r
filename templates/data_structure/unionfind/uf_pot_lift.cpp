//  yosupo: https://judge.yosupo.jp/submission/304943
//  liftAmt = 20: 137ms, 75.41Mb
//  liftAmt = 5: 78ms, 29.60Mb
//  n = q = 2e5
//
template<typename T, int liftAmt = 20>
class UF{
public:
    vector<int> uf, sizes, depth;
    vector<array<int, liftAmt>> lift;
    vector<array<T, liftAmt>> wf;
    vector<vector<pair<int, T>>> adj;
    int UMOD = 998244353;
    T wdef = 0;
    UF(int n):uf(n), wf(n), sizes(n, 1), lift(n), adj(n), depth(n){
        iota(uf.begin(), uf.end(), 0);
        for(int i{}; i < n; ++i)
            for(int j{}; j < liftAmt; ++j){
                lift[i][j] = i;
                wf[i][j] = wdef;
            }
    }

    // recalculate lift
    void calc(int v, int p, int c){
        lift[v][0] = p;
        wf[v][0] = c;
        depth[v] = depth[p]+1;
        for(int i{1}; i < liftAmt; ++i){
            lift[v][i] = lift[lift[v][i-1]][i-1];
            wf[v][i] = comb(wf[v][i-1], wf[lift[v][i-1]][i-1]);
        }
        for(auto& [a, b] : adj[v])
            calc(a, v, b);
    }

    // adding edge u -> v with weight w such that u+w = v
    int merge(int u, int v, int w){
        pair<int, T> x = findw(u);
        pair<int, T> y = findw(v);
        if(x.first != y.first){
            T amt = connect(x.second, w, y.second);
            if(sizes[x.first] > sizes[y.first]){
                swap(x, y);
                amt = inv(amt);
            }
            adj[y.first].push_back({x.first, amt});
            calc(x.first, y.first, amt);

            sizes[y.first] += sizes[x.first];
            uf[x.first] = y.first;
            return 1;
        }else{
            // test for inconsistency
            if(getpath(u, v) != w)
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
        // a = [x...y], c = [w...z], b = [x..yz..w]
        //
        return comb(comb(b, inv(a)), c);
    }

    // log(log(n)) finding
    pair<int, T> findw(int v){
        T ret = goup(v, depth[v], true);
        return {v, ret};
    }

    inline T goup(int &v, int p, bool left){
        int c{};
        T ret{};
        while(p){
            if(p&1){
                if(left)
                    ret = comb(ret, wf[v][c]);
                else
                    ret = comb(inv(wf[v][c]), ret);
                v = lift[v][c];
            }
            c++;
            p >>= 1;
        }
        return ret;
    }

    // pathw checks component, getpath does not
    T pathw(int u, int v){
        pair<int, T> x = findw(u);
        pair<int, T> y = findw(v);
        if(x.first != y.first)
            return -1;
        return getpath(u, v);
    }

    inline T getpath(int u, int v){
        T left{}, right{};
        if(depth[u] > depth[v]){
            left = comb(left, goup(u, depth[u]-depth[v], true));
        }else{
            right = comb(goup(v, depth[v]-depth[u], false), right);
        }
        if(u == v)
            return comb(left, right);
        for(int i = liftAmt-1; i >= 0; --i){
            if(lift[u][i] != lift[v][i]){
                left = comb(left, wf[u][i]);
                right= comb(inv(wf[v][i]), right);
                u = lift[u][i];
                v = lift[v][i];
            }
        }
        return comb(left, comb(wf[u][0], comb(inv(wf[v][0]), right)));
    }
};
