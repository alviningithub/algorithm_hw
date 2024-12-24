#include<iostream>
#include<tuple>
#include<bitset>
using namespace std;

#define get(a,b) get<b>(a)

bool check_aval(int bits,int n,int obs[]){
    int mask = 3;
    for(int i=0;i<n;i++){
        if( (bits & mask) == 3){
            return false;
        }
        if(bits & 1 == 1 && obs[n-i] == 1){
            return false; 
        } 
        bits >>= 1;
    }
    return true;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n = 4;
    cin>>n;
    int dp[5] = {};
    cout<<bitset<5>(n)<<endl;
    cout<<check_aval(n,5,dp);
    




}