#include <cstdio>
#include <algorithm>
using namespace std;

    #define max_n 1005

    struct point{
        int x,y;
    } T[max_n],Rez[max_n*max_n];

    int i,j,n,m;
    int x,y,d,rez;

    int cmmdc( int a, int b ){
        if ( b==0 )
            return a;
        if ( a==0 )
            return b;
        return cmmdc(b,a%b);
    }


    bool mysort ( point a, point b ){
        if ( a.x == b.x )
            return a.y<b.y;
        return a.x<b.x;
    }

int main(){

        freopen ("trapez.in","r",stdin);
        freopen ("trapez.out","w",stdout);
    
    scanf ("%d", &n );
    for ( i=1; i<=n; i++ ){
        scanf ("%d %d", &T[i].x, &T[i].y );
    }
    for ( i=1; i<=n; i++ ){
        for ( j=i+1; j<=n; j++ ){
            x=T[i].x-T[j].x;
            y=T[i].y-T[j].y;

            d=cmmdc(x,y);
            x/=d;
            y/=d;

            if ( y < 0 ){
                x*=-1;
                y*=-1;
            }
            Rez[++m].x=x;
            Rez[  m].y=y;
        }
    }
    sort ( Rez+1, Rez+1+m, mysort );
    for ( i=1; i<=m; ){
        j=i;
        while ( (i<=m) && ( Rez[i].x == Rez[j].x ) && ( Rez[i].y==Rez[j].y ) ){
            i++;
        }
        rez+=(i-j)*(i-j-1)/2;
    }
    printf("%d\n",rez);
    return 0;
}
