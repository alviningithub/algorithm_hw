#include<iostream>
#include<vector>
#include<stack>
#include<utility>
using namespace std;


#define MP make_pair
vector<vector<bool >> is_visit(1003,vector<bool>(1003,false)) ;
stack<pair<int,int>> finish_time;
int direction[5] = {1,0,-1,0,1};

void dfs(int x,int y,int h[1003][1003],int n,int m){
    is_visit[x][y] = true;
    for(int i=0;i<4;i++){
        int x_next = x + direction[i];
        int y_next = y + direction[i+1];
        if(h[x][y] >= h[x_next][y_next] && is_visit[x_next][y_next] == false ){
            dfs(x_next,y_next,h,n,m);
        }
    }
    finish_time.push(MP(x,y));
}

void dfs2(int x,int y,int h[1003][1003],int n,int m){
    is_visit[x][y] = true;
    for(int i=0;i<4;i++){
        int x_next = x + direction[i];
        int y_next = y + direction[i+1];
        if(h[x][y] >= h[x_next][y_next] && is_visit[x_next][y_next] == false ){
            dfs(x_next,y_next,h,n,m);
        }
    }
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    int h[1003][1003] ;
    for(int i=0;i<=n+1;i++){
        h[i][0] = 1000000;
        h[i][m+1] = 1000000;
    }
    for(int j=0;j<=m+1;j++){
        h[0][j] = 1000000;
        h[n+1][j] = 1000000;
    }

    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>h[i][j];
    //topological sort
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(!is_visit[i][j]) dfs(i,j,h,n,m);
    

    // while(!finish_time.empty()){
    //     cout<<finish_time.top().first<<" "<<finish_time.top().second<<endl;
    //     finish_time.pop();
    // }
   


    //reset is_visit
    for(int i=0;i<=n+1;i++)
        for(int j=0;j<=m+1;j++)
            is_visit[i][j] = false;
    //count start
    int ans=0;
    while(!finish_time.empty()){
        if(!is_visit[finish_time.top().first][finish_time.top().second]){
            dfs(finish_time.top().first,finish_time.top().second,h,n,m);
            ans++;
            
        }
        finish_time.pop();
    }
    
            
    cout<<ans<<endl;
    





}