#include<iostream>
#include<vector>
#include<queue>
#include<utility>

using namespace std;

#define pli pair<long long ,int >
#define pii pair<int,int>
#define MP make_pair

long long _min(long long a,long long b){
    return (a>b)? b:a;
}

//relax p.first from cur 
void relaxzation(pii p,long long cur_dis , vector<long long> &dis,priority_queue<pli,vector<pli>,greater<pli>> &pq,vector<bool> &is_visit ){
    if(!is_visit[p.first] && dis[p.first] > cur_dis + p.second){
        dis[p.first] = cur_dis + p.second;
        pq.push(MP(cur_dis + (long long )p.second,p.first));
    }
}

void dijkstra(int source,int n ,vector<long long> &dis,vector<vector<pii> > &graph,int discount[]){ 
    for(int i=0;i<=16*n;i++) dis[i] = 1e18;
    dis[source]= 0;
    int mapping[10] = {0,0,0,0,2,1,0,2,1,0};
    vector<bool> is_visit(16*n+1,false);                                         // modify to 16n
    priority_queue<pli,vector<pli>,greater<pli>> pq;    //(distance , next point)                    
    pq.push(MP(0,source));                                                  
    long long cur_dis;
    int cur;
    for( int i=1; i<=16*n; i++){                                               //modify to 16*n
        //find the shortest point which unvisited
        if(pq.empty()) break;
        do{
            cur_dis = pq.top().first;
            cur = pq.top().second;
            pq.pop();
        }while(is_visit[cur] && !pq.empty());                                              //if empty and isvisit break
        if(is_visit[cur]) break;
        //fill the value
        is_visit[cur] = true;
        dis[cur] = cur_dis;
        //relaxzation
        int true_cur = (cur-1)%n+1;
        int state = (cur-1)/n;
        for(pii p: graph[true_cur]){
            pii q;
            //consder the discount edge original node is p.first %(n-1)+1 the case code is (n-1)/n
            // 0:"" , 1: "F"
            switch(state){
            case 0:
                relaxzation(p,cur_dis,dis,pq,is_visit);
                for(int i=0;i<=2;i++){
                    pii q = MP(p.first+n*(i+1),p.second/discount[i]);
                    relaxzation(q,cur_dis,dis,pq,is_visit);
                }
                break;
            case 1: case 2: case 3:
                 q = MP(p.first + state*n,p.second);
                relaxzation(q,cur_dis,dis,pq,is_visit);
                for(int i=1;i<=2;i++){
                    int coupon = (state - 1 + i) % 3; //1 ->2 1->3 2->3 2->1 3->1 3 ->2
                    int next_vertex = p.first + 3*n + i*n + (state-1) * 2* n;
                    q = MP(next_vertex,p.second/discount[coupon]);
                    relaxzation(q,cur_dis,dis,pq,is_visit);
                }
                break;     
            case 4:     case 5:    case 6:       case 7:     case 8:      case 9:
                q = MP(p.first + state*n,p.second);
                relaxzation(q,cur_dis,dis,pq,is_visit);
                q = MP(p.first + 6*n + state*n,p.second/discount[mapping[state]] );
                relaxzation(q,cur_dis,dis,pq,is_visit);
                break;
            case 10:   case 11:    case 12:   case 13:   case 14:  case 15:
                q = MP(p.first + state*n,p.second);
                relaxzation(q,cur_dis,dis,pq,is_visit);
                break;
            default:
                cout<<"fx"<<endl;
            }                                       
        }
    }

}

int main(){
    int n,m,k;
    cin >>n>>m>>k;
    int discount[3] = {1,1,1};
    for(int i=0;i<k;i++) cin >> discount[i] ; // input discount
   
    //input graph
    vector< vector<pii> > graph(n+1);
    int a,b,w;
    for(int i=0;i<m;i++){
        cin>>a>>b>>w;
        graph[a].push_back(MP(b,w)); //(dest,weight)
        graph[b].push_back(MP(a,w));
    }

    //running dijkstra algorithm
    vector<long long > dis(16*n+1,1e18);
    dijkstra(1,n,dis,graph,discount);
    long long ans = dis[n];
    for(int i = 0 ; i<=15;i++){
        ans = _min(ans,dis[i*n+n]);
    }

    if(ans >= 1e18 -1){
        cout<<-1;
    }else {
        cout<<ans;
    }

}


/*
initial value set 1e9
priority queue and vector update simutanisely
(int ) -> (long long )
*/