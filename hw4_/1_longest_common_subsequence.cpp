#include<bits/stdc++.h>
using namespace std;

int dp[10000005] = {};
//add some new
int LCS(const string& s1,const string& s2,int n1,int n2){
    fill(dp,dp+10000005,0);
    int dp_left_down = 0 , dp_tmp ;
    for(int i=0;i<n1;i++){
        dp_left_down = 0;
        for(int j=0;j<n2;j++){
            dp_tmp = dp[j + 1];
            if(s1[i] == s2[j]) {
                dp[j + 1] =  dp_left_down +1 ;
            }else {
                dp[j + 1] = max(dp[j+1],dp[j]);
            }
            dp_left_down = dp_tmp;
        }
    }
    return dp[n2];

}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        string s1,s2;
        cin>>s1>>s2;
        int ans = LCS(s1,s2,n,m);
        cout<<ans<<"\n";
    }
    
}