#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

    int n,i,a,b,rez;


int main()
{
    freopen ("serviciu.in","r",stdin);
    freopen ("serviciu.out","w",stdout);
    scanf ("%d", &n );
    for ( i=1; i<=n; i++ )
    {
        scanf ("%d %d", &a, &b );
        rez=max ( rez, min ( abs ( a-b ) -1 , 2*n - 1 - abs ( a-b ) ) ) ;
    }
    printf("%d", rez+1);

    return 0;

}
