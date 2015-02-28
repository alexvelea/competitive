#include <cstdio>
#include <iostream>
using namespace std;

    int V[100000];
    int cifz,cif,a,b;

bool bt ( int nr )
{
    int i,cnr;
    if ( nr == b )
        return 1;
    int P[10];
    for ( i=1; i<=cif; i++ )
        P[i]=0;
    cnr=nr;
    while ( cnr )
    {
        P[ cnr%10 ]++;
        cnr/=10;
    }
    int ok=0,poz;
    for ( i=1; i<=cif; i++ )
        if ( P[i] == 0 )
        {
            ok++;
            poz=i;
        }
    cnr=nr;
    if ( ok )
    {
        // scoatem prima cifra
        nr*=10;
        nr+=poz;
        nr%=cifz;
        if ( ( V[nr] > V[cnr]+1 ) || ( V[nr]==0) )
        {
            V[nr]=V[cnr]+1;
            if ( bt(nr) )
            {
                printf("%d",poz);
                return 1;
            }
            return 0;
        }
    }
    else{

        int i;

        nr*=10;
        nr=nr%cifz;

        for ( i=1; i<=cif; i++ )
        {
            nr++;
            if ( ( V[nr] > V[cnr]+1 ) || ( V[nr]==0) )
            {
                V[nr]=V[cnr]+1;

                if ( bt(nr) )
                {
                    cout<<i;
                    return 1;
                }
            }

        }
    }
    return 0;
}

int main()
{
    cin>>cif;
    cifz=1;
    for ( int i=0; i<cif; i++ )
        cifz*=10;

    cin>>a>>b;
    V[a]=1;
    bt ( a );
    return 0;
}
