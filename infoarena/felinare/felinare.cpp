#include<cassert>
#include<cstdio>


#include <vector>

using namespace std;

	#define max_n 10000
	#define pb push_back

bool Viz[ 2*max_n ], Cuplaj[ 2*max_n ], Rez[ 2*max_n ];
int Other[ 2*max_n ];
vector<int> Vertex[ 2*max_n ];

int n,m,i,a,b,rez;

// debug
int rezf,R[2];
// /debug

bool find_path ( int nod ){
	Viz[ nod ] = 1;
	if ( nod > n )
		return find_path ( Other[ nod ] );
	for ( int i=0; i< int ( Vertex[ nod ].size() ); ++i ){
		if ( !Cuplaj[ Vertex[ nod ][ i ] ] ){
			Cuplaj[ Vertex[ nod ][ i ] ] = 1;
			Viz[ Vertex[ nod ][ i ] ] = 1;

			Other[ nod ] = Vertex[ nod ][ i ];
			Other[ Vertex[ nod ][ i ] ] = nod;
			return 1;
		}
	}
	for ( int i=0; i< int ( Vertex[ nod ].size() ); ++i ){
		if ( ( !Viz[ Vertex[ nod ][ i ] ] ) && find_path ( Vertex[ nod ][ i ] ) ){
			Other[ nod ] = Vertex[ nod ][ i ];
			Other[ Vertex[ nod ][ i ] ] = nod;
			return 1;
		}
	}
	return 0;
}

/*void df ( int nod, int stare ){
	Rez[ nod ] = stare;
	R[ stare ] ++;
	Viz[ nod ] = 1;
	for ( int i=0; i< int ( Vertex[ nod ].size() ); ++i ){
		if ( !Viz[ Vertex[ nod ][ i ] ] ){
			df ( Vertex[ nod ][ i ] , stare^1 );
		}
	}
	return ;
} */

void df ( int nod ){
	if ( Rez[ nod ] == 2 )
		Rez[ nod ] = 1;
	else
		return ;
	for ( int i=0; i<Vertex[nod].size(); ++i ){
		Rez[ Vertex[ nod ][ i ] ] = 2;
		df ( Other[ Vertex[ nod ][ i ] ]);
	}
}

int main(){

	freopen ("felinare.in","r",stdin);
	freopen ("felinare.out","w",stdout); 
	scanf ("%d %d", &n, &m );
	for ( i=1; i<=m; ++i ){
		scanf ("%d %d", &a, &b );
		Vertex[ a ].push_back ( n+b );
		Vertex[ n+b ].push_back ( a );
	}
	bool ok=0;
	do {
		ok=0;
		for ( i=1; i<=n; ++i ){
			if ( (!Viz[ i ]) && (!Cuplaj[ i ]) ){
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
		for ( i=1; i<=2*n; ++i ){
			Viz[ i ] = 0;
		} 

	} while ( ok );

	// facem minimal vertex cover
 /*   for ( i=1; i<=2*n; ++i ){
    	if ( ( !Cuplaj[ i ] ) && ( !Viz[ i ] ) ){
//			R[0]=R[1]=0;
			df ( i, 1 );
//			assert ( R[1] >= R[0] );
		}
	}
	for ( i=1; i<=2*n; ++i ){
		if ( !Viz[ i ] ){
//			R[1]=R[0]=0;
			df ( i, 1 );
 //   		assert ( R[1] >= R[0] );
		}
	}
	int s=0;
	for ( i=1; i<=2*n; ++i ){
		s+=Rez[i];
	}
	assert ( s >= 2*n-rez );*/

	for ( i=1; i<=n; ++i ){
		// 1 = good
		// 2 = bad
		Rez[ i ] = 2;
		Rez[ i+n ] = 1;
	}
	for ( i=1; i<=n; ++i ){
        if ( !Cuplaj[ i ] ){
			df ( i );
		}
	}

	printf("%d\n",2*n-rez);
	for ( i=1; i<=n; ++i ){
		int p = 0;
		if ( Rez[ i ] == 1 )
			p++;
		if ( Rez[ n+i ] == 1 )
			p+=2;
//		p += Rez[ i ] + 2*Rez[ n+i ];
		printf("%d\n", p );
	}

	return 0;
}
