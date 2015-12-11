#include <cstdio>
#include <algorithm>
using namespace std;

    #define prec 100000
    #define max_n 15005
    #define R3 1.7320508075688
    
    int abs ( int a ){  
        #define eps 150
        if ( ( a >= -eps ) && ( a<= eps ) )
            return 1;
        return 0;
    }

    struct point{
        int x,y;
    } T[max_n];

    int i,j,n,re;
    float a,b;

    bool mysort ( point a, point b ){
        if ( abs(a.x - b.x) ) {
            return a.y<b.y;
        }
        return a.x<b.x;
    }

    bool maimic ( point a, point b ){
        if ( abs ( a.x - b.x ) ){
            if ( abs ( a.y-b.y ) ){
                return 1;
            }
            return a.y<b.y;
        }
        return a.x<b.x;
    }

    void find ( point a ){
        int rez=j+1,ind;
        for ( ind=1; ind<n; ind<<=1 )
            ;
        for ( ; ind; ind>>=1 ){
            if ( ( rez+ind <=n ) ){
                if ( maimic ( T[rez+ind], a ) ) {
                    rez+=ind;
                }
            }
        }
        if ( ( abs( T[rez].x - a.x ) ) && ( abs( T[rez].y - a.y ) ) ){
            re++;
        }
    }


    void solve ( point a, point b ){
        // cautam punctul |c|
        point c;
        c.x=a.x + (b.x-a.x)/2.0 - ( b.y-a.y )*R3/2;
        c.y=a.y + (b.x-a.x)*R3/2 + (b.y-a.y)/2.0;
        find ( c );

        c.x=a.x + (b.x-a.x)/2.0 + ( b.y-a.y )*R3/2;
        c.y=a.y - (b.x-a.x)*R3/2 + (b.y-a.y)/2.0;
        find ( c );
    }

int main(){
        freopen ("triang.in","r",stdin);
        freopen ("triang.out","w",stdout);
    scanf ("%d", &n );
    for ( i=1; i<=n; i++ ){
        scanf ("%f %f", &a, &b );
        T[i].x=prec*a;
        T[i].y=prec*b;
    }
    sort ( T+1, T+n+1, mysort );
    for ( i=1; i<n; i++ ){
        for ( j=i+1; j<n; j++ ){
            solve ( T[i], T[j] );
        }
    }
    printf("%d", re);
    return 0;
}
