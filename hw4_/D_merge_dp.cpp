#include<iostream>
using namespace std;

long long  dp[5004][5004]={};
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    int base[5004];
    
    for(int i=0;i<n;i++){
        cin>>base[i];
    }
    int turn;//0 is faker 1 is chovy
    if(n%2 == 0){//chovy's turn
        for(int i=0;i<n;i++){
            dp[i][i] = -base[i];
        }
        //next if faker
        turn = 0;
    }else {//faker's turn
        for(int i=0;i<n;i++){
            dp[i][i] = base[i];
        }
        turn = 1; // next is chovy 
    }
    for(int k = 2 ; k <= n ; k++){
        for(int i=0;i+k-1<n ;i++){
            int front = i;
            int back = i + k -1;
            if(turn == 0){
                dp[front][back] = max(dp[front][back -1 ] + base[back],dp[front+1][back] + base[front]);
            }else {
                dp[front][back] = min(dp[front][back -1] - base[back],dp[front+1][back]-base[front]);
            }
        }
        turn = !turn;
    }
    cout<<dp[0][n-1]<<endl;
}