#include <cstdio>
#include <algorithm>
using namespace std;

long T[5],i,j,poz;
int main()
{
    scanf ("%d %d %d %d", &T[1], &T[2], &T[3], &T[4] );
    sort ( T+1,T+5);
    for ( i=1; i<5; )
    {
        j=i;
        while ( T[i]==T[j] )
            i++;
        poz++;
    }
    printf("%d\n",4-poz);
}
