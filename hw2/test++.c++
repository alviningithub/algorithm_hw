#include<iostream>
using namespace std;

#define mod 998244353


int main(){
    bool flag = 0;
    for(long long int i = 0 ; i< mod ;i+=2){
        if( (i * 499122177 ) %mod != i /2 ) cout<<i<<" ";
    }

    
}