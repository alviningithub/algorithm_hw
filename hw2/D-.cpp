#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

typedef long long LLI;

double distance(int x1,int x2,vector<LLI> &v){
    // if(x2 > x1)
    //     return sqrt(   (double)  ( (long long )(x2-x1+1)*(x2-x1+1) + (v[x2] - v[x1-1])*(v[x2] - v[x1-1]) )   );
    // return sqrt(   (double)  ( (long long )(x1-x2+1)*(x1-x2+1) + (v[x1] - v[x2-1])*(v[x1] - v[x2-1]) )   );
    if( abs(v[x1] - v[x2]) > 1e8+10 ) return 1e8+5; 
    return sqrt(    (double) ( (long long )(x1-x2)*(x1-x2) + (v[x1] - v[x2])*(v[x1] - v[x2]) ) )  ;
    
}

int main(){
    int n;
    cin>>n;
    vector<long long > v;
    v.resize(n+1);
    v[0] = 0;
    for(int i=1;i<=n;i++){
        long long  tmp ;
        cin>>tmp;
        v[i] = v[i-1] + tmp;
    }
    double min_dis= 1e9;
    int a,b;
    for(int i=0;i<=n;i++){
        for(int j=i+2;j<=n;j++){
            if(distance(i,j,v) < min_dis){
                min_dis = distance(i,j,v);
                a =i;
                b = j;
            }
        }
    }
    cout<< a+1 << " "<<b<<endl;
}