#include <cstdio>
#include <vector>
using namespace std;

    #define max_n 100
    #define INF 0x3f3f3f
    #define pb push_back


    int n,m,i,j,T[max_n][max_n],nr;
    char c;

    int dx[8]={0,0,1,1,1,-1,-1,-1};
    int dy[8]={1,-1,0,1,-1,0,1,-1};
    int d,dp;


    int V[max_n][max_n];
    int px,py,pnx,pny;
    int minim,act,ok;

    vector<int> rezx,rezy;

int valid ( int x, int y )
{
    if ( ( x==0 ) || ( x==n+1 ) || ( y==0 ) || ( y==m+1 ) )
        return 0;
    return 1;
}

int main()
{
    freopen ("traseu2.in","r",stdin);
    freopen ("traseu2.out","w",stdout);
    scanf ("%d %d", &n, &m );
    for ( i=1; i<=n; i++ )
        for ( j=1; j<=m; j++ )
        {
            
            scanf ("%c", &c );
            while ( c!='#' && ( ! ( ( c-'0' >= 0 ) && ( c-'0' <=9 ) ) )  )
                scanf ("%c", &c );
            if ( c=='#' )
                T[i][j]=-1;
            else{
                nr=c-'0';
                scanf ("%c", &c );
                while ( ( c-'0' >= 0 ) && ( c-'0' <=9 ) )
                {
                    nr*=10;
                    nr+=c-'0';
                    scanf ("%c", &c );
                }
                T[i][j]=nr;
            }
        }
    minim=INF;
    for ( i=1; i<=n; i++ )
        for ( j=1; j<=m; j++ )
        {
            if ( minim > T[i][j] && T[i][j]!=-1 )
            {
                minim=T[i][j];
                px=i;
                py=j;
            }
        }
    V[px][py]=1;
    act=minim;
    ok=1;
    while ( ok )
    {
        minim=INF;
        dp=-1;
        rezx.pb(px);
        rezy.pb(py);
        V[px][py]=1;
        for ( d=0; d<8; d++ )
        {
            pnx=px+dx[d];
            pny=py+dy[d];
            if ( valid ( pnx,pny ) && ( T[pnx][pny] > act ) && ( T[pnx][pny] < minim)  )
            {
                dp=d;  
                minim=T[pnx][pny];
            }
        }
        if ( dp == -1 )
        {
            ok=0;
        }
        else{
            px+=dx[dp];
            py+=dy[dp];
        }
        act=minim;
    }
    ok=1;
    for ( i=1; i<=n; i++ )
        for ( j=1; j<=m; j++ )
        {
            if ( T[i][j]!=-1 && V[i][j]==0 )
                ok=0;
        }
    if ( ok ){
        printf("Exista solutie!\n");
        printf("%d\n",rezx.size() );
        for ( i=0; i<rezx.size(); i++ )
            printf ("%d %d %d\n", rezx[i],rezy[i],T[rezx[i]][rezy[i]] );
    }
    else{
        printf("Nu exista solutie!\n");
    }
    return 0;
}   
