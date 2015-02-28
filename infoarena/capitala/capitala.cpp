#include <cstdio>
#include <vector>
using namespace std;


    #define INF ( (1<<31) - 1 )
    #define max_n 200005
    #define pb push_back

    struct noname{
        int a,b,c;
    } Mu[max_n];

    int Viz[max_n];
    int Maxim[max_n];
    int a,b,i,j,n,minim=INF;
    vector<int> T[max_n];

    int df2 ( int nod , int cost )
    {
        int maxim,maxim2=0;
        maxim=cost;
        Viz[nod]=1;
        #define mu Mu[ T[nod][i] ]
        for ( int i=0; i<T[nod].size(); i++ ){
            if ( !Viz[ mu.a + mu.b - nod ] ){
                if ( ( Maxim[ mu.a + mu.b - nod ] + mu.c ) >= maxim ){
                    maxim2=maxim;
                    maxim=Maxim [ mu.a + mu.b - nod ] + mu.c ;
                }
                else{
                    if ( ( Maxim[ mu.a + mu.b - nod ] + mu.c ) >= maxim2 ){
                        maxim2= Maxim[ mu.a + mu.b - nod ] + mu.c;
                    }
                }
            }
        }
        for ( int i=0; i<T[nod].size(); i++ )
        {
            if ( !Viz[ mu.a + mu.b - nod ] )
            {
                if ( Maxim[ mu.a + mu.b - nod ] + mu.c == maxim ){
                    // mergem pe maxim2
                    df2 ( mu.a+mu.b-nod,maxim2+mu.c);
                }
                else{
                    df2 ( mu.a+mu.b-nod, maxim+mu.c );
                }

            }
        }
        if ( maxim < minim )
            minim=maxim;
    }

    int df ( int nod ){
        Viz[nod]=1;
        int maxim=0;
        for ( int i=0; i<T[nod].size() ; i++ ){
            if ( 
                !Viz[ Mu[ T[nod][i] ].a + Mu[ T[nod][i] ].b - nod ] )
                maxim = max ( maxim , Mu[ T[nod][i] ].c + df ( Mu[ T[nod][i] ].a + Mu[ T[nod][i] ].b - nod ) );
        }
        Maxim[nod]=maxim;
        return maxim;
    }

int main()
{
/*    freopen ("capitala.in","r",stdin);
    freopen ("capitala.out","w",stdout);*/
    
    scanf ("%d", &n );
    for ( i=1; i<n; i++ ){
        scanf ("%d %d", &a, &b );
        Mu[i].a=a;
        Mu[i].b=b;
        Mu[i].c=1;

        T[a].pb(i);
        T[b].pb(i);
    }
    df ( 1 ); 
    for ( i=1; i<=n; i++ )
        printf ("%d --- %d\n",i,Maxim[i]);
    for( i=1; i<=n; i++ )
        Viz[i]=0;
    df2 ( 1, 0 );
    return 0;
}
