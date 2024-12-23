#include <iostream>
#include <algorithm>
#include<vector>
#include<utility>
#include<cmath>

using namespace std;

typedef long long LLI;
#define MP make_pair
#define PAUSE printf("Press Enter key to continue..."); fgetc(stdin);

LLI distance(int x1,int x2,vector<LLI> &v){
    // if(x2 > x1)
    //     return sqrt(   (double)  ( (long long )(x2-x1+1)*(x2-x1+1) + (v[x2] - v[x1-1])*(v[x2] - v[x1-1]) )   );
    // return sqrt(   (double)  ( (long long )(x1-x2+1)*(x1-x2+1) + (v[x1] - v[x2-1])*(v[x1] - v[x2-1]) )   );
    if( abs(v[x1] - v[x2]) > 1e8*2+1 ) return 1e16*4+5; 
    return    ( (long long )(x1-x2)*(x1-x2) + (v[x1] - v[x2])*(v[x1] - v[x2]) )   ;
    
}

LLI square(LLI a){
    if(a > 1e8*2+1) return 1e16*4+5;
    else return a*a;
}

pair<int,int> shortest_point(int L,int R,vector<LLI> &v){
    //if(R - L < 1) {cout<<"bad_ans";exit(0);}
    if(R-L == 2) return MP(L,R);
    pair<int,int> a,b; 
    int mid = (R-L)/2+L;
    if(R-L <6) {
        a = shortest_point(L,L+2,v);
        b = shortest_point(R-2,R,v);
    }else {
        a = shortest_point(L,mid,v);
        b = shortest_point(mid+1,R,v);
    }
    double d2;

    // put all dx < d into possible_point
    d2 = min(distance(a.first,a.second,v),distance(b.first,b.second,v));
    vector<pair<LLI,int>> possible_point(R-L+1);
    int len = 0;
    for(int i = L; i <= R;i++){
        if( (i-mid)*(i-mid)  < d2  ){
            possible_point[len]=(MP(v[i],i));
            ++len;        
        } 
    }

    // //initialize min_pts
    // pair<int,int> min_pts;
    // min_pts.first = possible_point[0].second;
    // for(int i=1;i<len;i++){
    //     if(abs(min_pts.first - possible_point[i].second) > 1){
    //         min_pts.second = max(possible_point[i].second,min_pts.first);
    //         min_pts.first = min(possible_point[i].second,min_pts.first);
    //         break;
    //     }
    // }
    //sort by y val
    sort(possible_point.begin(),possible_point.begin()+len);

        pair<int,int> min_pts;
    if( abs(possible_point[0].second -possible_point[1].second) != 1 ) {
        min_pts.first = min(possible_point[0].second,possible_point[1].second);
        min_pts.second = max(possible_point[0].second,possible_point[1].second);
    }else if( abs(possible_point[1].second - possible_point[2].second) != 1 ) {
        min_pts.first = min(possible_point[1].second,possible_point[2].second);
        min_pts.second = max(possible_point[1].second,possible_point[2].second);
    }else  {
        min_pts.first = min(possible_point[0].second,possible_point[2].second);
        min_pts.second = max(possible_point[0].second,possible_point[2].second);
    }

    //find min dis among possible point
    


    LLI min_dis = 1e18;
    // if(L == 7 && R == 12) 
    //     cout<<"error start\n";
    for(int i=0 ; i < len ; i++){
        for(int j = i + 1 ; j< len;j++){
            if(square(possible_point[j].first - possible_point[i].first)  > d2  ) break;
            if(abs(possible_point[i].second - possible_point[j].second) == 1) continue;
            pair<LLI,int> p1,p2;
            if(possible_point[i].second > possible_point[j].second) {
                p1 = possible_point[j];
                p2 = possible_point[i];
            }
            else{
                p1 = possible_point[i];
                p2 = possible_point[j];
            }
            LLI tmpd = distance(p1.second,p2.second,v);
            if(tmpd < min_dis){
                min_dis = tmpd;
                min_pts = MP(p1.second,p2.second);
            }
        }
    }

    //return val
    // if(min_pts.first == 0 && min_pts.second ==0) 
    //     cout<<"error occur\n";
    if(distance(a.first,a.second,v) < distance(b.first,b.second,v) && distance(a.first,a.second,v) < distance(min_pts.first,min_pts.second,v)){
       return a;             
    } else if(distance(b.first,b.second,v) < distance(a.first,a.second,v) && distance(b.first,b.second,v) < distance(min_pts.first,min_pts.second,v)){
        return b;
    }
    return min_pts;
   
}





int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    vector<LLI > v(n+1);
    v[0]=0;
    for(int i=1;i<=n;i++){
        LLI tmp;
        cin>>tmp;
        v[i] = v[i-1] + tmp;
    }
    pair<int,int> p;
    // cout<<"start to recursive"<<endl;
    p = shortest_point(0,n,v);
    
    cout<<p.first+1<<" "<<p.second<<endl;

}

/*
bug log

distance function value exceed long long 
find the pair that isnt neighbor can derect ignore the comparison between it 
didnt initialize the min_pts
the base case need to be firm

*/