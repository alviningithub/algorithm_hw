#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define LLI long long int
#define mod 998244353

vector<int> temp_array;

LLI merge_inversion(int L,int R,vector<int> &a){
    //base
    if(R <= L) return 0;

    //recursive
    LLI left_ans,right_ans;
    int mid = (R-L)/2+L;
    left_ans = merge_inversion(L,mid,a);
    right_ans = merge_inversion(mid+1,R,a);

    //merge
    int left_point = L, right_point = mid+1 , temp_point =0;
    LLI cross_inversion_point = 0;
    while(left_point <= mid && right_point <= R){
        if(a[left_point] > a[right_point]){
            temp_array[temp_point] = a[left_point];
            temp_point++,left_point++;
            cross_inversion_point += (R - right_point +1 );
        }else{
            temp_array[temp_point] = a[right_point];
            temp_point++,right_point++;
        }
    }

    for(int i = left_point ; i <= mid ; i++){
        temp_array[temp_point] = a[i];
        temp_point++;
    }

    for(int i=right_point; i<=R ; i++){
        temp_array[temp_point] = a[i];
        temp_point++;
    }

    for(int i = L; i<=R;i++){
        a[i] = temp_array[i-L];
    }

    //return
    return (left_ans + right_ans + cross_inversion_point ) % mod;
    //return (left_ans + right_ans + cross_inversion_point ) ;
    
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
   
    //input
    int n;
    LLI k;
    cin>>n>>k;
    vector<int> a(n),origin(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
        origin[i] = a[i];
    }

    //initialize
    temp_array.resize(n);

    //inversion point
    LLI n_inversion_point = 0;
    n_inversion_point = merge_inversion(0,n-1,a);

    //prepare set and rotate_result
    vector<long long  > rotated_result(n);
    rotated_result[0] = n_inversion_point;

    //caculate each rotated_result
    // 9999998888876543210 rotate 8
    // ++++++00000--------
    //       ^             lower_bound
    //            ^        upper_bound

    // 5 4 3 2 1^

    long long increase ,decrease;
    for(int i=1;i<n;i++){
        decrease = a.end() - upper_bound(a.begin(),a.end(),origin[i-1],greater<int>());
        increase = lower_bound(a.begin(),a.end(),origin[i-1],greater<int>()) - a.begin();
       // cout<< decrease<<" "<<increase <<endl;
        rotated_result[i] = (rotated_result[i-1] - decrease + increase ) %mod;
    }

    //count between rotate
    LLI between_rotate= 0;
    int current  = a[n-1];
    LLI count_same = 0;
    for(int i=n-1;i>=0;i--){
        if(a[i] == current){
            count_same ++;
            continue;            
        }
        between_rotate += (((i+1)*count_same%mod)%mod);
        between_rotate %= mod;
        current = a[i];
        count_same = 1;
    }

    LLI n_round = 0 ; // sigma rotate_result[0~n-1]
    for(int i=0;i<n;i++)
        n_round = (n_round + rotated_result[i]) % mod;
    

    //construct result 
    // k / n n_round + k mod n each round + k-1*k/2 * between rotate 

    LLI ans = 0;
    ans = (((k/n) % mod) * n_round) % mod ;

    for(int i=0; i < k % n ; i++){ // remain round 
        ans = (ans + rotated_result[i]) % mod ;
    }

    ans += (  (  ( ( ( (k % mod )*((k-1) % mod) ) % mod )*499122177 ) % mod ) * between_rotate) % mod ;
    ans = (ans %mod + mod ) % mod;

    cout<<ans <<endl;
    

    //8 7 6 5 4 4 3 1 1
    
    

}