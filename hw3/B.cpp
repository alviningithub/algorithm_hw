#include<iostream>
#include<stack>
#include <set>
using namespace std;

int max(int a,int b) 
{
    return (a>b)?a:b;
}

int main(){
    int n;
    cin>>n;
    set<int > z;
    int a[200005] = {};
    for(int i=1;i<=n;i++){
        cin>>a[i];
        //distinct test 
        if(z.find(a[i]) != z.end()) {
            cout<<-1;
            return 0;
        }else {
            z.insert(a[i]);
        }
    }
    a[0] = 1e9+7;
    
    //preorder check
    stack<int> check;
    int root = -1;
    for (int i = 1; i <= n; i++) {
        if (a[i] < root){
            cout<<-1;
            return 0;
        }
        while (!check.empty() && check.top() < a[i]) {
            root = check.top();
            check.pop();
        }
        check.push(a[i]);
    }

    //preorder to poseoder
    stack<int> s;
    stack<int > ancestor_left ;
    int cur_val,next_val;
    s.push(a[0]);
    ancestor_left.push(a[0]);
    for(int i=1;i<=n;i++){
        cur_val = a[i];
        if(cur_val < s.top()) {
            //left
            ancestor_left.push(s.top());
            s.push(cur_val);
        }else if(cur_val > s.top() && cur_val < ancestor_left.top() ){
            //right
            s.push(cur_val);
          
        }else {
            //ancestor 
            int last_ancestor;
            while(ancestor_left.top() < cur_val ){
                last_ancestor = ancestor_left.top();
                ancestor_left.pop();
            }
            while(s.top() < last_ancestor){
                cout<<s.top()<<" ";
                s.pop();
            }
            s.push(cur_val);
        }
    }

    //cout the last val and the stack
   
 
    while(s.size() > 1) {
        cout<<s.top()<<" ";
        s.pop();
    }

    return 0;
}