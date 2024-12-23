#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n , x,y;
    cin>>n>>x>>y;
    double p[n] , q[n];
    for(int i=0;i<n;i++){
        cin>>p[i];
    }
    for(int i=0;i<n;i++){
        cin>>q[i];
    }
    double dp[x+1][y+1] = {};
    
    for(int i=0;i<n;i++)
        for(int j = x;j >=0;j--){
            for(int k = y; k >= 0 ;k--){
                if(j >0 && k > 0){
                    dp[j][k] = max( max(dp[j][k] , dp[j-1][k] + p[i]) , max(dp[j][k-1] + q[i] , dp[j-1][k-1] + (1 - (1-p[i])*(1-q[i])) ));
                }else if(j > 0){
                    dp[j][k] = max(dp[j][k] , dp[j-1][k] + p[i]);
                }else if(k > 0){
                    dp[j][k] = max(dp[j][k] , dp[j][k-1] + q[i]);
                }
                    
            }
        }
    
    double max_val = 0;
    for(int i=0;i<=x;i++){
        for(int j=0;j<=y;j++){
            max_val = max(max_val,dp[i][j]);
        }
    }
    cout<<fixed<<setprecision(10)<<max_val;
}