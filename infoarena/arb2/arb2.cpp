#include <cstdio>

#include <vector>
using namespace std;

#define max_n 100005
#define pb push_back
#define FORIT( it, v ) for( typeof( (v).begin() ) it=(v).begin(); it!=(v).end(); ++it )

struct muchie {
	int nod,l,c;
} Edge;

int get_max ( int a, int b ){
	if ( a > b )
		return a;
	return b;
}
int get_min ( int a, int b ){
	if ( a < b )
		return a;
	return b;
}

bool Viz[ max_n ];
int LungMax[ max_n ], Best[ max_n ];
int i,n;
long long rez;

vector<muchie> Vertex[ max_n ];

int find ( int nod ){
	Viz[ nod ] = true;
	int s=0;
	FORIT ( it, Vertex[ nod ] ){
		if ( !Viz[ it->nod ] ){
			int x = find ( it->nod ) + it->l;
			LungMax[ nod ] = get_max ( LungMax[ nod ], x );

 			Best[ it->nod ] = get_min ( Best[ it->nod ], it->c );
			if ( !Best[ it->nod ] )
				Best[ it->nod ] = it->c;
			s += Best[ it->nod ];
		}
	}
	Best[ nod ] = s;
	return LungMax[ nod ];
}

void solve ( int nod, int act ){
	Viz[ nod ] = true;
	if ( LungMax[ nod ] + act < LungMax[ 1 ] ){
		rez += 1LL*Best[ nod ]*( LungMax[ 1 ] - act - LungMax[ nod ] );
		act = LungMax[ 1 ] - LungMax[ nod ];
	}
	FORIT ( it, Vertex[ nod ] ){
		if ( !Viz[ it->nod ] ){
			solve ( it->nod, act+it->l );
		}
	}
}

int main(){

	freopen ("arb2.in","r",stdin);
	freopen ("arb2.out","w",stdout);

	scanf ("%d", &n );
	for ( i=1; i<n; ++i ){
		int a=0;
		scanf ("%d %d %d %d", &a, &Edge.nod, &Edge.l, &Edge.c );
		Vertex[ a ].pb ( Edge );
	}
	find ( 1 );
	for ( i=1; i<=n; ++i ){
		Viz[ i ] = false;
	}
	solve ( 1,0 );
	printf("%lld\n",rez);
	return 0;
}
