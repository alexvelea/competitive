#include <cstdio>

#include <queue>
#include <vector>
using namespace std;


	#define pb push_back
	#define max_n 50005
	#define max_m 250005
	#define INF 0x3f3f3f3f

struct edge {
	int a,b,cost;
} Edge[ max_m ];

struct nod {
	int cost,ind;
	bool operator< ( const nod &b ) const {
		return cost > b.cost;
	}
} ;
priority_queue<nod> PQ;

vector<int> Vertex[ max_n ];
bool Viz[ max_n ];

int n,m,i;
int Best[ max_n ];

int main(){

    freopen ("dijkstra.in","r",stdin);
	freopen ("dijkstra.out","w",stdout);

	scanf ("%d %d", &n, &m );

    for ( i=2; i<=n; ++i ){
		Best[ i ] = INF;
	}

	for ( i=1; i<=m; ++i ){
		scanf ("%d %d %d", &Edge[ i ].a, &Edge[ i ].b, &Edge[ i ].cost );
		Vertex[ Edge[ i ].a ]. pb ( i );
 //   	Vertex[ Edge[ i ].b ]. pb ( i );
	}
	nod act;
	act.cost = 0;
	act.ind = 1;
	PQ.push( act );

	while ( PQ.size() ){
		nod act = PQ.top();
		PQ.pop();
		if ( !Viz[ act.ind ] ){
			Viz[ act.ind ] = 1;
			for ( i=0; i< Vertex [ act.ind ].size(); ++i ){
				int other = Edge[ Vertex[ act.ind ][ i ] ].a + Edge[ Vertex[ act.ind ][ i ] ].b - act.ind ;
				if ( Best[ other ] > act.cost + Edge[ Vertex[ act.ind ][ i ] ].cost ){
					Best[ other ] = act.cost + Edge[ Vertex[ act.ind ][ i ] ].cost;
					nod nx;
					nx.cost = Best[ other ];
					nx.ind = other;
					PQ.push( nx );
				}
			}
		}
	}

	for ( i=2; i<=n; ++i ){
		if ( Best[ i ] == INF ){
			printf("0 ");
		}
		else{
			printf("%d ", Best[ i ] );
		}
	}
	return 0;
}
