#include <cstdio>
#include <vector>
using namespace std;

    #define pb push_back
    #define se second
    #define fi first
    #define max_n 105
    #define max_m 40005

    vector<int> T[max_n];
    pair<int,int> Mu[max_m];

    int a,i,j,n,m,mc;
    bool Viz[max_n];
    bool Viz_m[max_m];

    vector<int> Noduri;
    vector<int> Rez_act;

    int C[max_m];
    int color;
    int It[max_n];
    int Rezultat=1;

    pair<int,int> Stiva[max_m];
    int Sta;

void solve ( int start )
{
    if ( !Rezultat )
        return ;
    int i,j,ok,nrm=0;

    Rez_act.erase ( Rez_act.begin(), Rez_act.end() );
    Noduri.erase ( Noduri.begin(), Noduri.end() );

    Noduri.pb( start );
    Viz[start] = 1;
    for ( i=0; i<Noduri.size(); i++ )
        for ( j=0; j<T[ Noduri[i] ].size(); j++ )
        {
            nrm++;
            if ( !Viz[ Mu [ T[Noduri[i]][j] ].fi + Mu [ T[Noduri[i]][j] ].se - Noduri[i] ] )
            {
                Viz[ Mu [ T[Noduri[i]][j] ].fi + Mu [ T[Noduri[i]][j] ].se - Noduri[i] ]=1;
                Noduri.pb ( Mu [ T[Noduri[i]][j] ].fi + Mu [ T[Noduri[i]][j] ].se - Noduri[i]  );
            }
        }
    nrm/=2;
    if ( nrm&1 )
    {
        int ok=0;
        for ( i=0; i<Noduri.size(); i++ )
            if ( T[ Noduri[i] ].size() != 2 )
                ok=1;
        if ( ok )
            ;
        else
        {
            Rezultat=0;
            return ;
        }
    }

    // punem muchiile
    for ( i=0,j=0; i<Noduri.size(); i++ )
    {
        if ( T[ Noduri[i] ].size()&1 )
        {
            j=i;
            i++;
            while ( !( T[ Noduri[i] ].size()&1 ) )
                i++;
            mc++;
            Mu[mc].fi=Noduri[i];
            Mu[mc].se=Noduri[j];
            T[ Noduri[i] ].pb( mc );
            T[ Noduri[j] ].pb( mc );
        }
    }
    Sta=0;
    Stiva[Sta].fi= Noduri[j];
    while ( Sta >= 0 )
    {
        #define nod Stiva[Sta].fi
        #define it It[nod]

        ok=1;
        for ( ; it< T[ nod ].size(); )
        {
            int aux_nod=nod,aux_it=it;
            it++;
            if ( !Viz_m [ T[aux_nod][aux_it] ] )
            {
                Viz_m[ T[aux_nod][aux_it] ]=1;
                Sta++;
                Stiva[ Sta ].fi = Mu [ T[aux_nod][aux_it] ].fi + Mu [ T[aux_nod][aux_it] ].se - aux_nod;
                Stiva[ Sta ].se = T[aux_nod][aux_it];
                ok=0;
                break;
            }
        }
        if ( ok )
        {
            Rez_act.pb ( Stiva[Sta]. se );
            Sta--;
        }
    }
    for ( i=Rez_act.size()-2; i>=0; i-- )
    {
        C[ Rez_act[i] ]=color+1;
        color^=1;
    }
}

int main()
{
    scanf ("%d", &n );
    mc=n*n;
    for ( i=1; i<=n; i++ )
    {
        scanf ("%d", &a );
        while ( a )
        {
            if ( a < i )
            {
                m++;
                Mu[m].fi=a;
                Mu[m].se=i;

                T[i].pb(m);
                T[a].pb(m);
            }
            if ( a == i )
            {
                m++;
                mc++;
                Mu[m].fi=a;
                Mu[m].se=a;

                Mu[mc].fi=a;
                Mu[mc].se=a;

                T[i].pb(m);
                T[i].pb(mc);
            }
            scanf ("%d", &a);
        }
    }

    for ( i=1; i<=n; i++ )
        if ( !Viz[i] )
            solve ( i );
    if ( Rezultat )
        for ( i=1; i<=n; i++ )
        {
            for ( j=0; j< T[i].size(); j++ )
                if ( T[i][j]<=m )
                    printf("%d ",C [ T[i][j] ]);
            printf("0\n");
        }
    else
        printf("No solution");
    return 0;
}
