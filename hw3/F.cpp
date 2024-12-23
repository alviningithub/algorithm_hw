#include<iostream>
#include<vector>
#include<utility>
#include<queue>
using namespace std;

#define pii pair<int,int>
#define MP make_pair

void dfs(int cur,int closest,vector<vector<int>> &graph, vector<pii> &vertex,vector<bool> &is_visited , vector<int> &node_snake){
    is_visited[cur] = true;
    //snk_id are here ,walk 0 step to arrived here 
    if(node_snake[cur] >= 0){
        vertex[cur] = MP(0,node_snake[cur]);
    } 
    //dfs to the next node
    for(int i : graph[cur]){
        if(!is_visited[i]){
            dfs(i,closest,graph,vertex,is_visited,node_snake);
            // move the snake
            if(vertex[cur].first > vertex[i].first + 1 && vertex[i].first +1  <= closest){
                vertex[cur] = vertex[i]; vertex[cur].first++;
            }else if(vertex[cur].first == vertex[i].first+1 && vertex[cur].second > vertex[i].second){
                vertex[cur] = vertex[i]; vertex[cur].first++;
            }
        }     
    }
}

void dfs2(int cur,int update_upper_bound,vector<vector<int>> &graph, vector<pii> &vertex,vector<bool> &is_visited , vector<int> &node_snake , vector<bool> &is_update){
    is_visited[cur] = true;
    int next_level_bound = update_upper_bound;
    if(update_upper_bound >= vertex[cur].first && vertex[cur].second != -1 && !is_update[vertex[cur].second]){
        node_snake[cur] = vertex[cur].second;
        next_level_bound = vertex[cur].first;
        is_update[vertex[cur].second] = true;
    }else if(update_upper_bound >= vertex[cur].first && vertex[cur].second != -1 && is_update[vertex[cur].second]){
        next_level_bound = vertex[cur].first;
    }
    for(int i:graph[cur]){
        if(!is_visited[i]){
            dfs2(i,next_level_bound,graph,vertex,is_visited,node_snake,is_update);
        }
    }

}


void clear(queue<pii> &q){
    while(!q.empty()){
        q.pop();
    }
}


int main(){
    //input edges and snakes initial pos
    int n,k,h;
    cin>>n>>k>>h;
    vector<vector<int>> graph(n+1);
    vector<int> node_snake(n+1,-1);
    vector<pii > vertex(n+1,MP(n+5,-1));
    vector<bool > is_visited(n+1,false);
    vector<int> snake_eat(k,0);
    vector<bool> is_update(k,false);
    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    } 

    for(int i=0;i<k;i++){
        int a;
        cin>>a;
        node_snake[a] = i;
    }

    queue<pii> q;
    for(int i=0;i<h;i++){
    //input ith apple
    int apple_pos ;
    cin>>apple_pos;
    //bfs the distance
    //initial bfs data
    int closest = 0;
    clear(q);
    fill(is_visited.begin(),is_visited.end(),false);
    q.push(MP(0,apple_pos));

    //start bfs
    while(!q.empty()){
        auto [dis,node] = q.front(); q.pop();
        is_visited[node] = true;

        if(node_snake[node] >= 0){
            closest = dis;
            break;
        }
        
        for(int i: graph[node]){
            if(!is_visited[i]){
                q.push(MP(dis+1,i));
            }
        }
    }
    //dfs pull the snakes
    fill(is_visited.begin(),is_visited.end(),false);
    fill(vertex.begin(),vertex.end(),MP(n+5,-1));
    dfs(apple_pos,closest,graph,vertex,is_visited,node_snake);
    
    //update the snake pos
    fill(is_visited.begin(),is_visited.end(),false);
    fill(node_snake.begin(),node_snake.end(),-1);
    fill(is_update.begin(),is_update.end(),false);
    dfs2(apple_pos,n+5,graph,vertex,is_visited,node_snake,is_update);
    
    //update apples 
    snake_eat[node_snake[apple_pos]]++;
    }

    vector<int> snake_last_pos(k);
    for(int i=1;i<=n;i++){
        if(node_snake[i] >= 0){
            snake_last_pos[node_snake[i]] = i;
        }
    }

    for(int i=0;i<k;i++){
        cout<<snake_last_pos[i]<<" "<<snake_eat[i]<<"\n";
    }cout<<endl;
    



}