#include <cstdio>
using namespace std;
int main()
{
    int rez=0,a,b,c,n;
    scanf ("%d", &n);

    for ( ; n; n-- )
    {
        scanf ("%d %d %d",&a,&b,&c);
        if ( a+b+c>=2 )
            rez++;
    }
    printf("%d\n",rez);
    return 0;
}
