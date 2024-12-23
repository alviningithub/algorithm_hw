#include<iostream>
#include <algorithm>
#include<vector>
using namespace std;
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

int main(){
    long long a,b,c;
    cin>>a>>b>>c;
    // vector<bool> visit(a*b+1,false);
    long long quantity = 0, sum  = 0;
    for(long long k=1;k<=c;k++){
        for(long long i=1;i<=a;i++){
            for(long long j=1;j<=b;j++){
                if(__gcd(i*j,k) == 1){
                    quantity ++;
                    quantity %= mod;
                    sum += ((i*j * fast_pow(k,mod-2)) % mod);
                    sum %= mod;
                }
                
            }
        }
    }
    cout<<quantity<<" "<<sum<<endl;;

}