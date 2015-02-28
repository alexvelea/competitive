#include <cstdio>
using namespace std;
#define next(a,b,c) ((a==c)?(a=1,b++):(a++))
#define max(a,b) ((a>b)?(a):(b))

    int na,nb,ma,mb;
    int A[55][55],B[55][55];
    int maxim,xr,yr,mx,my;
    char c;
    int i,j,r;

int main()
{
    scanf ("%d %d", &na, &ma );
    for ( i=1,j=1; i<=na;  )
    {
        scanf ("%c", &c);

        if ( (c=='0') || (c=='1') )
        {
            A[i][j]=c-'0';
            next(j,i,ma);
        }
    }
    scanf ("%d %d", &nb, &mb );
    for ( i=1,j=1; i<=nb;  )
    {
        scanf ("%c", &c);
        if ( c=='0' || c=='1' )
        {
            B[i][j]=c-'0';
            next(j,i,mb);
        }
    }
    for ( xr=-50; xr<=50; xr++ )
        for ( yr=-50; yr<=50; yr++ )

        {
            r=0;
            for ( i=max(1,-xr+1); (i<=na) && (i+xr>=1) && (i+xr<=nb); i++ )
                for ( j=max(1,-yr+1); (j<=ma) && (j+yr>=1) && (j+yr<=mb); j++ )
                {
                    if ( ( A[i][j]==1 ) && ( A[i][j]==B[i+xr][j+yr] ) )
                    {
                        r++;
                    }
                }
            if ( r>maxim )
            {
                maxim=r;
                mx=xr;
                my=yr;
            }
        }
    printf("%d %d", mx,my);
    return 0;
}
