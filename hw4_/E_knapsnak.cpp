#include<iostream>
#include<algorithm>
using namespace std;

int knapsnak(int n_item,int sz,int price[],int weight[],int quantity[]){
    int dp[sz+1] = {};
    for(int i=1;i<=n_item;i++){
        int num = min(quantity[i],sz / weight[i]); //how many stuf can I put into the bag if i just put items i
        for(int j = 1 ; num > 0 ;j *= 2){ // do 2^0 , 2^1 , 2^2 ...
            if (j > num) j = num; // do the rest
            num -= j;
            //create an item with price = j*price[i] and weight = j*weight[i]
            int cur_price = price[i] * j;
            int cur_weight = weight[i] * j;
            for(int k = sz ; k >=cur_weight; --k ){ 
                dp[k] = max(dp[k],dp[k - cur_weight] + cur_price);
            }
        }
    }
    return dp[sz];
}




int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,x;
    cin>>n>>x;
    int price[n+1] , caffenie[n+1],cups[n+1];
    for(int i= 1 ;i<=n;i++){
        cin>>price[i];
    }
    for(int j=1;j<=n;j++){
        cin>>caffenie[j];
    }
    for(int k=1;k<=n;k++){
        cin>>cups[k];
    }
    cout<<knapsnak(n,x,caffenie,price,cups);


}