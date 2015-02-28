#include <cstdio>
#include <vector>
using namespace std;
#define pb push_back
#define next(a) ((a==1)?(2):(1))

typedef struct { long val,c; } tip;
vector<tip> T[105];
tip aux;
int Cu[105];
int Nr[10];
int n,m,i,j,a,b,c,ok=1;
int Rez[105];
int RezFin[105],NrRez;


long df( long varf, long culoare )
{
    if ( Cu[varf]==0 )
        ;
    else
    {
        if ( Cu[varf]!=culoare )
            ok=0;
        return 0;
    }
    Cu[varf]=culoare;
    Nr[culoare]++;
    Rez[++Nr[0]]=varf;
    vector <tip> :: iterator it;
    for ( it=T[varf].begin(); it!=T[varf].end(); it++ )
    {

            if ( it->c )
            {
                df( it->val, culoare );

            }
            else
                df ( it->val, next( culoare ) );

    }
}

int main()
{
    scanf ("%d %d", &n, &m);
    for ( i=1; i<=m; i++ )
    {
        scanf ("%d %d %d", &a, &b, &c );
        aux.c=c;
        aux.val=b;
        T[a].pb(aux);
        aux.val=a;
        T[b].pb(aux);
    }
    ok=1;
    for ( i=1; i<=n; i++ )
    {
        if ( !Cu[i] )
        {
            Nr[0]=Nr[1]=Nr[2]=0;
            df(i,1);
            /*for ( j=1; j<=n; j++ )
                printf("i) %d    ->%d\n",j,Cu[j]);
            printf("\n");*/

            if ( Nr[1] >= Nr[2] )
            {
                // mergem pe Nr2
                for ( j=1; j<=Nr[0]; j++ )
                    if ( Cu[Rez[j]] == 2 )
                        RezFin[++NrRez]=Rez[j];
            }
            else{
                // mergem pe Nr2
                for ( j=1; j<=Nr[0]; j++ )
                    if ( Cu[Rez[j]] == 1 )
                        RezFin[++NrRez]=Rez[j];
            }
        }
    }
    if ( ok )
    {
        printf("%d\n",NrRez);
        for ( i=1; i<=NrRez; i++ )
            printf("%d ",RezFin[i] );
    }
    else
        printf("Impossible\n");
    return 0;
}
