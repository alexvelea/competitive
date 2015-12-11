#include <cstdio>
#include <iostream>

#include <vector>
#include <cstdlib>
using namespace std;

    #define max_n 50005
    #define pb push_back

    vector <int> T[2];
    int n,Val[max_n],Semn[max_n];
    long long s,act;
    int i;

int main()
{
    srand( time(NULL) );

    freopen ("semne.in","r",stdin);
    freopen ("semne.out","w",stdout);
    cin>>n>>s;
    for ( i=1; i<=n; i++ ){
        scanf ("%d", &Val[i] );
        if ( act <= s ){
            act+=Val[i];
            T[0].pb ( i );
        }
        else{
            act-=Val[i];
            T[1].pb ( i );
        }
    }
    while ( act!= s ){
        if ( act < s ){
            int nr = rand() % T[1].size();
            act+= 2*Val[ T[1][nr] ];
            T[0].pb ( T[1][nr] );
            T[1][nr]=T[1].back();
            T[1].pop_back();
        }
        else{
            int nr = rand() % T[0].size();
            act-= 2*Val[ T[0][nr] ];
            T[1].pb ( T[0][nr] );
            T[0][nr]=T[0].back();
            T[0].pop_back();
        }
    }
    for ( i=0; i<T[0].size(); i++ )
        Semn [T[0][i]]=1;
    for ( i=1; i<=n; i++ )
        if ( Semn[i] )
            printf("+");
        else
            printf("-");
    return 0;
}
