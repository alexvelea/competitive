#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

    #define INF ((1<<30)-1)
    #define max_n 5005

    int A[max_n],B[max_n],C[max_n];
    int n,m,i,j,minim;
    int Best[max_n];

    int BS ( int val ){
        int rez=0,ind;
        for ( ind=1; ind <= m; ind<<=1 )
            ;
        for ( ; ind; ind>>=1 )
            if ( ( ind+rez <=m ) && ( C[ind+rez] <= val ) )
                rez+=ind;
        return rez;
    }

int main(){
    
        freopen ("secv.in","r",stdin);
        freopen ("secv.out","w",stdout);
    
    minim=INF;
    scanf ("%d", &n );
    for ( i=1; i<=n; i++ ){
        scanf ("%d", &A[i] );
        B[i]=A[i];
    }
    sort ( B+1, B+n+1 );
    for ( i=1; i<=n; ){
        C[++m]=B[i];
        while ( ( C[m] == B[i] ) && ( i<=n ) )
            i++;
    }
    sort ( C+1, C+m+1 );
    for ( i=1; i<=n; i++ ){
        A[i]=BS ( A[i] );
    }
    for ( i=1; i<=n; i++ ){
        if ( A[i] != 1 ){
            Best[i]=INF;
            for ( j=i-1; j>=1; j-- ){
                if ( A[j] == A[i]-1 )
                    Best[i] = min( Best[i] , Best[j] + i-j );
            }
        }
    }    
    minim=INF;
    for ( i=1; i<=n; i++ ){
        if ( A[i] == m ){
            if ( minim > Best[i] )
                minim=Best[i];
        }
    }
    if ( minim != INF ){
        printf("%d\n",minim+1);
    }
    else{
        printf("-1\n");
    }
    return 0;
}
