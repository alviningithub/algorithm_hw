#include<iostream>
#include<algorithm>

using namespace std;

#define mod ((int)1e9+7)

struct matrix {
    int* mx;
    int sz;

    matrix(int size) {
        sz = size;
        mx = new int [size * size]; // mx[i][j] = mx[i*sz + j]
    }  

    ~matrix(){
        delete mx;
    }

    void identity(){
        for(int i=0; i< sz;i++){
            for(int j=0;j<sz;j++){
                if(i ==j ) mx[i*sz+j] = 1;
                else mx[i*sz+j] = 0;
            }
        } 
    }

    void zero(){
        for(int i = 0 ; i< sz;i++){
            for(int j=0 ; j< sz;j++){
                mx[i*sz+j] = 0;
            }
        }
    }

    matrix& operator=( const matrix &m) {
        if (this == &m) return *this;
        int min_sz = min(sz,m.sz);
        for(int i=0;i<min_sz;i++){
            for(int j=0;j<min_sz;j++){
                mx[i*sz+j] = m.mx[i*m.sz+j]; 
            }
        }
        return *this;
    }

    matrix operator*(matrix & m) const {
        matrix new_mx(sz);
        for(int i=0;i<sz;i++){
            for(int j=0;j<sz;j++){
                new_mx.mx[i*sz+j] = 0;
                for(int x = 0 ; x < sz ; ++x){
                    new_mx.mx[i*sz+j] =  (new_mx.mx[i*sz+j] +((long long)mx[i*sz+x] * m.mx[x*sz+j]) % mod ) % mod ;
                }
                
            }
        }
        return new_mx;
        
    }

    
    friend ostream& operator<<( ostream &os,const matrix &m)  {
        os<<"*---------------------------\n";
        for(int i=0;i<m.sz;i++){
            for(int j=0;j<m.sz;j++){
                os<<m.mx[i*m.sz+j]<<" ";
            }os<<"\n";
        }
        os<<"*---------------------------\n";
        return os;
    }

    friend istream& operator>>(istream &is, matrix &m) {
        for(int i=0;i<m.sz;i++){
            for(int j = 0 ; j < m.sz;j++){
                is>>m.mx[i*m.sz+j];
            }
        }
        return is;
    } 
};

/*
a b c 0
1 0 0 0
0 0 1 0
1 0 0 1
*/


inline void create_trans( int a,int b ,int c ,matrix &mx){
    for(int i=0;i<mx.sz;i++){
        for(int j=0;j<mx.sz;j++){
            mx.mx[i*mx.sz+j] = 0;
        }
    }  
    mx.mx[0*mx.sz+0] = a;
    mx.mx[0*mx.sz+1] = b;
    mx.mx[0*mx.sz+2] = c;
    mx.mx[1*mx.sz+0] = 1;
    mx.mx[2*mx.sz+2] = 1;
    mx.mx[3*mx.sz+0] = 1;
    mx.mx[3*mx.sz+3] = 1;
}

inline void create_ans (int x2 , int x1 , matrix &ans){
    ans.zero();
    ans.mx[0*ans.sz + 0] = x2;
    ans.mx[1*ans.sz + 0] = x1;
    ans.mx[2*ans.sz + 0] = 1;
    ans.mx[3*ans.sz + 0] = x1;
}



int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int k,s;
    cin>>k>>s;
    while (k--){
        int x1,x2,a,b,c;
        long long n;
        cin>>x1>>x2>>a>>b>>c>>n;
        matrix trans(4);
        create_trans(a,b,c,trans);
        //cout<<trans;
        //fast pow 
        n-=2;//x3 = trans * x2;
        matrix accum(4),half(4);
        accum.identity();
        half = trans;
        if(n & 1) 
            accum = accum * half;
        n = n >> 1;
        while(n != 0) {
            half = half * half;
            if(n & 1) 
                accum = accum * half;
            n = n >> 1;
        }
        matrix ans(4);
        create_ans(x2,x1,ans);
        ans = accum * ans;
        if(s == 0)
            cout<<ans.mx[0]<<" "<<0<<"\n";
        else 
            cout<<ans.mx[0]<<' '<<(ans.mx[3*ans.sz+0] + ans.mx[0]) % mod <<'\n';
    }

    
    
    
}