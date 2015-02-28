#include <cstdio>
#include <algorithm>
using namespace std;

    #define maxn 100005
    int n,i,first,actk,k,T[maxn],nr;
    int Max,val;

int main()
{
    scanf ("%d %d", &n, &k);
    for ( i=1; i<=n; i++ )
        scanf ("%d", &T[i]);
    sort ( T+1, T+n+1 );

    actk=k;
    first=n;
    nr=1;
    T[n+1]=T[n];
    for ( i=n; i>0; i-- )
    {
        actk+=(T[i+1]-T[i])*nr;
        while ( ( actk >= (T[i]-T[ first-1 ]) ) && ( first>1 ) )
        {
            nr++;
            actk-=T[i]-T[ first-1 ];
            first--;
        }
        if ( nr >= Max )
        {
            Max=nr;
            val=T[i];
        }
        nr--;
    }
    printf("%d %d",Max,val);
    return 0;
}
