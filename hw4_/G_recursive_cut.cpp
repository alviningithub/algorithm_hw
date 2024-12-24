#include<iostream>
using namespace std;

#define mod 998244353

int board[26][26] = {};
int obstacle[26][26] = {};

bool check_occupy(int x, int y)
{
    for(int i=-1 ; i<=1;i++){
        for(int j=-1;j<=1;j++){
            if(board[i+x][j+y]){
                return 1;
            }
        }
    }
    return 0;
}
void solve(int x,int y,int n,int &total){
    if(x ==n && y == n ){
        if(obstacle[n][n] || check_occupy(x,y)){
            return;
        }
        //putable
        total ++;
        total %= mod;
        return ;
    }
    if(check_occupy(x,y) || obstacle[x][y]){
        if(y == n){
            solve(x+1,1,n,total);
        }else {
            solve(x,y+1,n,total);
        }
        return;
    }
    //putable
    total++;
    total %= mod;
    board[x][y] = 1;
    if(y == n){
        solve(x+1,1,n,total);
    }else {
        solve(x,y+1,n,total);
    }
    board[x][y] = 0;
    if(y == n){
        solve(x+1,1,n,total);
    }else {
        solve(x,y+1,n,total);
    }
}

int main(){
    int n,k;
    cin>>n>>k;
    for(int i=0;i<k;i++){
        int a,b;
        cin>>a>>b;
        obstacle[a][b] = 1;
    }
    int ans = 0;
    solve(1,1,n,ans);
    ans += 1;
    ans %= mod;
    cout<<ans  <<endl;

}