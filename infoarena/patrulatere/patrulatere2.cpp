#include <cstdio>
#include <algorithm>
using namespace std;
 
#define max_n 260
#define INF 0x3f3f3f3f
 
struct point{
    int x,y;
} Point[max_n];
 
int n,rez,nr;
int i,j,l;
int Under[max_n][max_n];
 
bool under( point a, point b, point target ){
    if( a.x == b.x )
        return 0;
    if( a.x > b.x )
        swap(a,b);
    int d=b.x-a.x;
    if( target.x >= a.x && target.x <= b.x )
        ;
    else
        return 0;
    if( target.x == a.x )
        return 0;
    int y=a.y+(1.0*(target.x-a.x)/d*(b.y-a.y));
    if( y>=target.y )
        return 1;
    return 0;
}
 
int main(){
    freopen("patrulatere.in","r",stdin);
    freopen("patrulatere.out","w",stdout);
     
    scanf("%d", &n );
    for( i=1; i<=n; ++i ){
        scanf("%d %d", &Point[i].x, &Point[i].y );
    }
    for( i=1; i<=n; ++i ){
        for( j=i+1; j<=n; ++j ){
            nr=0;
            for( l=1; l<=n; ++l ){
                if( l!=i && l!=j ){
                    nr+=under( Point[i], Point[j], Point[l] );
                }
            }
            Under[i][j]=Under[j][i]=nr;
        }
    }   
    int rez=(1LL*n*(n-1)*(n-2)*(n-3)/24);
    int imin,imax;
    int a,xmin,xmax;
    for( i=1; i<=n; ++i )
        for( j=i+1; j<=n; ++j )
            for( l=j+1; l<=n; ++l ){
                xmin=min( Point[i].x, min( Point[j].x, Point[l].x ) );
                xmax=max( Point[i].x, max( Point[j].x, Point[l].x ) );
                a=-INF;
                if( Point[i].x == xmin && Point[i].y>a ){
                    imin=i;
                    a=Point[i].y;
                }
                if( Point[j].x == xmin && Point[j].y>a ){
                    imin=j;
                    a=Point[j].y;
                }
                if( Point[l].x == xmin && Point[l].y>a ){
                    imin=l;
                    a=Point[l].y;
                } 
 
                a=-INF;
                if( Point[i].x == xmax && Point[i].y>a ){
                    imax=i;
                    a=Point[i].y;
                }
                if( Point[j].x == xmax && Point[j].y>a ){
                    imax=j;
                    a=Point[j].y;
                }
                if( Point[l].x == xmax && Point[l].y>a ){
                    imax=l;
                    a=Point[l].y;
                }
                int other=i+j+l-imin-imax;
                if( under( Point[imin], Point[imax], Point[other] ) ){
                    rez-=Under[imin][imax]-Under[imin][other]-Under[other][imax]-1;
                }else{
                    rez-=Under[other][imin]+Under[other][imax]-Under[imin][imax];
                }
            }
    printf("%d\n",rez);
    return 0;
}