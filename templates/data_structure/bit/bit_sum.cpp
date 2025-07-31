//  yosupo: https://judge.yosupo.jp/submission/304020
//  120ms, 11.99Mb
//  n = q = 5e5
//
template <typename T>
class bit{
public:
    vector<T> tree;
    int si;
    bit(int n): tree(n), si(n){}
    bit(vector<T> &a): tree(a), si(a.size()){
        for(int i = si; i >= 1; --i)
            update(i+(i&-i)-1, tree[i-1]);
    }
    bit(vector<T> &&a): si(a.size()), tree(a){
        for(int i = si; i >= 1; --i)
            update(i+(i&-i)-1, tree[i-1]);
    }

    // 0 indexed
    void update(int ind, int val){
        ind++;
        while(ind <= si){
            tree[ind-1] += val;
            ind += ind&-ind;
        }
    }

    // [0, ind], 0 indexed
    T query(int ind){
        T sum = 0;
        if(ind < 0 || ind >= si)
            assert(false);
        ind++;
        while(ind >= 1){
            sum += tree[ind-1];
            ind ^= ind&-ind;
        }
        return sum;
    }

    // [start, end], 0 indexed
    T query(int start, int end){
        T sum = query(end);
        if(start != 0)
            sum -= query(start-1);
        return sum;
    }
};
