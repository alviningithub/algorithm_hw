#include<iostream>
#include<vector>
#include<utility>
#include<queue>
using namespace std;

#define pii pair<int,int>
#define pli pair<long long ,int>
#define MP make_pair

long long mst(int n,int m,vector<vector<pii>> &graph){
    vector<bool> is_visit(n+1,false);
    vector<long long >  vertex(n+1,1e9+7);
    priority_queue<pli,vector<pli>,greater<pli>> pq;
    pq.push(MP(0,1));//distance 0 vertex 1
    for(int i=0;i<n;i++){
        long long cur,cur_val;
        if(pq.empty()) break;
        do{
            cur = pq.top().second;
            cur_val = pq.top().first;
            pq.pop();
        }while(!pq.empty()&& is_visit[cur]);
        if(pq.empty() && is_visit[cur]) break;
        is_visit[cur] = true;
        vertex[cur] = cur_val;
        for(pii edge : graph[cur] ){
            if(!is_visit[edge.first] && vertex[edge.first] > edge.second){
                pq.push(MP(edge.second,edge.first));
                vertex[edge.first] = edge.second;
            }
        }

    }

    //checking tree span successful
    bool fail = 0;
    for(int i=1;i<=n;i++){
        if(!is_visit[i]){
            fail = 1;
            break;
        }
    }
    if(fail) return -1;
    
    //return ans;
    long long ans = 0;
    for(int i=1;i<=n;i++){
        ans += vertex[i];
    }
    return ans;
    
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    vector<vector<pii> > graph(n+1);
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        graph[a].push_back(MP(b,c));
        graph[b].push_back(MP(a,c));
    }

    long long ans = mst(n,m,graph);
    cout<<ans<<endl;

}