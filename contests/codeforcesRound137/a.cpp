#include <cstdio>
using namespace std;

    int n,i,k,ok=1;
    int A[100005];

int main()
{
    scanf ("%d %d", &n, &k );
    for ( i=1; i<=n; i++ )
        scanf ("%d", &A[i]);
    for ( i=k+1; i<=n; i++ )
        if ( A[i]!=A[k] )
            ok=0;
    if ( ok )
    {
        for ( i=k; i>0; i-- )
            if ( A[i]!=A[k] )
            {

                printf("%d\n",i);
                return 0;
            }
        printf("0");
    }
    else{
        printf("-1");
    }
    return 0;
}
