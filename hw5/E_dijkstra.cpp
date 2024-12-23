#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#include<algorithm>
using namespace std;

typedef pair<int,int> pii ;
typedef pair<long long,int> pli;
#define MP(a,b) make_pair(a,b)

vector<long long> dijkstra(int N,int source,vector<vector<pii>> &graph){
    vector<bool> visited(N+1,false);
    priority_queue<pli,vector<pli>,greater<pli>> pq;
    vector<long long> dis(N+1,1e18);
    dis[source] = 0;
    pq.push(MP(0,source));
    for(int i= 1;i<=N;i++){
        pli path_pair;
        if(pq.empty()) break;
        do
        {
            path_pair = pq.top();
            pq.pop();
        } while (!pq.empty() && visited[path_pair.second]);
        if(pq.empty() && visited[path_pair.second]) break;
        auto [distance,cur] = path_pair;
        visited[cur] = true;
        for(pii p:graph[cur]){
            if(!visited[p.first]){
                if(dis[p.first] > dis[cur] + p.second){
                    dis[p.first] = dis[cur] + p.second;
                    pq.push(MP(dis[p.first],p.first));
                }
            }
        }        
    }

    return dis;
    
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
        }else if(op == 2){
            int u,v;
            cin>>u>>v;
            vector<long long> distance = dijkstra(n,u,graph);
            cout<<distance[v]<<"\n";
        }else{
            cout<<"wrong operation ,please try again\n";
        }
    }
    
    return 0;
    
}