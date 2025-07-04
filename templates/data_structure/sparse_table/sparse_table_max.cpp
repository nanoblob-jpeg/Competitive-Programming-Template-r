template<typename T>
class sparseTable{
public:
    vector<int> powt;
    vector<vector<T>> stable;
    sparseTable(vector<T>& arr){
        int n = arr.size();
        powt.resize(n+1);
        for(int i{2}; i <= n; ++i){
            powt[i] = powt[i/2]+1;
        }

        stable = vector<vector<T>>(powt[n]+1, vector<T>(n));
        stable[0] = arr;
        for(int i{1}; i <= powt[n]; ++i){
            for(int j{}; j + (1ll<<i) <= n; ++j){
                stable[i][j] = sparseFunc(stable[i-1][j], stable[i-1][j+(1ll<<(i-1))]);
            }
        }
    };

    // [l, r], 0-indexed, range query
    T query(int l, int r){
        if(l > r || l < 0 || r >= stable[0].size()){
            assert(false);
            return T();
        }

        int pt = powt[r-l+1];
        return sparseFunc(stable[pt][l], stable[pt][r-(1ll<<pt)+1]);
    }

    inline T sparseFunc(const T& a, const T& b){
        return max(a, b);
    }
};
