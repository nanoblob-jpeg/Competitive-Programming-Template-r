template <typename T>
class bit{
public:
    vector<T> tree;
    int si;
    bit(int n): tree(n){si = n;}
    bit(vector<T> &a): tree(a.size()), si(a.size()){
        for(int i{}; i < a.size(); ++i){
            update(i, a[i]);
        }
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
            ind -= ind&-ind;
        }
        return sum;
    }

    // [start, end], 0 indexed
    T query(int start, int end){
        T sum = query(end);
        if(start != 0){
            sum -= query(start-1);
        }
        return sum;
    }
};
