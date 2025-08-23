//  yosupo: https://judge.yosupo.jp/submission/309439
//  104ms, 19.85Mb
//  n = q = 2e5
//
template <typename T>
struct UFOp;

template<typename T, template <typename> class Comb = UFOp>
class UF{
public:
    using Op = UFOp<T>;
    vector<int> uf, sizes, depth;
    vector<T> wf;
    vector<vector<int>> adj;
    UF(int n):uf(n), wf(n, Op::identity), sizes(n, 1), adj(n), depth(n){
        iota(uf.begin(), uf.end(), 0);
    }

    // recalculate depth
    void calc(int v, int p){
        depth[v] = depth[p]+1;
        for(auto& a : adj[v])
            calc(a, v);
    }

    // adding edge u -> v with weight w such that u+w = v
    int merge(int u, int v, T w){
        pair<int, T> x = find(u), y = find(v);
        if(x.first != y.first){
            T amt = Op::connect(x.second, w, y.second);
            if(sizes[x.first] > sizes[y.first]){
                swap(x, y);
                amt = Op::inv(amt);
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

    // log(n) finding
    pair<int, T> find(int v){
        if(uf[v] == v){
            return {v, Op::identity};
        }
        pair<int, T> ret = find(uf[v]);
        return {ret.first, Op::combine(wf[v], ret.second)};
    }

    T path(int u, int v){
        T wu = Op::identity, wv = Op::identity;
        while(depth[u] > depth[v]){
            wu = Op::combine(wu, wf[u]);
            u = uf[u];
        }
        while(depth[v] > depth[u]){
            wv = Op::combine(wv, wf[v]);
            v = uf[v];
        }
        while(u != v && uf[u] != u){
            wu = Op::combine(wu, wf[u]);
            u = uf[u];
            wv = Op::combine(wv, wf[v]);
            v = uf[v];
        }
        if(u == v)
            return Op::combine(wu, Op::inv(wv));
        else
            return Op::invalid;
    }
};

const int MOD = 998244353;
struct matrix{
    array<array<int, 2>, 2> val;
    constexpr matrix():val(){}
    constexpr matrix(int a, int b, int c, int d):val{{{a, b}, {c, d}}}{}
    int det(){
        return (((val[0][0]*val[1][1])%MOD - (val[0][1]*val[1][0])%MOD)%MOD + MOD)%MOD;
    }
    void mult(int m){
        val[0][0] = (val[0][0]*m)%MOD;
        val[0][1] = (val[0][1]*m)%MOD;
        val[1][0] = (val[1][0]*m)%MOD;
        val[1][1] = (val[1][1]*m)%MOD;
    }
    void inv(){
        int d = det();
        swap(val[0][0], val[1][1]);
        val[0][1] = ((val[0][1]*-1)+MOD)%MOD;
        val[1][0] = ((val[1][0]*-1)+MOD)%MOD;
        mult(d);
    }

    bool operator==(const matrix& other){
        return val == other.val;
    }
    bool operator!=(const matrix& other){
        return val != other.val;
    }
};

template <typename T>
struct UFOp{
    static constexpr T identity = T(1, 0, 0, 1);
    static constexpr T invalid = T(-1, -1, -1, -1);
    // inverse
    static T inv(T a){
        a.inv();
        return a;
    }

    static T combine(T a, T b){
        // this is for joining two weights end to end
        T ret;
        for(int i{}; i < 2; ++i){
            for(int j{}; j < 2; ++j){
                for(int k{}; k < 2; ++k){
                    ret.val[i][j] = (ret.val[i][j] + (a.val[i][k]*b.val[k][j])%MOD)%MOD;
                }
            }
        }
        return ret;
    }

    static T connect(T a, T b, T c){
        // this is for connecting between two trees
        // a = [x...y], c = [z...w], b = [x..yz..w]
        // 
        // x + b = w -> (x + a) + u = w -> y + u = w
        // w + c = z -> w = z - c
        // y + u = z - c -> y + u + c = z
        // y + (-a + b) + c = z
        return combine(combine(inv(a), b), c);
    }
};