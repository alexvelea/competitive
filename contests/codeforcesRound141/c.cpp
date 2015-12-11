#include <cstdio>
using namespace std;

    #define next(a,b,c) ((a==c)?(a=1,b++):(a++))
    #define maxn 505

    int n,m,T[maxn][maxn];
    int Sum[maxn][maxn],ok;
    char c;
    int P,PC;
    int Pos[20][maxn][maxn];
    int rez;
    int i,j,Pa[3][3],d,o;

int main()
{
    //freopen ("text.txt","r",stdin);

    scanf ("%d %d", &n, &m);
    for ( i=1,j=1; i<=n; )
    {
        scanf ("%c", &c );
        if ( c=='*' || c=='.' )
        {
            if (c=='*')
                T[i][j]=1;
            else
                T[i][j]=0;
            next(j,i,m);
        }
    }
    for ( i=1; i<=n; i++ )
        for ( j=1; j<=m; j++ )
            Sum[i][j]=Sum[i][j-1]+Sum[i-1][j]+T[i][j]-Sum[i-1][j-1];
    /*for ( i=1; i<=n; i++,printf("\n") )
            for ( j=1; j<=m; j++ )
                printf("%d ",T[i][j]);
    printf("\n\n");
    for ( i=1; i<=n; i++,printf("\n") )
            for ( j=1; j<=m; j++ )
                printf("%d ",Sum[i][j]);
    printf("\n\n");*/
    // pattern de 2*2
    for ( P=0; P<=15; P++ )
    {
        PC=P;
        for ( i=1; i<=2; i++ )
            for ( j=1; j<=2; j++ )
            {
                Pa[i][j]=PC&1;
                PC>>=1;
            }
        for ( d=1; d<=15; d++ )
            for ( i=1; i<=n; i++ )
                for ( j=1; j<=m; j++ )
                    Pos[d][i][j]=0;
        for ( i=1; i<=n; i++ )
            for ( j=1; j<=m; j++ )
                Pos[0][i][j]=T[i][j]^1;
        /*for ( i=1; i<=2; i++,printf("\n") )
            for ( j=1; j<=2; j++ )
                printf("%d ",Pa[i][j]);*/
        for ( d=1,o=1; d<=n; d<<=1,o++ )
        {
            for ( i=1; i+2*d-1<=n; i++ )
                for ( j=1; j+2*d-1<=m; j++ )
                {
                    ok=1;
                    if ( Pa[1][1] == 0 )
                    {
                        if ( Pos[o-1][i][j]==1 )
                            ;
                        else
                            ok=0;
                    }
                    else{
                        if ( ( Sum[ (i+d-1) ][ (j+d-1) ]+Sum[( i-1) ][ (j-1) ] - Sum[ (i+d-1) ][ (j-1) ] - Sum[ (i-1) ][ (j+d-1) ] ) == d*d )
                            ;
                        else
                            ok=0;
                    }
                    if ( Pa[1][2] == 0 )
                    {
                        if ( Pos[o-1][i][j+d]==1 )
                            ;
                        else
                            ok=0;
                    }
                    else{
                        if ( ( Sum[ (i+d-1) ][ (j+d-1)+d ]+Sum[( i-1) ][ (j-1)+d ] - Sum[ (i+d-1) ][ (j-1)+d ] - Sum[ (i-1) ][ (j+d-1)+d ] ) == d*d )
                            ;
                        else
                            ok=0;
                    }
                    if ( Pa[2][2] == 0 )
                    {
                        if ( Pos[o-1][i+d][j+d]==1 )
                            ;
                        else
                            ok=0;
                    }
                    else{
                        if ( ( Sum[ (i+d-1)+d ][ (j+d-1)+d ]+Sum[( i-1)+d ][ (j-1)+d ] - Sum[ (i+d-1)+d ][ (j-1)+d ] - Sum[ (i-1)+d ][ (j+d-1)+d ] ) == d*d )
                            ;
                        else
                            ok=0;
                    }
                    if ( Pa[2][1] == 0 )
                    {
                        if ( Pos[o-1][i+d][j]==1 )
                            ;
                        else
                            ok=0;
                    }
                    else{
                        if ( ( Sum[ (i+d-1)+d ][ (j+d-1) ]+Sum[( i-1)+d ][ (j-1) ] - Sum[ (i+d-1)+d ][ (j-1) ] - Sum[ (i-1)+d ][ (j+d-1) ] ) == d*d )
                            ;
                        else
                            ok=0;
                    }
                    if ( ok )
                        {
                            Pos[o][i][j]=1;
                            if ( o>=2 )
                                rez++;
                        }
                }

        }
        //printf("    ->%d\n",rez);
        /*for ( i=1; i<=n; i++,printf("\n") )
            for ( j=1; j<=m; j++ )
                printf("%d ",T[i][j]);
        printf("\n\n");
        for ( i=1; i<=n; i++,printf("\n") )
            for ( j=1; j<=m; j++ )
                printf("%d ",Pos[1][i][j]);
        printf("\n\n");printf("\n\n");printf("\n\n");*/
    }
    printf("%d\n",rez);
    return 0;
}
