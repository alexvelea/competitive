#include <cstdio>
using namespace std;

    int Sum[100][100];
    int i,j,l,s;

int main()
{
    scanf ("%d", &s );
    for ( i=0; i<=9; i++ )
        Sum[1][i]=1;
    for ( l=2; l<=9; l++ )
    {
        for ( i=0; i<=s; i++ )
            for ( j=0; j<=9; j++ )
                Sum[l][ i+j ]+=Sum[l-1][i];
    }
    if ( s==1 )
        Sum[9][s]++;
    printf("%d\n", Sum[9][s] );
    return 0;
}
