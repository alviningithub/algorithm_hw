#include<iostream>
#include<vector>

using namespace std;

void linear_sieve(int n,vector<bool> &is_prime){
    is_prime.resize(n+1,1);
    is_prime[0] = false;
    is_prime[1] = false;
    vector<int> prime;
    prime.clear();
    for(int i=2;i<=n;i++){
        if(is_prime[i] )
            prime.push_back(i);
        for(int j : prime){
            if((long long )i*j >n) break;
            is_prime[i*j] = false;
            if(i % j  == 0 ) break;       
        }
    }
}

template<class T>
class segment_tree {
public:
    //segment_tree();
   
    void build_with_array(vector<T> &array,int sz){
        if(sz == 0) return ;
        capacity = 4*sz;
        size = sz;
        the_tree.resize(capacity+1);
        build(0,size-1,1,array);

    }
    T query(int L,int R){
        return recursive_query(L,R,0,size-1,1);    
    }
    void modify(int pos ,T& val){
        recursive_modify(0,size-1,pos,val,1);
    }


private:
    vector<T> the_tree;
    int capacity = 0;
    int size = 0;
    
    
    T& merge( T &a,  T &b) const{
        return (a > b) ? a : b ;
    }

    void build(int L,int R , int cur ,vector<T> &array){
        if(L == R){
            the_tree[cur] = array[L];
            return;
        } 
        int mid = (R-L)/2+L;
        build(L,mid,cur*2,array);
        build(mid+1,R,cur*2+1,array);
        the_tree[cur] = merge(the_tree[cur*2],the_tree[cur*2+1]);
        
    }

    T& recursive_query(int query_l,int query_r,int cur_l,int cur_r,int cur) {
        if(query_l == cur_l && query_r == cur_r ) return the_tree[cur];
        int mid = (cur_r - cur_l)/2+cur_l;
        if(mid >= query_r){
            return recursive_query(query_l,query_r,cur_l,mid,cur*2);
        }else if(mid+1 <= query_l){
            return recursive_query(query_l,query_r,mid+1 , cur_r, cur*2+1);
        }else{
            return merge(recursive_query(query_l,mid,cur_l,mid,cur*2),recursive_query(mid+1,query_r,mid+1,cur_r,cur*2+1));
        }
    }

    void recursive_modify(int L,int R,int pos,T &val,int cur){
        if(L == R){
            the_tree[cur] = val;
            return;
        } 
        int mid = (R-L)/2+L;
        if( pos <= mid ){
            recursive_modify(L,mid,pos,val,cur*2);
        }else {
            recursive_modify(mid + 1 ,R,pos,val,cur*2+1);
        }
        the_tree[cur] = merge(the_tree[cur*2],the_tree[cur*2+1]);
    }


};



int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,q;
    cin>>n>>q;
    //find prime
    vector<bool> is_prime;
    linear_sieve((int)1e6+1,is_prime);

    vector<int > array(n);
    for(int i=0;i<n;i++){
        //if not prime change to -1
        int a;
        cin>>a;
        if(is_prime[a]){
            array[i] = a;
        }else 
            array[i] = -1;
        
    }

    segment_tree<int> S;
    S.build_with_array(array,n);
    while(q--){
        int op;
        cin>>op;
        switch(op){
        case 1:
            int idx,val;
            cin>>idx>>val;
            idx=idx-1;
            if(!is_prime[val]) val = -1;
              S.modify(idx,val);
            break;
        case 2:
            int L,R;
            cin>>L>>R;
            cout<<S.query(L-1,R-1)<<" ";
            break;
        
        default:
            cout<<"wrong query";
        }
    }
}