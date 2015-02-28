#include <cstdio>
#include <algorithm>
using namespace std;

    typedef struct { int val[4]; } bilet;
    bilet T[1000000];
    int Sol[4];
    int i,n,m,k,j;

    int rez;
    char Rez[1000000];

void bt ( int start, int deep )
{
    if ( deep == k+1 )
    {
        ++m;
        for ( int i=1; i<=k; ++i )
            T[m].val[i]=Sol[i];
    }
    else{
        for ( int i=start; i<=n*n; ++i )
        {
            Sol[deep]=i;
            bt ( i+1, deep+1 );
        }
    }
}

bool ok ( int ind )
{
    int nr[4];
    for ( int i=1; i<=k; i++ )
    {
        // formam inversele 
        nr[i] = n* int ( ( T[ind].val[i] -1 )/n ) ;
        nr[i] +=  n - ( ( T[ind].val[i]-1 )%n );
    }
    sort ( nr+1,nr+k+1 );
    for ( int i=1; i<=k; i++ )
        if ( T[ind].val[i] ==  nr[i] )
            ;
        else
            return T[ind].val[i] < nr[i];
    return 1;
}

void lin_col( int nr )
{
    Rez[rez++]=char ( ( nr+n-1 )/n + '0' );
    Rez[rez++]=char ( ( ( ( nr-1 )%n ) + 1 ) + '0' );
}

void afisare ( int ind )
{
//    printf("%d %d ---- ",T[ind].val[1],T[ind].val[2] );
    for ( int i=1; i<=k; i++ )
        lin_col( T[ind].val[i] );
    Rez[rez++]='\n';
}

int main()
{
    freopen ("bilete.in","r",stdin);
    freopen ("bilete.out","w",stdout);
    scanf ("%d %d", &n, &k);
    bt ( 1 , 1 );
    for ( i=1; i<=m; i++ )
    {
        if ( ok ( i ) )
            afisare( i );
    }
    Rez[rez]='\0';
    printf("%s",Rez);
    return 0;

}
