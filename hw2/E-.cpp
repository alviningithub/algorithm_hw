#include<iostream>
#include<vector>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> v(n);
        for(int i=0;i<n;i++){
            cin>>v[i];
        }
        long long sum = 0;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(v[i] > v[j]) 
                    sum++;
            }
        }

        cout<<sum<<endl;
    }
}
/*
1
15
1 5 3 4 8 7 6 1 10 12 14 15 13 2 4
*/