#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

#define max_n 1005
#define FORIT( it, v ) for( typeof((v).begin()) it = (v).begin(); it!=(v).end(); ++it )
#define pb push_back

int n,m,a,b,c,i,maxflow;
int Father[ max_n ], Bfs[ max_n ];
int Edge[ max_n ][ max_n ];
vector<int> Vertex[ max_n ];

bool bfs(){
	int st,dr,nod;
	st=dr=1;
	Bfs[ 1 ] = 1;
	while ( st<=dr ){
		nod = Bfs[ st++ ];
		if ( nod == n )
			continue;
		FORIT( it, Vertex[ nod ] ){
			if ( !Father[ *it ] && Edge[ nod ][ *it ]>0 ){
				Father[ *it ] = nod;
				Bfs[ ++dr ] = *it;
			}
		}
	}
	bool ok=0;
	int m;
 	FORIT( it, Vertex[ n ] ){
		if ( Father[ *it ] || *it == 1 ){
			nod = *it;
			m = Edge[ nod ][ n ];
			if ( m>0 ){
				while( nod!=1 ){
					m = min( m, Edge[ Father[ nod ] ][ nod ] );
					nod = Father[ nod ];
				}
				if( m>0 ){
 					ok=1;
					maxflow+=m;
					nod = *it;
					Edge[ nod ][ n ] -= m;
					Edge[ n ][ nod ] += m;
					while ( nod!=1 ){
						Edge[ Father[ nod ] ][ nod ] -= m;
						Edge[ nod ][ Father[ nod ] ] += m;
						nod = Father[ nod ];
					}
				}
			}
		}
	}
	return ok;
}

int main(){
	freopen("maxflow.in","r",stdin);
	freopen("maxflow.out","w",stdout);
	scanf ("%d %d", &n, &m );
	for( ; m; --m ){
		scanf("%d%d%d",&a,&b,&c);
		Edge[ a ][ b ] = c;
		Vertex[ a ].pb( b );
		Vertex[ b ].pb( a );
	}
	Father[ 1 ] = 1;
	while ( bfs () ){
		for( i=2; i<=n; ++i ){
			Father[ i ] = 0;
		}		
	}
	printf("%d", maxflow);
	return 0;
}
