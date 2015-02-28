#include <cstdio>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

#define fi first
#define se second
#define mp make_pair

const int max_n = 1005, max_c = 1005, INF=0x3f3f3f3f;

vector< pair<int,int> > Vertex[max_n];
int Best[max_n][max_c];
int Cost[max_n];

int n, m, k, S, D;
int a, b, t;


void get_min( int &a, int b ){
	if( a>b )
		a = b;
}

void make_graph( int nod, int k ){
	int i, t;
	for( t=0; t<=k; ++t )
		for( i=1; i<=n; ++i )
			Best[i][t] = INF;
	for( t=0; t<=k; ++t )
		Best[nod][t] = 0;
	for( t=0; t<=k; ++t ){

		if( t )
			for( i=1; i<=n; ++i )
				get_min( Best[i][t], Best[i][t-1] );

		for( i=1; i<=n; ++i )
			if( !t || Best[i][t] < Best[i][t-1] )
				FORIT( it, Vertex[i] )
					if( t+Cost[ it->fi ] <= k )
						get_min( Best[it->fi][ t+Cost[it->fi] ], Best[i][t] + it->se );
	}
}

int main(){
	
   	int i;

	freopen("drum-bugetat.in","r",stdin);
	freopen("drum-bugetat.out","w",stdout);
	
	scanf("%d %d %d", &n, &m, &k );
	scanf("%d %d", &S, &D );
	
	for( i=1; i<=n; ++i )
		scanf("%d", &Cost[i] );
	
	for( i=1; i<=m; ++i ){
		scanf("%d %d %d", &a, &b, &t );
		Vertex[a].push_back( make_pair( b, t ) );
		Vertex[b].push_back( make_pair( a, t ) );
	}
	
	make_graph( S, k );
	
	if( Best[D][k] == INF ){
		printf("-1\n");
		return 0;
	}
	int t;
	for( t = k; t>=0 && Best[D][t] == Best[D][k]; --t )
		;
	t++;
	printf("%d %d\n", Best[D][k], t );
	return 0;
}

