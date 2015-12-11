#include <cstdio>
#include <cstdlib>
using namespace std;
int main()
{
    int n,i,u,l;
    freopen ("secv3.in","w",stdout);
    scanf ("%d %d %d", &n, &u, &l );
    printf("%d %d %d\n",n,u,l);
    for ( i=1; i<=2*n; i++ )
        printf("%d ",rand()%1000+1);
    return 0;
}
