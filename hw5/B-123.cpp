#include<iostream>
#include<vector>
using namespace std;

struct car{
    int pos;
    int c;
    int d;
};

struct range{
    long long s_pos;
    long long e_pos;
};

void rec_pick(int n,int m,long long  &ans,long long  cur,long long  cur_max,long long table[10][10],int used[]){
    if(cur == m){
        ans = min(ans,cur_max);
        return ;
    }
    for(int i=0;i<n;i++){
        if(!used[i]){
            used[i] = 1;
            
            rec_pick(n,m,ans,cur+1,max(cur_max,table[i][cur]),table,used);
            used[i] = 0;
        }
    }

}


int main(){
    int n,m;
    cin>>n>>m;
    vector<car> cars(n);
    vector<long long >passenger(m);
    for(int i=0;i<n;i++){
        cin>>cars[i].pos>>cars[i].c>>cars[i].d;
    }
    for(int i=0;i<m;i++){
        cin>>passenger[i];
    }
    long long table[10][10];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            table[i][j] = (long long)cars[i].c * abs((long long )cars[i].pos - passenger[j]) + (long long )cars[i].d;
        }
    }
    long long ans = 4*1e18;
    int used[10] = {};
    rec_pick(n,m,ans,0,0,table,used);
    cout<<ans<<endl;
    return 0;

}