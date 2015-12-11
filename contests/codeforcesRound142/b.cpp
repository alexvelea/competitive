#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

#define maxn 100005
#define fi first
#define se second

typedef struct { int to,c; } Muchie;
Muchie aux;

vector <Muchie> V[maxn];
    vector <Muchie> :: iterator itM;
vector <int> St[maxn];
    vector <int> :: iterator it;
priority_queue < pair< int, int > > Deq;

    int a,b,c;
    int i,j;
    int n,m;
    int Viz[maxn];
    int Best[maxn];
    pair<int,int> act;
int main()
{
    scanf ("%d %d", &n, &m );
    for ( i=0; i<m; i++ )
    {
        scanf ("%d %d %d", &a, &b, &c);
        aux.to=a;
        aux.c=c;
        V[b].push_back(aux);
        aux.to=b;
        V[a].push_back(aux);
    }
    for ( i=1; i<=n; i++ )
    {
        scanf ("%d", &a );
        for ( j=1; j<=a; j++ )
        {
            scanf ("%d", &b );
            St[i].push_back(b);
        }
    }
    Deq.push( make_pair ( 0,1 ) );
    while ( !Deq.empty() )
    {
        act=Deq.top();
        Deq.pop();
        if ( !Viz[ act.se ] )
        {
            Viz[ act.se ]=1;
            act.fi*=-1;
            Best[ act.se ]=act.fi;
            //printf("    ----> %d %d\n",act.se,act.fi);
            for ( it=St[ act.se ].begin(); ( it!=St[ act.se ].end() ) && ( *it<act.fi ) ; it++ )
                ;
            int T=act.fi;
            for ( ; ( it!=St[ act.se ].end() ) && ( *it == T ); it++ )
                T++;

            for ( itM = V[ act.se ].begin(); itM!= V[act.se].end(); itM++ )
            {
                if ( !Viz[ itM->to] )
                {
                    //printf("        From - %d   To - %d         c - %d\n",act.se,itM->to,itM->c+T);
                    Deq.push( make_pair ( -( itM->c+T ) , itM->to ));
                }
            }

        }
    }
    /*for ( i=1; i<=n; i++ )
        printf("-> %d       Best[] -> %d \n",i,Best[i]);*/
    if ( Viz[n] )
        printf("%d\n", Best[n] );
    else
        printf("-1");
    return 0;
}
