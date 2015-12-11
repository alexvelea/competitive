#include <cstdio>

#include <vector>

using namespace std;

	#define max_n 10005

vector <int> Vertex[ 2*max_n ];
bool Viz[ 2*max_n ], Cuplaj[ 2*max_n ];
int Other[ 2*max_n ];

int n,m,e,i,a,b,rez;

bool find_matching ( int nod ){
	Viz[ nod ] = 1;
	if ( !Cuplaj[ nod ] && nod > n ){
		Cuplaj[ nod ] = 1;
		return 1;
	}
	if ( nod > n ){
		return find_matching ( Other[ nod ] );
	}
	for ( int i=0; i< Vertex[ nod ].size(); ++i ){
		if ( !Cuplaj[ Vertex[ nod ][ i ] ] ){
			Cuplaj[ Vertex[ nod ][ i ] ] = 1;
			Viz[ Vertex[ nod ][ i ] ] = 1;

			Other[ nod ] = Vertex[ nod ][ i ];
			Other[ Vertex[ nod ][ i ] ] = nod;

			return 1;
		}
	}
	for ( int i=0; i< Vertex[ nod ].size(); ++i ){
    	if ( ( !Viz[ Vertex[ nod ][ i ] ] ) && find_matching ( Vertex[ nod ][ i ] ) ){
            Other[ nod ] = Vertex[ nod ][ i ];
			Other[ Vertex[ nod ][ i ] ] = nod;
			return 1;
		}
	}
	return 0;
}

int main(){

	freopen ("cuplaj.in","r",stdin);
	freopen ("cuplaj.out","w",stdout);

	scanf ("%d %d %d", &n, &m, &e );
	for ( i=1; i<=e; ++i ){
		scanf ("%d %d", &a, &b );
		b += n;
		Vertex[ a ].push_back ( b );
	}
	int ok=0;
	do {
		ok=0;
		for ( i=1; i<=n+m; ++i ){
			Viz[ i ] = 0;
		}
		for ( i=1; i<=n; ++i ){
			if ( !Viz[ i ] && !Cuplaj[ i ] ){
				Cuplaj[ i ] = 1;
				if ( find_matching ( i ) ){
					rez++;
					ok=1;
				}
				else{
					Cuplaj[ i ] = 0;
				}
			}
		}
		
	} while ( ok );
    printf("%d\n", rez );
	for ( i=1; i<=n; ++i ){
		if ( Cuplaj[ i ] ){
			printf("%d %d\n", i, Other[ i ]-n );
		}
	}
	return 0;
}
