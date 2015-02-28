#include <cstdio>
#include <iostream>
using namespace std;

    unsigned long long a,b,c;

unsigned long long multi ( unsigned long long a, unsigned long long b ){
    int T[50];
    int i=0;
    while ( b ){
        T[++i]=b%10;
        b/=10;
    }
    unsigned long long rez=0;
    for ( ; i>0; i-- ){
        unsigned long long p=rez;
        int j;
        for ( j=1; j<=9; j++ ){
            rez=(rez+p)%c;
        }
        for ( j=1; j<=T[i]; j++ ){
            rez=(rez+a)%c;
        }
    }
    return rez;
}

unsigned long long pw ( unsigned long long a, unsigned long long b ){
    if ( b==1 )
        return a;
    if ( b==0 )
        return 1;
    if ( b&1 ){
        return (multi( a, pw(multi(a,a),b/2) ));
    }
    else
        return pw((multi(a,a)),b/2);
}

int main(){
   freopen("classictask.in","r",stdin);
    freopen ("classictask.out","w",stdout);
    cin>>a>>b>>c;
    cout<<pw(a,b);
    return 0;
}
