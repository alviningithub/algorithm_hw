#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include<queue>
using namespace std;

typedef pair<int,int> pii; 
typedef long long ll;
typedef pair<ll,int> pli;  
#define MP make_pair

class BIT{
    public:
        int lowbit(int x){
            return x&-x;
        }

        void build(vector<int> &v,int n){
            if(n < 1) return;
            capacity = n;
            the_tree.resize(n+1);
            vector<long long> presum(n+1,0);
            for(int i=1;i<=n;i++){
                presum[i] = presum[i-1] + v[i];
            }
            for(int i=1;i<=n;i++){
                int left = i - lowbit(i) + 1;
                the_tree[i] = presum[i] - presum[left-1];
            }
            return ;

        }

        long long query(int pos){
            long long  ans = 0;
            for(;pos > 0; pos -= lowbit(pos)){
                ans += the_tree[pos];
            }
            return ans;
        }

        void modify(int pos,long long x){ //add x to pos
            for(;pos<= capacity; pos += lowbit(pos)){
                the_tree[pos] += x;
            }   
        }
    private:
        vector<long long> the_tree;
        int capacity;   
};


class DSU{
    public:
        DSU(){
            dsu.resize(300005);
            for(int i=0;i<300005;i++){
                dsu[i] = i;
            }
        }

        int find(int a){
            if(dsu[a] == a) return a;
            dsu[a] = find(dsu[a]);
            return dsu[a];
        }
        
        void uni(int a,int b){
            int root_a = find(a);
            int root_b = find(b);
            if(root_a == root_b) return;
            if(root_a <= root_b){
                dsu[root_b] = root_a;
                return ;
            }
            dsu[root_a] = root_b;
        }


    private:
        vector<int> dsu; //add array
};

int dfs(int cur,int parant,vector<bool> &is_visit,vector<vector<pii>> &graph,queue<int> &cycle_vertex){
    is_visit[cur] = true;
    int find_cycle = 0;
    for(auto [next,dis]:graph[cur]){
        if(!is_visit[next]){
            find_cycle = dfs(next,cur,is_visit,graph,cycle_vertex);
            if(find_cycle && cur != find_cycle){
                cycle_vertex.push(cur);
                return find_cycle;
            }else if(find_cycle == cur){
                cycle_vertex.push(cur);
                return 0;
            }
        }else if( next != parant){
            cycle_vertex.push(cur);
            return next;
        }
    }
    return 0;
}




queue<int> find_the_cycle(int N,vector<vector<pii>> &graph){
    vector<bool> is_visit(N+1,false);
    vector<int> parant(N+1,0);
    queue<int> q;
    q.push(1);
    //find a point on the cycle
    int cur;
    bool find_cycle;
    while(!q.empty()){
        cur =q.front();
        q.pop();
        is_visit[cur] = true;
        for(auto [next,dis]:graph[cur]){
            if(!is_visit[next] ){
                parant[next] = cur;
                q.push(next);
            }else if( parant[cur] != next){
                find_cycle = true;
                break;
            }
        }
        if(find_cycle ) break;
    }
    fill(is_visit.begin(),is_visit.end(),false);
    while(!q.empty()) q.pop();
    dfs(cur,0,is_visit,graph,q);
    return q;
    
}

bool comp(pii a,int b){
    return a.first < b;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,q;
    cin>>n>>q;
    vector<vector<pii>> graph(n+1);
    for(int i=0;i<n;i++){
        int a,b,w;
        cin>>a>>b>>w;
        graph[a].push_back(MP(b,w));
        graph[b].push_back(MP(a,w));
    }
    for(int i=1;i<=n;i++){
        sort(graph[i].begin(),graph[i].end());
    }
    
    //find circular by bfs
    queue<int> cycle = find_the_cycle(n,graph);
    //deal with cycle
    vector<int> index_to_cycle(1,0);
    vector<int> cycle_to_index(n+1,0);
    int size = 0;
    while(!cycle.empty()){
        size++;
        index_to_cycle.push_back(cycle.front());
        cycle_to_index[cycle.front()] = size;
        cycle.pop();
    }
    index_to_cycle[0] = index_to_cycle[size];
    if(size != n) return 0 ; //only cycle
    vector<int> dis_on_cyc(size+1,0);
    int source,dest;
    for(int i=0;i<size;i++){
        source = index_to_cycle[i];
        dest = index_to_cycle[i+1];      
        auto it = lower_bound(graph[source].begin(),graph[source].end(),dest,comp);
        dis_on_cyc[i+1] = it->second;
    }
    BIT bit;
    bit.build(dis_on_cyc,size);
    dis_on_cyc.clear();
    // deal with branch
    //dfs on all point on the cycle
    //remember the sequence 
    //create a sum which save the distance to the tree
    // vector<long long > dis_to_root(n+1,0);
    // for(int i=1;i<size;i++){
        
    // }
    
    while(q--){
        int op;
        cin>>op;
        if(op == 1){
            int a,b,c;
            cin>>a>>b>>c;
            auto it = lower_bound(graph[a].begin(),graph[a].end(),b,comp);
            it->second += c;
            it = lower_bound(graph[b].begin(),graph[b].end(),a,comp);
            it->second += c;
            if(cycle_to_index[a] != 0 && cycle_to_index[b] != 0){
                int modify_pos_idx;
                if(cycle_to_index[a] == 1 && cycle_to_index[b] == size || cycle_to_index[b] == 1 && cycle_to_index[a] == size)
                    modify_pos_idx = 1 ;// special case 
                else 
                    modify_pos_idx = max(cycle_to_index[a],cycle_to_index[b]);
                bit.modify(modify_pos_idx,c);
            }
        }else if(op == 2){
            int u,v;
            cin>>u>>v;
            if(cycle_to_index[u] != 0 && cycle_to_index[v] != 0){
                source = cycle_to_index[u];
                dest = cycle_to_index[v];
                if(dest < source) swap(source,dest);
                cout<< min( bit.query(dest) - bit.query(source), (bit.query(source) - 0 ) + (bit.query(size) - bit.query(dest)) )<<"\n";
            }
            
       
        }else{
            cout<<"wrong operation ,please try again\n";
        }

    }

  
    return 0;
    


}