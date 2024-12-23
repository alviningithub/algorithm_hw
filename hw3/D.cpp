#include<iostream>
#include <utility>
#include<algorithm>
#include<vector>
using namespace std;

#define piii pair<int,pair<int,int>>
#define pii pair<int,int>
#define MP make_pair
#define N 100001
#define Q_max = 100001
#define logM 318



int fnd(int a,int dsu[]){
    if(dsu[a] == a) return a;
    dsu[a] = fnd(dsu[a]);
    return dsu[a];
}

void uni(int a, int b,int dsu[]){
    int root_a = fnd(a);
    int root_b = fnd(b);
    dsu[root_a] = root_b;
}
//L R for m Q for n
void binary_serach_with_array(int L,int R,int Q, int query_search[],vector<pii > &query , vector<int > &ans,vector<piii> &edges,vector<int> dsu,int last_time ){
    //return if L == R
    if(L==R) {
        for(int i=0;i<Q;i++){
            ans[query_search[i]] = edges[L].first;
        }
        return;
    }
    if(Q == 0) return ;
    //complete dsu
    int mid = (R-L)/2 + L;
    for(int i = last_time+1;i<=mid;i++){

    }

    //query and rearrange

    //recursive

}


int main(){
    int n,m;
    cin>>n>>m;
    vector<piii> edges(m+1);
    for(int i=1;i<=m;i++){
        int a,b,w;
        cin>>a>>b>>w;
        edges[i] = MP(w,MP(a,b));
    }
    sort(edges.begin()+1,edges.end(),greater<piii>());
    int Q;
    cin>>Q;
    vector<pii> querys(Q);
    for(int i=0;i<Q;i++){
        cin>>querys[i].first>>querys[i].second;
    }
    vector<int > ans(Q);
    int query_search[Q];
    binary_search_with_array();
    




}