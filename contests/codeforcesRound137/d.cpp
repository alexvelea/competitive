#include <cstdio>
#include <algorithm>
using namespace std;

    #define maxn 100005

    int i,j,n,x;
    int Rb,Rw;
    int A[maxn];
    int B[maxn];

int main()
{
    scanf ("%d %d", &n, &x );
    for ( i=1; i<=n; i++ )
        scanf ("%d", &A[i]);
    for ( i=1; i<=n; i++ )
        scanf ("%d", &B[i]);

    sort ( A+1,A+n+1 );
    sort ( B+1,B+n+1 );

    // worst case
    for ( i=n, j=1; j<=n && i>0; i--,j++ )
    {
        while ( ( A[i]+B[j] < x ) && ( j<=n ) )
            j++;
        if ( j<=n )
            Rw++;
    }
    printf("%d %d", 1, Rw );
    return 0;
}

