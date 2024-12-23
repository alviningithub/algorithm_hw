#include<iostream>
#include<vector>
#include<utility>
using namespace std;

typedef  long long  ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define MP make_pair
#define mod 998244353

int fast_pow(int a,int e){
    long long result = 1;
    long long mul = a;
    while(e > 0){
        if(e & 1) {
            result *= mul;
            result %= mod;
        }
        mul = (mul*mul) % mod;
        e >>= 1;
    }

    return result;
}

int max(int a,int b){
    return (a>b)?a:b;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie();
    long long a,b,c;
    cin>>a>>b>>c;
    vector<pll> va(max(a,c) + 1,MP(0,0));
    vector<pll> vb(max(b,c) + 1,MP(0,0));

    for(int i=1;i<=a;i++){
        long long  n = a/i;
        va[i].first = n;
        va[i].second = (((n*i) %mod * (n+1)) %mod) * fast_pow(2,mod-2);
        va[i].second %= mod;
    }

    for(int i=1;i<=b;i++){
        ll n = b/i;
        vb[i].first = n;
        vb[i].second = (((n*i) %mod * (n+1)) %mod) * fast_pow(2,mod-2);
        vb[i].second %= mod;
    }

    for(int i=1;i<=c;i++){
        
    }


    return 0;


}