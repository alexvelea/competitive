#include <iostream>
using namespace std;

    #define MOD 1000000007
    #define max_n 101
    #define exp(a) ((a<=m%n)?(mpn+1):(mpn))
    long long n,m,k,i,mpn,l,j;
    long long Su[max_n][max_n*max_n];
    long long CB[max_n][max_n];

    long long FACT[max_n];
    long long FACTW[max_n];

    long long pow ( long long nr, long long p )
    {
        if ( p==1 )
            return nr;
        if ( p&1 )
            return ( nr* pow ( (nr*nr) %MOD, p/2 ) )%MOD;
        else
            return ( pow ( (nr*nr)%MOD, p/2 )%MOD) ;
    }

    long long fact ( long long a )
    {
        if ( a==0 )
        {
            return 0;
        }
        if ( a==1 )
        {
            FACT[1]=1;
            return 1;
        }
        if ( FACT[a] )
            return FACT[a];
        FACT[a]=(fact(a-1)*a)%MOD;
        return FACT[a];
    }

    long long factw ( long long a )
    {
        if ( FACTW[a] )
            return FACTW[a];
        FACTW[a]=pow ( fact(a), MOD-2 );
        return FACTW[a];
    }

    long long cb ( long long a, long long b )
    {

        if ( CB[a][b] )
            return CB[a][b];
        CB[a][b]=fact(a);
        CB[a][b]*=factw(b);
        CB[a][b]%=MOD;
        CB[a][b]*=factw(a-b);
        CB[a][b]%=MOD;
        return CB[a][b];
    }

int main()
{
    cin>>n>>m>>k;
    mpn=m/n;
    for ( i=1; i<=n; i++ )
        Su[i][0]=1;
    for ( i=1; i<=n; i++ )
    {
        Su[1][i] = pow ( cb ( n,i ) , exp(i) );
    }

    for ( l=0; l<=k; l++ )
        for ( j=1; j<=n && ( ( j+l ) <=k ); j++ )
        {
            Su[i][l+j]+= Su[i-1][ l ] * pow ( cb(n,j) , exp(i) );
            Su[i][l+j]%=MOD;
        }
    long long rez=0;

    /*for ( i=1; i<=n; i++,cout<<"\n" )
        for ( j=0; j<=k; j++ )
            cout<<Su[i][j]<<" ";*/

    for ( i=1; i<=n; i++ )
    {
        rez+=Su[i][k];
        rez%=MOD;
    }
    cout<<rez<<"\n";
    return 0;
}
