#include <cstdio>

#include <iostream>
#include <queue>

using namespace std;

#define max_t 125
#define max_n 1050
#define max_m 16050
#define INF 0x3f3f3f3f
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

int Best[ max_t ][ max_n ];
bool PQVertexViz[ max_t ][ max_n ];

struct nod {
	int Timp,Ind,ValBest;
	nod (){
		Timp=Ind=0;
		ValBest = INF;
	}
	nod ( int a, int b ){
		Timp = a;
		Ind = b;
		ValBest = INF;
	}
	bool operator < ( nod const &b ) const{
		return b.ValBest < ValBest;
	}
	bool viz (){
		return PQVertexViz[ Timp ][ Ind ];
	}
	void set_viz( bool a ){
		PQVertexViz[ Timp ][ Ind ] = a;
	}
	int global_best(){
		return Best[ Timp ][ Ind ];
	}
	void set_best( int val ){
		Best[ Timp ][ Ind ] = val;
		ValBest = val;
	}
} ;
priority_queue<nod> PQ;

bool VertexViz[ max_t ][ max_n ], EdgeViz[ max_t ][ max_m ];

int Direction[ 2 ] = { +1, -1 }, dir;
int n,m,p,i,j,a,b;
int Cost[ max_n ], Edge[ max_n ][ max_n ];
vector<int> Vertex[ max_n ];
int Length, Where, Ind, Next, Cop[ 15 ], t;

int main(){

	freopen("patrol.in","r",stdin);
	freopen("patrol.out","w",stdout);

	scanf("%d %d %d", &n, &m, &p );
	for ( i=1; i<=n; ++i ){
		scanf("%d", &Cost[ i ] );
	}
	for ( i=1; i<=m; ++i ){
		scanf("%d %d", &a, &b );
		Vertex[ a ].push_back(b);
		Vertex[ b ].push_back(a);
		Edge[ a ][ b ] = i;
		Edge[ b ][ a ] = i;
	}
	for ( i=1; i<=p; ++i ){
 		scanf("%d", &Length );
		for ( j=1; j<=Length; ++j ){
			scanf("%d", &Cop[ j ]);
		}
		Where = 1;
		dir = 0;
		for ( t=0; t<120; ++t ){
			VertexViz[ t ][ Cop[ Where ] ] = 1;
			if ( Where + Direction[ dir ] == 0 || Where + Direction[ dir ] == Length+1 )
				dir^=1;
			Next = Where + Direction[ dir ];
			EdgeViz[ t ][ Edge[ Cop[ Where ] ][ Cop[ Next ] ] ] = 1;
			Where = Next;
		}
	}
	for ( t=0; t<=120; ++t ){
		EdgeViz[ t ][ 0 ] = 1;
	}
	for ( i=1; i<=n; ++i )
		VertexViz[ 120 ][ t ] = 1;
	for ( t = 0; t<120; ++t ){
		for ( i=1; i<=n; ++i ){
			Best[ t ][ i ] = INF;
		}
	}
	Best[ 0 ][ 1 ] = Cost[ 1 ];
	PQ.push( nod( 0,1 ) );
	bool ok=1;
	while ( PQ.size() && ok ){
		nod act = PQ.top();
		PQ.pop();
		if ( !act.viz() ){
			if ( act.Ind == n )
				ok=0;
			act.set_viz( 1 );
			FORIT( it, Vertex[ act.Ind ] ){
				if ( !VertexViz[ act.Timp+1 ][ *it ] && !EdgeViz[ act.Timp ][ Edge[ act.Ind ][ *it ] ] ){
					// mergeeee.
					nod Next( act.Timp+1, *it );
					if ( Next.global_best() > act.global_best() + Cost[ *it ] ){
                    	Next.set_best( act.global_best() + Cost[ *it ] );
						PQ.push( Next );
					}
				}
			}
		}
	}
	int minim = INF;
	for ( t=0; t<120; ++t ){
		if ( Best[ t ][ n ] < minim ){
			minim = Best[ t ][ n ];
		}
	}
	if ( minim == INF )
		printf("-1\n");
	else
		printf("%d\n",minim);
	return 0;
}
