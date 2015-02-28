#include <cstdio>

#include <algorithm>
#include <queue>
using namespace std;

const int max_n=50005, INF=0x3f3f3f3f;

#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define fi first
#define se second


int Best[max_n];
bool Viz[max_n];
int n, m, i, a, b, c;

priority_queue< pair<int,int> > PQ;
vector< pair<int,int> > Vertex[max_n];

int main(){
	freopen("dijkstra.in","r",stdin);
	freopen("dijkstra.out","w",stdout);
	scanf("%d %d", &n, &m );
	while( m-- ){
		scanf("%d %d %d", &a, &b, &c );
 		Vertex[a].push_back( make_pair( b ,c ) );
	}
	for( i=2; i<=n; ++i )
		Best[i] = INF;
	PQ.push( make_pair( 0, 1 ) );
	while( !PQ.empty() ){
		int nod = PQ.top().second;
		PQ.pop();
		if( !Viz[nod] ){ 	// o pereche de forma -Best[i], i poate sa apara de mai multe ori in priority_queue pentru ca de fiecare daca cand ii facem cate un update, o re-introducem cu noul cost
							// pe noi ne intereseaza doar prima aparitie a lui 'i', cea cu costul minim
			Viz[nod] = true;
			FORIT( it,Vertex[nod] )
				if( Best[ it->fi ] > Best[nod] + it->se ){
					Best[ it->fi ] = Best[nod] + it->se;
					PQ.push( make_pair( -Best[ it->fi ], it->fi ) );
					// it->fi e un vecin a lui 'nod' pt care am facut o imbunatatire
					// Am actualizat Best[ it->fi ] cu Best[nod] + costul muchiei
					// Am pus in PQ -Best, deoarece e max-Heap ( primul element e maxim -> noi vrem sa fie minim -> punem *(-1) )
				}
		}
	}
	for( i=2; i<=n; ++i )
		if( Best[i] == INF )
			printf("0 ");
		else
			printf("%d ", Best[i] );
	return 0;
}

