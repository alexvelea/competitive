#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int max_t=105, max_n=55, max_m=305, INF=100;
const int Source=51, Sink=52;

#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

char Start[max_n];
char C[max_n*max_t][max_n*max_t];

queue<int> Deq;
vector<int> Vertex[max_t*max_n];
vector< pair<int,int> > StartEdge[max_n];
int From[max_t*max_n], MaxFlow, Target;

int n, m;
int a, b, L;
int i, T;

char min( int a, int b ){
	if( a<b )
		return a;
	return b;
}

void make_empty(){
	while( !Deq.empty() )
		Deq.pop();
	for( int i=0; i<max_t*max_n; ++i )
		From[i]=0;
}

bool Find_Flow(){
	int mn=INF, nod;
	make_empty();
	Deq.push(Source);
	From[Source]=Source;
	while( !Deq.empty() ){
		if( From[Sink] )
			break;
		nod = Deq.front();
		Deq.pop();
		FORIT( it,Vertex[nod] ){
			if( C[nod][*it] && !From[*it] ){
				From[*it]=nod;
				Deq.push( *it );
			}
		}
	}
	if( From[Sink] )
		;
	else
		return false;
	for( nod=Sink; nod!=Source; nod=From[nod] ) 
		mn = min( mn, C[From[nod]][nod] );
	for( nod=Sink; nod!=Source; nod=From[nod] ){
		C[From[nod]][nod]-=mn;
		C[nod][From[nod]]+=mn;
	}
	MaxFlow += mn;
	return true;
}

void AddEdge( int T ){
	for( int i=1; i<=n; ++i )
		FORIT( it, StartEdge[i] ){
			C[ (T)*max_n + i ][ (T+1)*max_n + it->first ] = it->second;
 			Vertex[ (T)*max_n + i ].push_back( (T+1)*max_n + it->first );
			Vertex[ (T+1)*max_n + it->first ].push_back( (T)*max_n + i );
		}
	C[ (T+1)*max_n + 1 ][Sink]=INF;
	Vertex[ (T+1)*max_n + 1 ].push_back( Sink );
	return ;
}

int main(){
	freopen("algola.in","r",stdin);
	freopen("algola.out","w",stdout);

	scanf("%d %d", &n, &m );
	for( i=1; i<=n; ++i ){
		scanf("%d", &Start[i] );
		Target += Start[i];
	}
	for( i=1; i<=m; ++i ){
		scanf("%d %d %d", &a, &b, &L );
		StartEdge[a].push_back( make_pair( b, L ) );
		StartEdge[b].push_back( make_pair( a, L ) );
	}
 	for( i=1; i<=n; ++i ){
        StartEdge[i].push_back( make_pair( i, INF ) );

		C[Source][i] = Start[i];
		Vertex[i].push_back( Source );
		Vertex[Source].push_back( i );
	}
	C[1][Sink]=INF;
 	Vertex[1].push_back(Sink);
	for( T=0; ; ++T ){
		while( Find_Flow() )
			;
		if( Target == MaxFlow ){
			printf("%d\n",T);
			return 0;
		}
		AddEdge( T );
	}
	return 0;
}

