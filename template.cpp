#include <bits/stdc++.h>

using namespace std;

// thank you geothermal :goat:
void __deb(int t) {cerr << t;}
void __deb(long t) {cerr << t;}
void __deb(long long t) {cerr << t;}
void __deb(unsigned int t) {cerr << t;}
void __deb(unsigned long t) {cerr << t;}
void __deb(unsigned long long t) {cerr << t;}
void __deb(float t) {cerr << t;}
void __deb(double t) {cerr << t;}
void __deb(long double t) {cerr << t;}
void __deb(char t) {cerr << '\'' << t << '\'';}
void __deb(const char *t) {cerr << '\"' << t << '\"';}
void __deb(const string &t) {cerr << '\"' << t << '\"';}
void __deb(bool t) {cerr << (t ? "true" : "false");}
template<typename T, typename V>
void __deb(const pair<T, V> &x){ cerr << '{'; __deb(x.first); cerr << ", "; __deb(x.second); cerr << '}'; }
template<typename T>
void __deb(const T &x){
    int f = 0; cerr << '{'; 
    for(auto &i: x){ if(f++) cerr << ", "; __deb(i);}
    cerr << "}";
}
void _rdeb(vector<string> &names, int ind){}
template<typename T, typename... V>
void _rdeb(vector<string> &names, int ind, T t, V... v){
    if(ind != 0) cerr << "==============\n";
    cerr << names[ind] << '\n'; __deb(t); cerr << '\n';
    _rdeb(names, ind+1, v...);
}
template<typename... V>
void _deb(string vars, V... v){
    vector<string> names(1);
    for(char c : vars)
        if(c == ','){
            while(names.back().size() && isspace(names.back().back())) names.back().pop_back();
            names.push_back("");
        }else
            if(!isspace(c) || names.back().size())
                names.back().push_back(c);
    while(names.back().size() && isspace(names.back().back())) names.back().pop_back();
    _rdeb(names, 0, v...);
}
#ifdef DEBUG
#define deb(x...) {                              \
    cerr << __func__ << ':' << __LINE__ << '\n'; \
    _deb(#x, x);                                 \
}
#define debsep(x...) {                           \
    cerr << __func__ << ':' << __LINE__ << '\n'; \
    _deb(#x, x);                                 \
    cerr << "****************************\n";    \
}
#else
#define deb(x...)
#define debsep(x...)
#endif

#define ar array
#define ll long long
typedef int uci;
#define int long long
#define F first
#define S second
typedef complex<double> cd;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define irep(i, a, b) for(int i = a; i > (b); --i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef pair<int, int> pii;
#define ve vector
typedef ve<int> vi;
typedef ve<vi> vvi;

seed_seq seq{
    (uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
    (uint64_t) __builtin_ia32_rdtsc(),
    (uint64_t) (uintptr_t) make_unique<char>().get()
};
mt19937 rng(seq);
// mt19937_64 lrng(seq);

struct debugger{
    template <typename T>
    debugger& operator<<(T &a){
        #ifdef DEBUG
            cerr << a;
        #endif
        return *this;
    }
    template <typename T>
    debugger& operator<<(T &&a){
        #ifdef DEBUG
            cerr << a;
        #endif
        return *this;
    }
} deb;

const double PI = acos(-1.0);
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

//! function insert

//THINK FIRST, CODE SECOND
//DON'T GET STUCK ON ONE STRATEGY
//CALM DOWNNN FOR ONCE IN YOUR LIFE
//REDUCE
//COUGH E??!?!?!! O.O
//uwu i see you ryan

void solve() {

}

uci main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}

/*
    random number generator stuff
    num = rng(); gives integer number
    num = uniform_int_distribution<int>(a, b)(rng); -> bounds [a, b]
    num = uniform_real_distribution<double>(a, b)(rng); -> bounds [a, b)
    can also instantiate distributions and call on generator:
    uniform_int_distribution<int> thing(a, b);
    num = thing(rng);
*/
// struct custom_hash {
//     static uint64_t splitmix64(uint64_t x) {
//         // http://xorshift.di.unimi.it/splitmix64.c
//         x += 0x9e3779b97f4a7c15;
//         x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
//         x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
//         return x ^ (x >> 31);
//     }
//     size_t operator()(uint64_t x) const {
//         static const uint64_t FIXED_RANDOM = lrng();
//         return splitmix64(x + FIXED_RANDOM);
//     }
// };
