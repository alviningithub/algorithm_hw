#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

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

bool cmp2(range a,range b){
    if(a.s_pos != b.s_pos){
        return a.s_pos < b.s_pos;
    }return a.e_pos < b.e_pos;
}

class cmp{
public:
    bool operator()(range a,range b){
    if(a.e_pos != b.e_pos){
        return a.e_pos > b.e_pos;
    }return a.s_pos > b.s_pos;
    }

};




int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    vector<car> cars(n);
    vector<long long > passenger(m);
    for(int i=0;i<n;i++){
        cin>>cars[i].pos>>cars[i].c>>cars[i].d;
    }
    for(int i=0;i<m;i++){
        cin>>passenger[i];
    }
    sort(passenger.begin(),passenger.end());

    //binary search the ans
    long long  l = 0 , r = 5 * (1e18);

    while(l < r){
        long long mid = (r - l) /2 + l;
        //check if every passenger have a car
        vector<range> ranges(n);
        for(int i=0;i<n;i++){
            long long time_left = mid - cars[i].d;
            // there is no time left 
            if(time_left < 0){
                ranges[i].s_pos = 2 * 1e9; //impossible
                ranges[i].e_pos = -1;
            }else{
               // still some time left , finding the ragne
                long long max_move_dis = time_left / cars[i].c;
                while((max_move_dis + 1)* cars[i].c <= time_left ) max_move_dis++;
                while((max_move_dis )* cars[i].c > time_left) max_move_dis --;
                ranges[i].s_pos = (long long)cars[i].pos - max_move_dis;
                ranges[i].e_pos = (long long)cars[i].pos + max_move_dis; 
            }
            
        }
        sort(ranges.begin(),ranges.end(),cmp2);
        //check if all the passenger are taken
        int counter = 0;
        bool success = true;
        priority_queue<range,vector<range>,cmp> pq;
        for(int i=0;i<m ;i++){
            //push the uber that avaliable by i
            while(counter < n && (ranges[counter].s_pos <= passenger[i] )){
                pq.push(ranges[counter]);
                counter++;
            }
            //pop the ubers which are out of date
            while(!pq.empty() && !(pq.top().s_pos <= passenger[i] && passenger[i] <= pq.top().e_pos)){
                pq.pop();
            }
            // no uber avaliable stop
            if(pq.empty()){
                success = false;
                break;
            }
            // pop the first avaliable uber 
            pq.pop();
        }

        //counter == m means every passenger are taken 
        if(success){
            r = mid ;
        }else {
            l = mid + 1;
        }
    }
    
    cout<<l<<endl;
    
    return 0;
}

