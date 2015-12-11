#include <cstdio>
#include <cmath>
using namespace std;
    
    double p;
    int n,i,j;

int main()
{
    freopen ("zaruri.in","r",stdin);
    freopen ("zaruri.out","w",stdout);

    scanf ("%d", &n );
    p=3.5;
    for ( i=2; i<=n; i++ )
    {
        j=ceil(p);
        p= (j-1)*p/6 + ( (6.0+j)*(6.0-j+1.0)/2.0 )/6.0; 
    }
    printf("%.8f\n",p);
    return 0;
}
