#include <cstdio>
using namespace std;

    #define maxn 105
    int n,d,l,i,T[maxn];

int main()
{
    scanf ("%d %d %d", &n, &d, &l );
    for ( i=1; i<n; i++ )
    {
        T[i]=1;
        d=-d+1;
    }
    T[n]=d;
    for ( i=n; i>=1; i-- )
    {
        if ( T[i] < 1 )
        {
            T[i-1] +=1-T[i];
            T[i]=1;
        }
        if ( T[i] > l )
        {
            T[i-1]-=T[i]-l;
            T[i]=l;
        }
    }

    if ( T[0]!=0 )
    {
        printf("-1");
        return 0;
    }
    for ( i=1; i<=n; i++ )
        printf("%d ",T[i]);

}
