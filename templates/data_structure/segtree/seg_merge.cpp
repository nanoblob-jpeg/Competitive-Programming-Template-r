//  yosupo: https://judge.yosupo.jp/submission/306045
//  1301ms, 168.13Mb
//  n = q = 5e5
//
template<typename T>
class mergetree{
public:
    vector<vector<T>> seg;
    int lbound, rbound;
    mergetree(vector<T> vals):seg(4*vals.size()), lbound(0), rbound(vals.size()-1){
        build(1, lbound, rbound, vals);
    }
    void build(int v, int l, int r, vector<T> &vals){
        if(l > r)
            return;
        if(l == r){
            seg[v].resize(1);
            seg[v][0] = vals[l];
            return;
        }

        int mid = l + (r-l)/2;
        build(v*2, l, mid, vals);
        build(v*2+1, mid+1, r, vals);
        // we fold the auxiliary array for the merge sort into
        // the end of the seg[v] array, minor optimization
        int ind = r-mid, ind2 = mid+1;
        seg[v].resize(r-l+1);
        for(int i = ind, j = l; i < seg[v].size(); ++i, ++j)
            seg[v][i] = vals[j];

        int sind = 0;
        while(ind < seg[v].size() && ind2 <= r){
            seg[v][sind++] = seg[v][ind] < vals[ind2] ? seg[v][ind++] : vals[ind2++];
            vals[l+sind-1] = seg[v][sind-1];
        }
        while(ind2 <= r){
            seg[v][sind++] = vals[ind2++];
            vals[l+sind-1] = seg[v][sind-1];
        }
        while(ind < seg[v].size())
            vals[l+sind++] = seg[v][ind++];
    }

    int qlower_bound(int v, T val, int l, int r, int lq, int rq){
        if(l > r || lq > r || rq < l)
            return 0;
        else if(lq <= l && r <= rq){
            return seg[v].end() - std::lower_bound(seg[v].begin(), seg[v].end(), val);
        }else{
            int mid = l + (r-l)/2;
            return qlower_bound(v*2, val, l, mid, lq, rq) + qlower_bound(v*2+1, val, mid+1, r, lq, rq);
        }
    }

    int lower_bound(int l, int r, T val){
        return qlower_bound(1, val, lbound, rbound, l, r);
    }
    int upper_bound(int l, int r, T val){
        return qlower_bound(1, val+1, lbound, rbound, l, r);
    }
};
