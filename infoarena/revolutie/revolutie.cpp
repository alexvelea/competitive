#include <cstdio>

#include <algorithm>
#include <vector>
using namespace std;

	#define max_n 130 

bool Viz[ 2*max_n ], Cuplaj[ 2*max_n ];
int Other[ 2*max_n ];
vector<int> Vertex[ max_n ];
vector<int> Rez;

int n,i,j,a,rez;

bool find_path ( int nod ){
    Viz[ nod ] = 1;
	if ( nod > n )
		return find_path ( Other[ nod ] );
	for ( int i=0; i< Vertex[ nod ].size(); ++i ){
		if ( !Cuplaj[ Vertex[ nod ][ i ] ] ){
        	Cuplaj[ Vertex[ nod ][ i ] ] = 1;
			Other[ nod ] = Vertex[ nod ][ i ];
			Other[ Vertex[ nod ][ i ] ] = nod;
			return 1;
		}
	}
	for ( int i=0; i< Vertex[nod].size(); ++i ){
		if ( !Viz[ Vertex[ nod ][ i ] ] && find_path ( Vertex[ nod ][ i ] ) ){
			Other[ nod ] = Vertex[ nod ][ i ];
			Other[ Vertex[ nod ][ i ] ] = nod;
			return 1;
		}
	}
	return 0;
}

int main(){

	freopen ("revolutie.in","r",stdin);
	freopen ("revolutie.out","w",stdout);

	scanf ("%d", &n );
	for ( i=1; i<=n; ++i ){
		for ( j=1; j<=n; ++j ){
			scanf ("%d", &a );
        	if ( a ){
				Vertex[ i ].push_back ( j+n );
			}
		}
	}
	bool ok=1;
	do {
		ok=0;
		for ( i=1; i<=2*n; ++i ){
			Viz[ i ] = 0;
		}
		for ( i=1; i<=n; ++i ){
			if ( !Viz[ i ] && !Cuplaj[ i ] ){
				Cuplaj[ i ] = 1;
				if ( find_path ( i ) ){
					rez++;
					ok=1;
				}
				else{
					Cuplaj[ i ] = 0;
				}
			}
		}
	} while ( ok );
	
	if ( rez != n ){
 		printf("-1\n");
	}
	else{
		for ( i=1; i<=n; ++i ){
			if ( Other[ i ] != n+i ){
				int a=i;
				int b=Other[ n+i ];
				Rez.push_back ( a );
				Rez.push_back ( b );
				swap ( Other[ Other[ a ] ], Other[ Other[ b ] ] );
				swap ( Other[ a ], Other[ b ] );
			}
		}
		printf("%d\n", Rez.size()/2 );
		for ( i=0; i< Rez.size(); i+=2 ){
			printf("L %d %d\n", Rez[ i ], Rez[ i+1 ] );
		}
	}

	return 0;
}           
