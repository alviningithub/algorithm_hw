#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include<queue>
#include<cmath>
using namespace std;
#define mod 998244353

typedef pair<int,int> pii; 
typedef long long ll;
typedef pair<ll,int> pli;  
#define MP make_pair

int logn ;


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
    
        true_dfs2(1,is_visit,graph,dis_to_root);
    
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
    // for(int i=1;i<=cyc_size ;i++){
    //     is_visit[index_to_cycle[i]] = true;
    // }
    // for(int i=1;i<=cyc_size;i++){
    //     for(int j=0;j<logn+1;j++){
    //         lca[index_to_cycle[i]][j] = index_to_cycle[i]; 
    //     }
    // }
    int time = 0;
    
    true_dfs3(1,time,n,1,is_visit,graph,in,out,lca);
    
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
    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        graph[a].push_back(MP(b,1));
        graph[b].push_back(MP(a,1));
    }

    for(int i=1;i<=n;i++){
        sort(graph[i].begin(),graph[i].end());
    }
    int size;
    vector<int> index_to_cycle;
    vector<long long > dis_to_root(n+1,0);
    dfs2(n,size,index_to_cycle,graph,dis_to_root);
    
    //find lca and inout time

    vector<vector<int>> lca(n+1,vector<int>(logn+1));
    vector<int> in(n+1),out(n+1);
    dfs3(n,size,index_to_cycle,graph,in,out,lca);

    while(q--){
        int u,v;
        cin>>u>>v;
        
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
}