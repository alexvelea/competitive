#include <cstdio>
using namespace std;

    #define max_n 1004
    int n,i,j,a,ok;

    struct linie {
        long long val[max_n];
    } Act1, Act2, Last1, Last2;
    long long maxim;

    long long minim ( long long a, long long b ){
        if ( a<b )
            return a;
        return b;
    }

int main(){

    freopen ("diagonale.in","r",stdin);
    freopen ("diagonale.out","w",stdout);   

    scanf ("%d", &n );
    for ( i=1; i<=n; i++ ){
        for ( j=1; j<=n; j++ ){
            scanf ("%d", &a );
            Act1.val[j]=Last1.val[j-1]+a;
            Act2.val[j]=Last2.val[j+1]+a;
        }
        if ( ( maxim < Act1.val[n] ) || ( !ok ) ){
            ok=1;
            maxim = Act1.val[n];
        }
        if ( maxim < Act2.val[1] ){
            maxim = Act2.val[1];
        }       
        Last1=Act1;
        Last2=Act2;
    }
    for ( i=1; i<=n; i++ ){
        if ( maxim < Act1.val[i] ){
            maxim=Act1.val[i];
        }
        if ( maxim < Act2.val[i] ){
            maxim=Act2.val[i];
        }
    }
    printf("%lld", maxim);
    return 0;
}
