#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long
typedef int uci;
#define int long long

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
    vector<int> a(n);
    for(int i{}; i < n; ++i)
        cin >> a[i];
    //! test point_add_range_sum_decl
    while(q--){
        int t;
        cin >> t;
        if(t == 0){
            int p, x;
            cin >> p >> x;
            ds.update(p, x);
        }else{
            int l, r;
            cin >> l >> r;
            cout << ds.query(l, r-1) << '\n';
        }
    }
}
