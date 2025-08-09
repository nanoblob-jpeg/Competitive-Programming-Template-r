//  yosupo: https://judge.yosupo.jp/submission/305289
//  98ms, 15.63Mb
//  n = q = 5e5
//
template<typename T>
class prefixSum{
public:
    vector<T> vals;
    prefixSum(vector<T>& in):vals(in.size()+1){
        for(int i{}; i < vals.size(); ++i)
            vals[i+1] = vals[i] + in[i];
    }

    T query(int l, int r){
        return vals[r+1] - vals[l];
    }

    T query(int r){
        return vals[r+1];
    }
};
