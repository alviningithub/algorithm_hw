#include<iostream>
#include<algorithm>
#include<utility>
#include<vector>
using namespace std;

typedef pair<int,pair<int,int>> pii;
typedef long long LLI;
#define MP make_pair



bool cmp(pii a, pii b){
    if(a.second.first  != b.second.first){
        return a.second.first > b.second.first;
    }else if(a.second.second % 2 != b.second.second%2){
        return a.second.second%2;
    }else if(a.second.second != b.second.second){
        return a.second.second < b.second.second;
    }
    return a.first < b.first;

}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //input 
    vector<pii> v;
    int n;
    cin>>n;
    int a,b;
    v.resize(n);
    for(int i=0;i<n;i++){
        cin>>a>>b;
        v[i] = MP(i+1,MP(a,b));
    }
    // for(int i=0;i<n;i++){
    //     cout<<v[i].first<<" "<<v[i].second.first<<" "<<v[i].second.second<<" \n";
    // }
    //sort with cmp
    sort(v.begin(),v.end(),cmp);
    //output
    for(pii p:v){
        cout<<p.first<<" ";
    }

}