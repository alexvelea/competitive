#include <cstdio>

#include <vector>

using namespace std;

	#define max_n 100005
	#define pb push_back

vector<int> Rez, T[ max_n ];
bool Viz[ max_n ];

int last,act,	i,j,n;
int a,b;


bool gasit ( int nr, int ind ){
	for ( int i=0; i< T[ ind ].size(); ++i ){
		if ( T[ ind ][ i ] == nr )
			return 1;
	}
	return 0;
}

void afisare (){
	for ( int i=0; i<Rez.size(); ++i ){
		printf("%d ", Rez[i] );
	}
	printf("\n");
}

int PP[20];
int final=0;

void bt ( int nr ){
	if ( nr == n ){
		int ok=1;
		for ( int i=3; i<=3+n; ++i ){
			for ( int j=0; j<4; ++j ){
				int g=0;
				for ( int l=i-2; l<=i+2; ++l ){
					if ( PP[ l ] == T[ PP[ i ] ][ j ] )
						g=1;
				}
				if ( !g )
					ok=0;
			}
		}
		if ( ok && (!final) ){
			final=1;
			for ( int i=1; i<=n; ++i )
				printf("%d ",PP[ i ] );
		}
	}
	else{
		for ( int i=1; i<=n; ++i ){
			if ( !Viz[ i ] ){
				Viz[ i ]=1;
				PP[ nr+1 ] = i;
				PP[ nr+1+n ] = i;
				bt ( nr+1 );
				Viz[ i ]=0;
			}
		}
	}
}

int main(){
	scanf ("%d", &n );
	
	for ( i=1; i<=2*n; ++i ){
		scanf ("%d %d", &a, &b );
		T[ a ].pb( b );
		T[ b ].pb( a );
	}

	if ( n <= 6 ){
		bt ( 0 );
		if ( !final )
			printf("-1\n");
		return 0;
	}

	// il punem pe 1 in capul listei
	Viz[ 1 ]=1;
	Rez.pb( 1 );
	for ( i=0; i<4; ++i ){
		act = T[ 1 ][ i ];
        int nr=0;
		for ( j=0; j<4; ++j ){
			if ( gasit( T[ act ][ j ], 1 ) ){
// 				printf("%d - %d\n",act, T[ act ][ j ]);
				nr++;
			}
		}
//		printf("\n");
		if ( nr == 1 ){
			for ( j=0; j< T[ 1 ].size(); ++j ){
				if ( gasit( T[ act ][ j ], 1 ) ){
					Rez.pb( T[ act ][ j ] );
					Viz[ T[ act ][ j ] ] = 1;
				}
			}
			Rez.pb( act );
			Viz[ act ]=1;
			i=5;
		}
	}

/*	debug
	afisare();*/

	int ok=1;
	for ( i=4; i<=n && ok; ++i ){
		act = Rez[ Rez.size()-1 ];
		last = Rez[ Rez.size()-2 ];
		int fnd = 0;
		for ( j=0; j< T[ last ].size(); ++j ){
			if ( gasit ( T[ last ][ j ], act ) && ( !( Viz[ T[ last ][ j ] ] ) ) ){
//				printf("%d !! \n", T[ last ][ j ] );
				Viz[ T[ last ][ j ] ] = 1;
				Rez.pb ( T[ last ][ j ] );
                fnd = 1;
			}
		}
		if ( !fnd ){
			ok=0;
		}
	}
	if ( ok ){
		for ( i=0; i<Rez.size(); ++i ){
			printf("%d ", Rez[ i ] );
		}
	}
	else{
		printf("-1\n");
	}
		
	return 0;
}


