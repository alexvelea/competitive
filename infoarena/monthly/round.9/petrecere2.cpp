#include <cstdio>
#include <vector>
using namespace std;

    #define max(a,b) ((a>b)?(a):(b))
    #define max_n 100005
    #define pb push_back
    vector<int> T[max_n];
    typedef struct { int val,a,b; } muchie;
    muchie Mu[max_n];

    int n,i,j,m,rez,V[max_n],Rez[2],ok,Cu[max_n],It[max_n];

void df ( int varf, int culoare )
{
    Cu[varf]=culoare;
    Rez[culoare]++;
    V[varf]=1;
    for ( ; It[varf] < T[varf].size(); It[varf]++ )
    {
        #define it It[varf]
        if ( !V [ Mu[ T[varf][it] ].a + Mu[ T[varf][it] ].b - varf ] )
        {
            df ( Mu[ T[varf][it] ].a + Mu[ T[varf][it] ].b - varf,  culoare^Mu[ T[varf][it] ].val );
        }
        else
        {
            if ( Cu [ Mu[ T[varf][it] ].a + Mu[ T[varf][it] ].b - varf ] != ( culoare^ Mu[ T[varf][it] ].val ) )
                ok=0;
        }

    }
}

int main()
{
    freopen ("petrecere2.in","r",stdin);
    freopen ("petrecere2.out","w",stdout);
    scanf ("%d %d", &n, &m );
    for ( i=1; i<=m; i++ )
    {
        scanf ("%d %d %d", &Mu[i].val, &Mu[i].a, &Mu[i].b );
        T [ Mu[i].a ].pb ( i );
        T [ Mu[i].b ].pb ( i );
    }

    for ( i=1; i<=n; i++ )
    {
        if ( !V[i] )
        {
            Rez[0]=0;
            Rez[1]=0;
            ok=1;
            df ( i ,0 );
            if ( ok )
                rez+=max ( Rez[0], Rez[1] );
        }
    }

    printf("%d", rez );
    return 0;
}
