#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

    #define max_n 5005
    int A[max_n],B[max_n],C[max_n],best[max_n];
    int n,m,i,j;
    vector<int> V[max_n];

int bs ( int val ){
    int ind=(1<<14),rez=0;
    for ( ; ind; ind>>=1 ){
        if ( ( ind+rez <=m ) && ( C[ind+rez]<=val ) )
            rez+=ind;
    }
    return rez;
}

int main(){
    
        freopen ("secv.in","r",stdin);
        freopen ("secv.out","w",stdout);

    scanf ("%d", &n );
    for ( i=1; i<=n; i++ ){
        scanf ("%d", &A[i] );
        B[i]=A[i];
    }
    sort ( B+1, B+n+1 );
    for ( i=1; i<=n; i++ ){
        C[++m]=B[i];
        j=i;
        while ( ( B[i]==B[j] ) && ( i<=n ) )
            i++;
    }
    for ( i=1; i<=n; i++ ){
        A[i]=bs(A[i]);
    }
    for ( i=n; i>=1; i-- ){
        V[ A[i] ].push_back(i);        
    }
    for ( i=1; i<=m; i++ )
        V[i].push_back(0);
    best[0]=0x3f3f3f3f;
    for ( i=2; i<=m; i++ ){
        if ( V[i].size() == 1 ){
            printf("-1");
            return 0;
        }
        for ( int it=0,it2=0; it< V[i].size()-1; it++ ){
            while ( V[i][it] < V[i-1][it2] )
                it2++;
            best[ V[i][it] ]= best[ V[i-1][it2] ] + V[i][it]-V[i-1][it2];
        }
    }
/*    for ( i=1; i<=n; i++ )
        printf("%d ",best[i]);*/
    int minim=0x3f3f3f3f;
    for ( i=0; i<V[m].size()-1; i++ )
        if ( best[ V[m][i] ] < minim )
            minim=best[ V[m][i] ];
    if ( minim == 0x3f3f3f3f ){
        printf("-1");
        return 0;
    }
    printf("%d\n",minim+1);
    return 0;
}
