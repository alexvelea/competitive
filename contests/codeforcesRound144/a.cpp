#include <cstdio>
using namespace std;

    int Rez[105][105];
    int n,m,act,i,j,k;

int main()
{
    scanf ("%d", &k );
    n=100;
    while ( n*(n-1)*(n-2)/6 > k )
        n--;
    k-=n*(n-1)*(n-2)/6;
    act=n+1;
    m=n;

    for ( i=1; i<=n; i++ )
        for ( j=i+1; j<=n; j++ )
            Rez[i][j]=1;

    while ( k )
    {
        while ( m*(m-1)/2 > k )
            m--;
        for ( i=1; i<=m; i++ )
            Rez[i][act]=1;
        k-=m*(m-1)/2;
        act++;
    }
    act--;
    printf("%d\n",act);
    for ( i=1; i<=act; i++ )
        for ( j=1; j<=i; j++ )
            Rez[i][j]=Rez[j][i];
    for ( i=1; i<=act; i++,printf("\n"))
        for ( j=1; j<=act; j++ )
            printf("%d",Rez[i][j]);
    return 0;
}
