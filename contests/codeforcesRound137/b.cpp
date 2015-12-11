#include<cstdio>
#include<iostream>

#include <algorithm>
using namespace std;

    #define maxn 1005

    int i,j,n,m,q,x,y;
    char c;
    int T[maxn][maxn];
    int ColNow[maxn];
    int LinNow[maxn];

int main()
{
    scanf ("%d %d %d", &n, &m, &q);
    for ( i=1; i<=n; i++ )
        for ( j=1; j<=m; j++ )
            scanf ("%d", &T[i][j] );

    for ( i=1; i<=n || i<=m; i++ )
        LinNow[i]=ColNow[i]=i;

    for ( ; q; q-- )
    {
        cin>>c>>x>>y;
        if ( c=='c' )
            swap ( ColNow[x], ColNow[y] );
        if ( c=='r' )
            swap ( LinNow[x], LinNow[y] );
        if ( c=='g' )
            printf("%d\n", T[ LinNow[x] ] [ ColNow[y] ] );
    }


    return 0;
}
