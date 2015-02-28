#include <cstdio>
using namespace std;

    double p=0,n,m,i;

int main()
{
    scanf ("%d %d", &n, &m );
    for ( i=1; i<=m; i++ )
    {
        p+=1-p/n;
        printf("%.10f\n",p);
    }
    return 0;
}
