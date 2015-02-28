#include <cstdio>
#include <utility>
using namespace std;

    #define max_n 32005
    int n,A[max_n],i;

void inverseaza ( int st, int dr ){
    for ( int i=0; st+i < dr-i; i++ ){
        swap ( A[st+i], A[dr-i] );
    }
}

void merge_sort ( int st, int dr, int bit ){
    // check
    int i,val=( A[st]&(1<<bit) ), ok=1, m;
    for ( i=st; i<=dr; i++ ){
        if ( ( A[i]&(1<<bit) ) != val )
            ok=0;
    }
    if ( ok ){
        return ;
    }
    m=(st+dr)/2;
    merge_sort ( st, m, bit );
    merge_sort ( m+1, dr, bit );
    // gasim elementele care trebuie mutate.
    
    int s,d;
    for ( s=m; s>=st && ( ( A[s] & (1<<bit) ) == (1<<bit) ) ; s-- ){
        ;
    }
    for ( d=m+1; d<=dr && ( ( A[d] & (1<<bit) ) == 0 ) ; d++ ){
        ;
    }
    if ( ( s==m ) && ( d==m+1 ) ){
        return ;
    }
    s++;
    d--;
    if ( s<d ){
        printf("%d %d\n",s,d);
        inverseaza(s,d);
    }
}

void inv_sort ( int st, int dr, int bit ){

    int i;

    if ( bit == -1 )
        return ;
    merge_sort ( st, dr, bit );
    for ( i=st; (i<=dr) && ( ( A[i]&(1<<bit) ) == 0 ); ++i )
        ;
    if ( ( i==dr+1 ) || ( i==st ) ){
        inv_sort ( st, dr, bit-1 );
    }
    else{
        inv_sort ( st, i-1, bit-1 );
        inv_sort ( i, dr, bit-1 );
    }
}

int main(){


    freopen ("invsort.in","r",stdin);
    freopen ("invsort.out","w",stdout);

    scanf ("%d", &n);
    for ( i=1; i<=n; i++ ){
        scanf ("%d", &A[i]);
    }
    inv_sort ( 1, n, 16 );
/*    for ( i=1; i<=n; i++ ){
        printf("%d ",A[i]);
    }*/
    return 0;
}
