#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include<queue>
#include<cmath>
using namespace std;

typedef pair<int,int> pii; 
typedef long long ll;
typedef pair<ll,int> pli;  
#define MP make_pair

int logn ;

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

int dfs(int cur,int parant,vector<bool> &is_visit,vector<vector<pii>> &graph,queue<int> &cycle_vertex){
    is_visit[cur] = true;
    int find_cycle = 0;
    for(auto [next,dis]:graph[cur]){
        if(!is_visit[next]){
            find_cycle = dfs(next,cur,is_visit,graph,cycle_vertex);
            if(find_cycle && cur != find_cycle){
                cycle_vertex.push(cur);
                return find_cycle;
            }
            // else if(find_cycle == cur){
            //     cycle_vertex.push(cur);
            //     return 0;
            // }
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
    bool find_cycle = 0;
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


void true_dfs2(int cur,vector<bool> &is_visit,vector<vector<pii>> &graph,vector<long long> &dis_to_root){
    is_visit[cur] = true;
    for(auto [next,dis]:graph[cur]){
        if(!is_visit[next]){
            dis_to_root[next] = dis_to_root[cur] + dis;
            true_dfs2(next,is_visit,graph,dis_to_root);
        }
    }
    return ;
}

void dfs2(int n,int cyc_size,vector<int> &index_to_cycle,vector<vector<pii>> &graph,vector<long long> &dis_to_root){
    vector<bool> is_visit(n+1,false);
    for(int i=1;i<=cyc_size ;i++){
        is_visit[index_to_cycle[i]] = true;
    }
    for(int i=1;i<=cyc_size;i++){
        true_dfs2(index_to_cycle[i],is_visit,graph,dis_to_root);
    }
    return ;
}


void true_dfs3(int cur,int &time,int n,int pre,vector<bool> &is_visit,vector<vector<pii>> &graph,vector<int> &in,vector<int> &out,vector<vector<int>> &lca){
    is_visit[cur] = true;
    in[cur] = time;
    time++;
    int k = pre;
    for(int i=0;i<logn+1;i++){
        lca[cur][i] = k, k = lca[k][i];
    }
    for(auto [next,dis]:graph[cur]){
        if(!is_visit[next]){
            true_dfs3(next,time,n,cur,is_visit,graph,in,out,lca);
        }
    }
    out[cur] = time;
    time++;
    return ;
}

void dfs3(int n,int cyc_size,vector<int> &index_to_cycle,vector<vector<pii>> &graph,vector<int> &in,vector<int> &out,vector<vector<int>> &lca){
    vector<bool> is_visit(n+1,false);
    for(int i=1;i<=cyc_size ;i++){
        is_visit[index_to_cycle[i]] = true;
    }
    for(int i=1;i<=cyc_size;i++){
        for(int j=0;j<logn+1;j++){
            lca[index_to_cycle[i]][j] = index_to_cycle[i]; 
        }
    }
    int time = 0;
    for(int i=1;i<=cyc_size;i++){
        true_dfs3(index_to_cycle[i],time,n,index_to_cycle[i],is_visit,graph,in,out,lca);
    }
    return ;
}

int isanc(int anc,int vtx,vector<int> &in,vector<int> &out){
    if( in[anc] <= in[vtx] && out[anc] >= out [vtx]){
        return true;
    }return false;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,q;
    cin>>n>>q;
    logn = log2(n)+1;
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
    vector<int> index_to_cycle;
    vector<int> cycle_to_index(n+1,0);
    int size = 0;
    index_to_cycle.push_back(0);
    while(!cycle.empty()){
        size++;
        index_to_cycle.push_back(cycle.front());
        cycle_to_index[cycle.front()] = size;
        cycle.pop();
    }
    index_to_cycle[0] = index_to_cycle[size];
    index_to_cycle.push_back(index_to_cycle[1]);
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
    //create a sum which save the distance to the tree
    //create a dsu to store which tree the node belongs to
    //create a lca
    vector<long long > dis_to_root(n+1,0);
    dfs2(n,size,index_to_cycle,graph,dis_to_root);
    
    //find lca and inout time
    vector<vector<int>> lca(n+1,vector<int>(logn+1));
    vector<int> in(n+1),out(n+1);
    dfs3(n,size,index_to_cycle,graph,in,out,lca);


    
    
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
            //case 1 on different tree
             if(lca[u][logn] != lca[v][logn]){
                source = cycle_to_index[lca[u][logn]];
                dest   = cycle_to_index[lca[v][logn]];
                if(dest < source) swap(source,dest);
                long long ans = min( bit.query(dest) - bit.query(source), (bit.query(source) - 0 ) + (bit.query(size) - bit.query(dest)) );
                ans += dis_to_root[u] + dis_to_root[v];
                cout<<ans<<'\n';
            }
            //case 2 on the same tree
            else {
                int root ;
                if(isanc(u,v,in,out)) root = u;
                else if(isanc(u,v,in,out)) root = v;
                else {
                    root = u;
                    for(int i = logn ;i>=0 ;i-- ){
                        if(!isanc(lca[root][i],v,in,out)){
                            root = lca[root][i];
                        }
                    }
                    root = lca[root][0];
                }
                long long ans = dis_to_root[u] + dis_to_root[v] - 2*dis_to_root[root];
                cout<<ans<<"\n";
            }
            cout<<endl;
       
        }else{
            cout<<"wrong operation ,please try again\n";
        }

    }

  
    return 0;
    


}

/*
10 10
1 2 1
2 3 1
3 4 1
3 1 1
3 7 1
4 5 1
5 6 1
5 8 1
7 10 1
7 9 1

 */