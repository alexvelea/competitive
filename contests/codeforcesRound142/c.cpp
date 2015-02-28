#include <cstdio>
#include <iostream>
using namespace std;
#define maxn 1000006

    int B[maxn];
    int n,m,a,b,i;
    long long Rez,Sum;

int main()
{
    scanf ("%d %d", &n, &m );
    if ( n<3 )
    {
        cout<<"0";
        return 0;
    }
    for ( i=1; i<=m; i++ )
    {
        scanf ("%d %d", &a, &b );
        B[a]++;
        B[b]++;
    }
    for ( i=1; i<=n; i++ )
        Sum+=(n-1-B[i])*B[i];
    Sum/=2;
    Rez=(long long)n*(n-1)*(n-2)/6;
    Rez-=Sum;
    cout<<Rez;
    return 0;
}
