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
    //! test point_set_range_freq_decl
    for(int i{}; i < n; ++i)
        ds.update(i, a[i]);

    while(q--){
        int t;
        cin >> t;
        if(t == 0){
            int k, v;
            cin >> k >> v;
            ds.update(k, v);
        }else{
            int l, r, x;
            cin >> l >> r >> x;
            r--;
            if(l <= r){
                cout << ds.query(l, r, x) << '\n';
            }else
                cout << 0 << '\n';
        }
    }
}
