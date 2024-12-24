#include<iostream>
#include<tuple>
#include<algorithm>
#include<vector>
#include<stack>
#include<utility>
using namespace std;


#define MT make_tuple
#define pil pair<int,long long >
#define MP make_pair


template<class T>  
class segment_tree {
public:
    //segment_tree();
    void build_with_interger(int sz,int default_value){
        if(sz == 0) return ;
        capacity = 4*sz;
        size = sz;
        the_tree.resize(capacity+1);
        for(int i=1;i<=capacity;i++) the_tree[i] = default_value;
    }
    void build_with_array(vector<T> &array,int sz){ //input the array which start from 1 && the array size
        if(sz == 0) return ;
        capacity = 4*sz;
        size = sz;
        the_tree.resize(capacity+1);
        build(0,size-1,1,array);

    }
    T query(int L,int R){
        if(L > R) return 0;
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


bool cmp(tuple<int,int,int,int> a, tuple<int,int,int,int> b){
    //sort by difficult then floor 
    if(get<2>(a) != get<2>(b)){
        return get<2>(a) < get<2>(b); 
    }
    return get<0>(a) < get<0>(b);
}




//create a compare function for tuple
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    vector<tuple<int,int,int,int>> floor_data(n+1); //#floor ,lowest floor can reach,difficulty,value,
    for(int i=0;i<n;i++){
        int d,v,l;
        cin>>d>>v>>l;
        floor_data[i] = MT(i,i-l,d,v);
    }
    sort(floor_data.begin(),floor_data.begin()+n,cmp);
    segment_tree<long long > st;
    st.build_with_interger(n,0); //the maximum reward you can get in the range level
    int last_difficulty = 0;
    stack<pil> cache;
    for(int i=0;i<n;i++){
        auto [top,bottom,difficulty,reward] = floor_data[i];
        //if difficult increase flush the cache
        if(difficulty > last_difficulty){
            while(!cache.empty()){
                st.modify(cache.top().first,cache.top().second);
                cache.pop();
            }
        }
        //find the maxval in the floor 
        int max_reward = st.query(bottom,top-1);
        int cur_reward = reward + max_reward;
        //cache the result 
        cache.push(MP(top,cur_reward));
        last_difficulty = difficulty;
    }

    //clear the cache
    while(!cache.empty()){
        st.modify(cache.top().first,cache.top().second);
        cache.pop();
    }
    long long ans = st.query(0,n-1);
    cout<<ans<<endl;
    

}