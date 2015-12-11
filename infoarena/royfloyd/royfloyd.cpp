#include <cstdio>
using namespace std;

    #define max_n 105

    int T[max_n][max_n],n,i,j,k;

int main(){

        freopen ("royfloyd.in","r",stdin);
        freopen ("royfloyd.out","w",stdout);

    scanf ("%d", &n );
    for ( i=1; i<=n; i++ ){
        for ( j=1; j<=n; j++ ){
            scanf ("%d", &T[i][j] );
        }
    }
    for ( k=1; k<=n; k++ ){
        for ( i=1; i<=n; i++ ){
            for ( j=1; j<=n; j++ ){
                if ( ( ( T[i][j] > T[i][k]+T[k][j] ) || ( (T[i][j] ==0) ) ) && ( ( T[i][k]!=0 ) && ( T[k][j]!=0 ) && ( i!=j ) ) )
                    T[i][j]=T[i][k]+T[k][j];
            }
        }
    }
    for ( i=1; i<=n; i++,printf("\n") ){
        for ( j=1; j<=n; j++ ){
            printf("%d ", T[i][j]);
        }
    }
    
    return 0;
}
