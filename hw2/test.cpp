#include<iostream>
using namespace std;

#define mod 998244353
//#define mod 2147483649

long long  fast_pow(int n, int p){
    if(p == 0) return 1;
    if(p == 1) return n;
    long long half = fast_pow(n,p/2);
    if( p % 2 ) 
        return ((half * half) % mod  * n) % mod;
    return (half* half )%mod;
}

int main(){
    cout<<fast_pow(2,mod - 2);
}