#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long
typedef int uci;
#define int long long

//! test ds
//! function insert

uci main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int n, q;
    cin >> n >> q;
    //! test uf_decl
    for(int i{}; i < q; ++i){
        int t, u, v;
        cin >> t >> u >> v;
        if(t == 0){
            uf.merge(u, v);
        }else{
            cout << (uf.find(u) == uf.find(v)) << '\n';
        }
    }
}
