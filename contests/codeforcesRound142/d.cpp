#include <cstdio>
using namespace std;
#define maxn 5005

    int H[maxn];
    int n,i,j,st,last,act,rez;
    typedef struct { int val, rez,ok; } poo;
    poo R[maxn];

int main()
{
    scanf ("%d", &n );
    for ( i=1; i<=n; i++ )
        scanf ("%d", &H[i]);
    last=0;
    R[1].ok=1;
    R[1].val=-1;
    for ( i=1; i<=n; i++ )
    {
        last=R[i].val;
        //printf("    -> %d\n",last);
        j=i;
        if ( R[i].ok )
        {
            act=H[j];
            rez=R[i].rez;
            while ( ( act<last ) && ( j<n ) )
            {
                rez++;
                j++;
                act+=H[j];
            }
            //printf("%d %d\n", i,j );
            // acum mergem pana la final!
            j++;
            if ( act >= last )
            {
                for ( ; j<=n+1; j++ )
                {
                    if ( ( R[j].rez > rez ) || !R[j].ok )
                    {
                        R[j].ok=1;
                        R[j].rez=rez;
                        R[j].val=act;
                    }
                    act+=H[j];
                    rez++;
                }
            }
        }
    }
    for ( i=1; i<=n+1; i++ )
        printf ("%d     %d\n",R[i].rez,R[i].val);
    printf("%d\n", R[n+1].rez);
    return 0;
}
