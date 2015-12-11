#include <cstdio>
#include <algorithm>
using namespace std;

    #define max_n 4000

    struct cord{
        int x,y,z;
    } C[max_n];

    int maxim,s,n,t,i;
    int Aib[max_n][max_n];

    int max ( int a, int b ){
        if ( a>b ){
            return a;
        }
        return b;
    }

    int query ( int x, int y ){
        int rez=0,j=y;
        for ( ; x; x-=(x&(-x)) ){
            for ( y=j; y; y-=(y&(-y)) ){
                rez=max(rez,Aib[x][y]);
            }
        }
        return rez;
    }

    void add ( int x, int y , int val, int tip ){
        int j;
        for ( ; x<=n; x+=(x&(-x)) ){
            for ( j=y; j<=n; j+=(j&(-j)) ){
                if ( tip == 0 ){
                    Aib[x][j]=max(Aib[x][j],val);
                }
                else{
                    Aib[x][j]=val;
                }
            }
        }
    }

    bool mysort ( cord a, cord b ){
        if ( a.x == b.x ){
            if ( a.y == b.y ){
                return a.z>b.z;
            }   
            else{
                return a.y>b.y;
            }
        }
        else{
            return a.x<b.x;
        }
    }

int main(){

    freopen ("cutii.in","r",stdin);
    freopen ("cutii.out","w",stdout);

    scanf ("%d %d", &n, &t);
    for ( ; t; --t ){
        maxim=0;
        for ( i=1; i<=n; i++ ){
            scanf ("%d %d %d", &C[i].x, &C[i].y, &C[i].z );
        }
        sort ( C+1, C+n+1, mysort );
        for ( i=1; i<=n; i++ ){
            s=query ( C[i].y-1 , C[i].z-1 );
            s++;
            if ( maxim < s )
                maxim=s;
            add ( C[i].y, C[i].z, s, 0 );
        }
        for ( i=1; i<=n; i++ )
            add ( C[i].y, C[i].z, 0, 1 );
        printf("%d\n",maxim);
    }
    return 0;
}
