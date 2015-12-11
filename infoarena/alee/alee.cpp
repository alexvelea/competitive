#include <cstdio>
using namespace std;

    #define max_n 180

    int n,m,i,a,b;
    int x1,x2,y1,y2;
    int u,p;
    bool Pos[max_n][max_n];
    struct xycost{
        short x,y,cost;
    } Bf[max_n*max_n];

    int dx[4]={0,0,1,-1};
    int dy[4]={1,-1,0,0};

    bool valid ( int x, int y ){
        if ( x==0 || y==0 || x==n+1 || y==n+1 )
            return 0;
        return 1;
    }

int main(){

        freopen ("alee.in","r",stdin);
        freopen ("alee.out","w",stdout);

    scanf ("%d %d", &n, &m );
    for ( i=1; i<=m; i++ ){
        scanf ("%d %d", &a, &b );
        Pos[a][b]=1;
    }
    scanf ("%d %d %d %d", &x1, &y1, &x2, &y2 );
    Bf[0].x=x1;
    Bf[0].y=y1;
    Bf[0].cost=1;
    while ( p <= u ){  
        if ( Bf[p].x == x2 && Bf[p].y == y2 ){
            printf("%d\n",Bf[p].cost);
            return 0;
        }
        for ( i=0; i<4; i++ ){
            if ( valid ( Bf[p].x+dx[i], Bf[p].y+dy[i] ) && !Pos[ Bf[p].x+dx[i] ][ Bf[p].y+dy[i] ] ){
                Pos[ Bf[p].x + dx[i] ][ Bf[p].y + dy[i] ]=1;
                Bf[++u].x=Bf[p].x + dx[i];
                Bf[  u].y=Bf[p].y + dy[i];
                Bf[  u].cost=Bf[p].cost+1;
            }
        }
        p++;
    }
    return 0;
}
