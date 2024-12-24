#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;

#define piii pair<int,pair<int,int>>

int cmp(piii a,piii b){
    long long tmpa,tmpb;
    tmpa = a.second.second * b.second.first;
    tmpb = b.second.second * a.second.first;
    if(tmpa != tmpb){
        return tmpa > tmpb;
    }
    return a.first < b.first;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<piii> v;
        v.resize(n);
        for(int i=0;i<n;i++){
            v[i].first = i + 1;
        }
        for(int i=0;i<n;i++){
            cin>>v[i].second.first;
        }
        for(int i=0 ; i< n;i++){
            cin>>v[i].second.second;
        }
        sort(v.begin(),v.end(),cmp);
        for(int i=0;i<n;i++){
            cout<<v[i].first<<" ";
        }
        cout<<"\n\n";

    }
    
}