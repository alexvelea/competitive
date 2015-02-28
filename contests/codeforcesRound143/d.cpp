#include <cstdio>
using namespace std;

    int T[7];
    int i,sum;
    int x1,x0,y1,y0,z1,z0;

int main()
{
    scanf ("%d %d %d", &x1, &y1, &z1 );
    scanf ("%d %d %d", &x0, &y0, &z0 );
    for ( i=1; i<=6; i++ )
        scanf ("%d ",&T[i] );
    sum=0;
    if ( ( x1 > x0 ) || ( x1 < 0 ) )
    {
        if ( x1 > 0 )
        {
            // vede fata a6
            sum+=T[6];
        }
        else{
            // vede fata a5
            sum+=T[5];
        }
    }
    if ( ( y1 > y0 ) || ( y1 < 0 ) )
    {
        if ( y1 > 0 )
        {
            // vede fata a6
            sum+=T[2];
        }
        else{
            // vede fata a5
            sum+=T[1];
        }
    }
    if ( ( z1 > z0 ) || ( z1 < 0 ) )
    {
        if ( z1 > 0 )
        {
            // vede fata a6
            sum+=T[4];
        }
        else{
            // vede fata a5
            sum+=T[3];
        }
    }
    printf("%d", sum );
    return 0;
}
