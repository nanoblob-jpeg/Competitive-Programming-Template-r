#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long
typedef int uci;
#define int long long

const int MOD = 998244353;
struct Func{
    int m, b;
    Func(int x = 1, int y = 0):m(x),b(y){}
};

//! test op_pre_decl
//! test ds
//! test op_decl
//! function insert

uci main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int n, q;
    cin >> n >> q;
    vector<Func> a(n);
    for(int i{}; i < n; ++i){
        cin >> a[i].m >> a[i].b;
    }

    //! test point_set_range_composite_decl
    while(q--){
        int t;
        cin >> t;
        if(t == 0){
            int p, c, d;
            cin >> p >> c >> d;

            ds.update(p, Func(c, d));
        }else{
            int l, r, x;
            cin >> l >> r >> x;
            Func ret = ds.query(l, r-1);
            int val = ((x*ret.m)%MOD + ret.b)%MOD;
            cout << val << '\n';
        }
    }
}
