//  yosupo: https://judge.yosupo.jp/submission/306107
//  non cleanup
//  430ms, 280.06Mb
//  q = 5e5
//  non cleanup
//  in random -> ~0.5x memory, but max mem still same
//
template<int bits = 30, bool multiset = true>
class bittrie{
public:
    struct node{
        node* child[2];
        int wordends, totalCount;
        node():wordends(0),totalCount(0){
            child[0] = child[1] = nullptr;
        }
    };
    node *root;

    bittrie(){
        root = new node();
    }

    bool addWord(node* no, int s, int ind){
        if(ind < 0){
            if(multiset || no->wordends == 0){
                no->wordends++;
                no->totalCount++;
                return true;
            }
            return false;
        }
        int t = !!(s&(1ll<<ind));
        if(!no->child[t]){
            no->child[t] = new node();
        }
        if(addWord(no->child[t], s, ind-1)){
            no->totalCount++;
            return true;
        }
        return false;
    }

    bool addWord(int s){
        return addWord(root, s, bits-1);
    }

    bool removeWord(node* no, int s, int ind){
        if(ind < 0){
            if(no->wordends > 0){
                no->wordends--;
                no->totalCount--;
                return true;
            }
            return false;
        }
        int t = !!(s&(1ll<<ind));
        if(!no->child[t])
            return false;
        if(removeWord(no->child[t], s, ind-1)){
            no->totalCount--;
#ifdef CLEAN_UP
            if(no->child[t]->totalCount == 0){
                delete no->child[t];
                no->child[t] = nullptr;
            }
#endif
            return true;
        }
        return false;
    }

    bool removeWord(int s){
        return removeWord(root, s, bits-1);
    }

    int size(){
        return root->totalCount;
    }

    void buildMinXorElement(node* no, int s, int ind, int& ret){
        if(ind < 0 || no->totalCount == 0)
            return;
        int t = !!(s&(1ll<<ind)); // max should just be using one ! instead of !!
        if(no->child[t] && no->child[t]->totalCount > 0){
            ret |= t<<ind;
            buildMinXorElement(no->child[t], s, ind-1, ret);
        }else{
            ret |= (t^1)<<ind;
            buildMinXorElement(no->child[t^1], s, ind-1, ret);
        }
    }

    int minXorElement(int x){
        int ret{};
        buildMinXorElement(root, x, bits-1, ret);
        return ret;
    }
};
