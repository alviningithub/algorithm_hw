#include<iostream>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,q;
    cin>>n>>q;
    int a[200005];
    long long total=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        total += a[i];
    }
    for(int i=0;i<q;i++){
        int k,x;
        cin>>k>>x;
        total -= a[k];
        total += x;
        a[k] = x;
        cout<<total<<'\n';
    }

    
}