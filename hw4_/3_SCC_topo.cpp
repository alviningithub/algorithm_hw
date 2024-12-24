#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<set>
#include<utility>
using namespace std;

class DSU{
    public:
        DSU(){
            dsu.resize(200005);
            for(int i=0;i<200005;i++){
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
DSU scc;

void dfs_fin(int cur, vector<vector<int>> &graph,stack<int> &fin,vector<bool > &is_visit ){
    is_visit[cur] = true;
    for(int i:graph[cur]){
        if(!is_visit[i])
            dfs_fin(i,graph,fin,is_visit);
    }
    fin.push(cur);
}

long long dfs_scc(int cur ,vector<vector<int >> &graph, vector<bool> &is_visit,long long pinecones[]){
    long long sum = 0;
    is_visit[cur] = true;
    for(int i:graph[cur]){
        if(!is_visit[i]){
            scc.uni(cur,i);
            sum += dfs_scc(i,graph,is_visit,pinecones);
        }
    }
    return sum + pinecones[cur];
}

void dfs_fin_2(int cur, vector<vector<int>> &graph,stack<int> &fin,vector<bool > &is_visit ){
    is_visit[cur] = true;
    for(int i:graph[cur]){
        if(!is_visit[scc.find(i)])
            dfs_fin(scc.find(i),graph,fin,is_visit);
    }
    fin.push(cur);
}

    long long coin[200001]; //add a array
    long long  ans[200001] = {}; 
#define pii pair<int,int>
#define MP make_pair

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1; i<=n; i++) cin>>coin[i];
    vector<vector<int >> graph(n+1);
    vector<vector<int> > graph_reverse(n+1);
    for(int i = 0 ; i < m ; i ++) {
        int a,b;
        cin>>a>>b;
        graph[a].push_back(b);
        graph_reverse[b].push_back(a);
    }
    
    //dfs fisrt time  find finish time
    stack<int> fin_time;
    vector<bool> is_visit(n+1);
    for(int i=1;i<=n;i++){
        if(!is_visit[i])    
            dfs_fin(i,graph,fin_time,is_visit);
    }

    //dfs second time find scc and create another stack to store sum and root 
    for(int i=0;i<=n;i++) is_visit[i] = false;
    long long tmp;
    for(int i = 1 ;i <=n;i++){
        if(!is_visit[fin_time.top()]){
            tmp=dfs_scc(fin_time.top(),graph_reverse,is_visit,coin);
            coin[scc.find(fin_time.top())] = tmp;
        }
        fin_time.pop();
    }
    
    //create a new graph with reverse edge 
    // vector<vector<int>> new_graph_re(n+1);
    //clear graph for mem
    for(int i=0;i<=n;i++){
        graph[i].clear();
    }
    set<pii> s;
    for(int i=1;i<=n;i++){
        for(int j: graph_reverse[i]){
            int start = scc.find(i);
            int end = scc.find(j);

            if(start != end && s.find(MP(i,j)) == s.end()){
                graph[start].push_back(end) ;
                s.insert(MP(i,j));
            }
        }
    }

    //topological sort
    for(int i=0;i<=n;i++) is_visit[i] = false;
    while(!fin_time.empty()) fin_time.pop();
    for(int i=1;i<=n;i++){
        if(!is_visit[scc.find(i)] ) dfs_fin_2(scc.find(i),graph,fin_time,is_visit);
    }
    //dp on this dag
    while(!fin_time.empty()){
        int cur = fin_time.top();
        fin_time.pop();
        ans[cur] = max(ans[cur],coin[cur]);
        for(int i:graph[cur]){
            ans[i] = max(ans[i],ans[cur] + coin[i]);
        }
    }
    //output
    for(int i=1;i<=n ; i++){
        cout<<ans[scc.find(i)]<<" ";
    }

    return 0;




}