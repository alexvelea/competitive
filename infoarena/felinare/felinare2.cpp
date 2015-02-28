#include <cassert>
#include <cstdio>       
 
#include <vector>
 
using namespace std;
 
    #define max_n 10000
    #define pb push_back 
 
int Other[ 2*max_n ];
int Rez[ 2*max_n ];
bool Viz[ 2*max_n ];
int n;
int R[2];
 
vector<int> Vertex[ 2*max_n ];
 
bool find_path ( int nod ){
    if ( Viz[ nod ] )
        return 0;
    Viz[ nod ] = 1;
    for ( int i=0; i< Vertex[ nod ].size(); ++i ){
        if ( !Other[ Vertex[ nod ][ i ] ] || find_path ( Other[ Vertex[ nod ][ i ] ] ) ){
            Other[ nod ] = Vertex[ nod ][ i ];
            Other[ Vertex[ nod ][ i ] ] = nod;
            return 1;
        }
    }
    return 0;
}
 
void df ( int nod, int stare ){
    if ( Viz[ nod ] == 1 )
        return ;
    R[ stare ] ++;
    Viz[ nod ] = 1;
    Rez[ nod ] = stare;
    for ( int i=0; i< Vertex[ nod ].size(); ++i ){
        Rez[ Vertex[ nod ][ i ] ] = stare^1;
        Viz[ Vertex[ nod ][ i ] ] = 1 ;
        df ( Other[ Vertex[ nod ][ i ] ] , stare );
    }
    return ;
}
 
int main(){
 
    freopen ("felinare.in","r",stdin);
    freopen ("felinare.out","w",stdout);
 
    int m;
    int a,b;
    scanf ("%d %d", &n, &m );
    for ( ; m; --m ){
        scanf ("%d %d", &a, &b );
        Vertex[ a ]. pb ( n+b );
        Vertex[ n+b ]. pb ( a );
    }
 
    bool ok;
    int rez=0;
    do {
        ok = false;
        for ( int i=1; i<=n; ++i ){
            if ( !Other[ i ] ){
                if ( find_path ( i ) ){
                    ok=1; 
                    rez ++;
                }
            }
        }
        for ( int i=1; i<=2*n; ++i )
            Viz[ i ] = false ;
    } while ( ok );
 
    printf("%d\n",2*n-rez);
 
    for ( int i=1; i<=2*n; ++i ){
        if ( !Other[ i ] && !Viz[ i ] ){
            R[1]=R[0]=0;
            df ( i,1 );
            assert ( R[1] > R[0] );
        }
    }
    for ( int i=1; i<=2*n; ++i ){
        if ( Viz[ i ] == 0 ){
            R[1]=R[0]=0;
            df ( i,1 );
            assert( R[1] >= R[0] );
        }
    }
    for ( int i=1; i<=n; ++i ){
        int p=0;
        if ( Rez[ i ] == 1 )
            p++;
        if ( Rez[ i+n ] == 1 )
            p+=2;
        printf("%d\n",p);
    }
    return 0;
}
