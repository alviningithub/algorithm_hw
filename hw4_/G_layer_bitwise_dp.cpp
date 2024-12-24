#include<iostream>

using namespace std;

typedef long long ll;
#define mod 998244353

bool check_aval(int bits,int n,int obs[]){
    int mask = 3;
    for(int i=0;i<n;i++){
        if((bits & mask) == 3){
            return false;
        }
        if( (bits & 1) == 1 && obs[n-i] == 1){
            return false; 
        } 
        bits >>= 1;
    }
    return true;
}



ll find(int constrain,int bits,int ith_turn,int n,int last_dp[]){
    ll ans = 0;
    if(ith_turn == n)
        //find a valid bitset
        return last_dp[bits];
    //try to put a king here 
    //from right to left
    if( ith_turn == 0 && (constrain & 3) == 0 ) { // there is no king on the right most two square
        ans += find(constrain,bits|(1<<ith_turn),ith_turn + 1,n,last_dp) % mod ;
    }
        // bit on the right don't have king && there is no kings on constrain square ith - 1 , ith , ith+1 
    if(  ith_turn != 0 && !(bits & 1<<(ith_turn-1) ) && !(constrain &  7 << (ith_turn - 1) )){
        ans = find(constrain,bits|(1<<ith_turn),ith_turn + 1,n,last_dp) % mod;
    }
    ans += find(constrain,bits,ith_turn + 1,n,last_dp)  ;
    ans = ans %mod;
    return ans;
}



int main(){
    int n;
    cin>>n;
    int dp[2][(1<<n)] = {};
    int obs[n+2][n+2] = {};
    int k;
    cin>>k;
    for(int i=0;i<k;i++){
        int a,b;
        cin>>a>>b;
        obs[a][b] = 1;
    }

    //dp init
    int layer = 1; 
    int cur_row = layer % 2;
    for(int i=0;i<(1<<n);i++){
        if(check_aval(i,n,obs[1])){
            dp[cur_row][i] = 1; 
        }
        
    }
    layer ++;
    for(;layer <=n;layer++){
        cur_row = layer %2;
        for(int j=0; j<(1<<n); j++){
            //dp[j][cur_row] = sum(dp[*][!cur_row]);
            if(!check_aval(j,n,obs[layer])){
                dp[cur_row][j] = 0;
                continue;
            } 
            dp[cur_row][j] = find(j,0,0,n,dp[!cur_row]);
        }   
    }
    ll ans = 0;
    for(int i=0;i<(1<<n) ;i++){
        ans = (ans + dp[cur_row][i]) % mod;
    }
    cout<<ans;

}