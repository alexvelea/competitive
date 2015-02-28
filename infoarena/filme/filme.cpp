#include <cstdio>
#include <algorithm>
using namespace std;

    int T[100005];
    int n,m,i,a,b;

int main(){
    freopen ("filme.in","r",stdin);
    freopen ("filme.out","w",stdout);

    scanf ("%d %d", &n, &m);
    for ( i=1; i<=n; i++ ){
        scanf ("%d %d", &a, &b);
        T[i]=a+b;
    }
    sort ( T+1, T+n+1 );
    for ( i=1; i<=n && m-T[i]>=0; i++ )
        m-=T[i];
    printf("%d\n",i-1);
    return 0;
}
