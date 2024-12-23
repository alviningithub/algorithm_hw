#include<iostream>
#include<vector>
#include<stack>
using namespace std;

void dfs_fin(int cur, vector<vector<int>> &graph,stack<int> &fin,vector<bool > &is_visit ){
    is_visit[cur] = true;
    for(int i:graph[cur]){
        if(!is_visit[i])
            dfs_fin(i,graph,fin,is_visit);
    }
    fin.push(cur);
}

long long dfs_scc(int cur ,vector<vector<int >> &graph, vector<bool> &is_visit,vector<int> &pinecones,stack<int> &scc){
    long long sum = 0;
    scc.push(cur);
    is_visit[cur] = true;
    for(int i:graph[cur]){
        if(!is_visit[i]){
            sum += dfs_scc(i,graph,is_visit,pinecones,scc);
        }
    }
    return sum + pinecones[cur];
}

int main(){
    //input
    int n,m;
    cin>>n>>m;
    vector<int > pinecones(n+1);
    for(int i=1;i<=n;i++){
        cin>>pinecones[i];
    }
    vector<vector<int >> graph(n+1);
    vector<vector<int >> graph_reverse(n+1);
    for(int i=1;i<=m;i++){
        int a,b;
        cin>>a>>b;
        graph[a].push_back(b);
        graph_reverse[b].push_back(a);
    }

    //SCC

    //dfs once find finish time
    stack<int > finish_time;
    vector<bool> is_visit(n+1,false);
    for(int i=1;i<=n;i++){
        if(!is_visit[i])
            dfs_fin(i,graph,finish_time,is_visit);
    }

    //dfs reversely again with data update
    vector<long long > ans(n+1);
    for(int i=0;i<=n;i++) is_visit[i] = false;
    stack<int> scc;
    while(!finish_time.empty()){
        if(!is_visit[finish_time.top()]){
            long long sum = dfs_scc(finish_time.top(),graph_reverse,is_visit,pinecones,scc);
            while(!scc.empty()){
                ans[scc.top()] = sum;
                scc.pop();
            }
        }
        finish_time.pop();
    }

    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }cout<<endl;
}