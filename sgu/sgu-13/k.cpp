#include <cstdio>
using namespace std;
int main()
{
    int a,b;
    scanf ("%d %d", &a, &b );
    b-=a;
    if ( b >= 30*60 )
    {
        printf("4");
        return 0;
    }
    if ( b >= 15*60 )
    {
        printf("3");
        return 0;
    }
    if ( b >= 5*60 )
    {
        printf("2");
        return 0;
    }
    if ( b >= 1 )
    {
        printf("1");
        return 0;
    }
    printf("0\n");
    return 0;

}
