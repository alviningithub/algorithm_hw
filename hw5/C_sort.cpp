#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;
 

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,x,y;
    cin>>n>>x>>y;
    double data[n];
    for(int i=0;i<n;i++){
        cin>>data[i];
    }
    double u;
    for(int i=0;i<n;i++){
        cin>>u;
    }
    sort(data,data+n);
    double ans = 0;
    for(int i=n-1;i>n-1-x;i--){
        ans += data[i];
    }
    cout<<fixed<<setprecision(10)<<ans<<endl;
}