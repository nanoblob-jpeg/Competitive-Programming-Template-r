//  yosupo: https://judge.yosupo.jp/submission/304417
//  34ms, 4.59Mb
//  n = q = 2e5
//
//! test start ds
class UF{
public:
    vector<int> uf;
    UF(int n):uf(n){
        iota(uf.begin(), uf.end(), 0);
    }

    int find(int v){
        if(uf[v] == v)
            return uf[v];
        return uf[v] = find(uf[v]);
    }

    int merge(int u, int v){
        u = find(u);
        v = find(v);
        if(u != v){
            uf[u] = v;
            return 1;
        }
        return 0;
    }
};
//! test end ds
