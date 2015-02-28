// 22:15
#include <cstdio>

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

#define max_n 200005
#define max_m 400005
#define pb push_back
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

struct muchie {
	int a,b,c;
	muchie(){
		a=b=c=0;
	}
	int other( int nod ){
		return a+b-nod;
	}
	bool operator< ( const muchie b ) const {
		return b.c < c;
	}
} Edge[ max_m ];

int n,m,rez,i;
bool Viz[ max_n ];
vector <muchie> Rez;
priority_queue <muchie> PQ;
vector <int> Vertex[ max_n ];

void Expand( int nod ){
	Viz[ nod ] = 1;
	FORIT ( it, Vertex[ nod ] ){
		PQ.push( Edge[ *it ] );
	}
	return ;
}

int main(){
	freopen("apm.in","r",stdin);
	freopen("apm.out","w",stdout);
	scanf("%d %d", &n, &m );
	for ( i=1; i<=m; ++i ){
		scanf("%d %d %d", &Edge[ i ].a, &Edge[ i ].b, &Edge[ i ].c );
		Vertex[ Edge[ i ].a ].pb( i );
		Vertex[ Edge[ i ].b ].pb( i );
	}
	Expand( 1 );
	muchie edge;
	int nod;
	while( PQ.size() ){
		edge = PQ.top();
		PQ.pop();
		nod = edge.a;

		if ( Viz[ nod ] ) 
			nod = edge.other( nod );
        if ( !Viz[ nod ] ){
			rez += edge.c;
			Rez.pb( edge ); 
			Expand( nod );
		}
	}
	printf("%d\n%d\n",rez,n-1);
	FORIT( it, Rez )
		printf("%d %d\n", it->a, it->b );
	return 0;
}
