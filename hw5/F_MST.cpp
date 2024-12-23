#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<queue>
using namespace std;

#define piii pair<pair<int,int>,int>
#define pii pair<int,int>
#define MP make_pair

typedef vector< vector< pii>> graph_T;

vector<int> mst(int n,vector<vector<pii>> &graph,vector<piii> &edge){
    priority_queue<piii,vector<piii>,greater<piii>> pq;
    vector<bool> is_visit(n+1,false);
    vector<int> MST_edge;
    int counter = 0;
    int sum = 0;
    for(int i=1;i<=n;i++){
        if(!is_visit[i])
        is_visit[i] = true;
            for(pii p: graph[i]){
                if(!is_visit[p.first]){
                    pq.push(MP(MP(edge[p.second].second,p.second),p.first));
                }
            }
            while(!pq.empty()){
                piii cur = pq.top();
                pq.pop();
                while(!pq.empty() && is_visit[cur.second]) {
                    cur = pq.top();
                    pq.pop();
                }
                if(pq.empty() && is_visit[cur.second]) {
                    break;
                }
                is_visit[cur.second] = true;
                MST_edge.push_back(cur.first.second);
                for(pii p:graph[cur.second]){
                    if(!is_visit[p.first]){
                        pq.push(MP(MP(edge[p.second].second,p.second),p.first));
                    }
                }
            }
    }
    return MST_edge;

}

bool cmp(piii a,piii b){
    return a.second > b.second;
}

long long dfs(graph_T &graph,vector<piii> &mst_edge,int cur){
    
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    graph_T graph(n+1);
    vector<piii> edge(m);
    for(int i = 0;i<m;i++){
        int a,b,w;
        cin>>a>>b>>w;
        graph[a].push_back(MP(b,i));
        graph[b].push_back(MP(a,i));
        edge[i] =  MP(MP(a,b),w);
    }
    
    vector<int> mst_edge = mst(n,graph,edge);
    vector<piii> True_mst_edge(mst_edge.size());
    for(int i=0;i<mst_edge.size();i++){
        True_mst_edge[i] = edge[mst_edge[i]];
    }
    sort(True_mst_edge.begin(),True_mst_edge.end(),cmp);
    for(piii p: True_mst_edge){
        for(pii q: graph[p.]){

        }
    }

    return 0;

}