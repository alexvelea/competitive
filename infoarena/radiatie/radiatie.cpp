#include <cstdio>
#include <ctime>
#include <cstdlib>

#include <algorithm>
#include <vector>

using namespace std;

#define max_n 15005
#define max_q 15005
#define max_m 30005

#define fi first
#define se second
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define pb push_back

struct muchie {
	int a,b,c;
	muchie(){
		a=b=c=0;
	}
	int other( int nod ){
		return a+b-nod;
	}
	bool operator < ( const muchie b ) const {
		return c < b.c;
	}
} Edge[ max_m ];

vector<muchie> Vertex[ max_n ];
int n,m,q;
pair<int,int> Query[ max_q ];

void read(){

	freopen("radiatie.in","r",stdin);
	freopen("radiatie.out","w",stdout);

	int i;
	scanf("%d %d %d", &n, &m, &q );
	for ( i=1; i<=m; ++i ){
		scanf("%d %d %d", &Edge[ i ].a, &Edge[ i ].b, &Edge[ i ].c );
	}
	for( i=1; i<=q; ++i ){
		scanf("%d %d", &Query[ i ].fi, &Query[ i ].se );
	}
}

bool Viz_m[ max_m ];
int Father[ max_n ];

int get_set( int nod ){
	if( Father[ nod ] != nod ){
		Father[ nod ] = get_set( Father[ nod ] );
	}         
	return Father[ nod ];
}

bool unite( int a, int b ){
 	int ma = get_set( a ), mb = get_set( b );
	if( ma == mb )
		return 0;
	else{
		int x = rand()%2;
		if ( x )
			Father[ ma ] = mb;
		else
			Father[ mb ] = ma;
		return 1;
	}
}

void make_apm(){
	int i;
	sort( Edge+1, Edge+m+1 );
	for( i=1; i<=n; ++i ){
		Father[ i ] = i;
	}
	for( i=1; i<=m; ++i ){
		if ( unite( Edge[ i ].a, Edge[ i ].b ) ){
			Viz_m[ i ] = 1;
		}
	}
	for( i=1; i<=m; ++i ){
		if( Viz_m[ i ] ){
			Vertex[ Edge[ i ].a ].pb( Edge[ i ] );
			Vertex[ Edge[ i ].b ].pb( Edge[ i ] );
		}
	}
}

int First[ max_n ], Level[ max_n ], Parcurgere[ 2*max_n ], p;
pair< int,int > Parent[ max_n ][ 20 ];
int RMQ[ 2*max_n ][ 20 ], Log[ 2*max_n ];
bool Viz[ max_n ];

void euler( int nod, int level ){
	Viz[ nod ] = 1;
	Parcurgere[ ++p ] = level;
	First[ nod ] = p;
	Level[ nod ] = level;
	FORIT( it, Vertex[ nod ] ){
		if( !Viz[ it->other( nod ) ]){
			euler( it->other( nod ), level+1 );
			Parent[ it->other( nod ) ][ 0 ] = make_pair( nod, it->c );
			Parcurgere[ ++p ] = level;
		}
	}
}

void make_rmq(){
	int i,l;
	euler( 1,1 );	
	Log[ 0 ] = Log[ 1 ] = 0;
	for( i=2; i<=p; ++i ){
		Log[ i ] = Log[ i>>1 ] + 1;
	}
	for( i=1; i<=p; ++i ){
		RMQ[ i ][ 0 ] = Parcurgere[ i ];
	}
	for( l=1; (1<<l) <= p; ++l ){
		for( i=1; i-1+(1<<l) <=p; ++i ){
			RMQ[ i ][ l ] = min( RMQ[ i ][ l-1 ], RMQ[ i+(1<<(l-1)) ][ l-1 ] );
		}
	}
	// facem parentii
	int nod,cost;
	for( l=1; (1<<l) <= p; ++l ){
		for( i=1; i<=n; ++i ){
			nod = Parent[ i ][ l-1 ].fi;
			cost = Parent[ i ][ l-1 ].se;
			cost = max( cost, Parent[ nod ][ l-1 ].se );
			Parent[ i ][ l ] = make_pair( Parent[ nod ][ l-1 ].fi, cost );
		}
	}
}

int go_deeper( int nod, int target ){
	int result=0, act=0;
	while( target ){
		if( target & (1<<act) ){
			result = max( result, Parent[ nod ][ act ].se );
			nod = Parent[ nod ][ act ].fi;
			target ^= (1<<act);
		}
		act++;
	}
	return result;
}

void solve(){
	int i,a,b,d,l,target,result;
	for( i=1; i<=q; ++i ){
		a = Query[ i ].fi;
		b = Query[ i ].se;
		// facem rmq
		a = First[ a ];
		b = First[ b ];
		if ( a > b )
			swap( a,b );
		d = b-a+1;
		l = Log[ d ];
		target = min( RMQ[ a ][ l ], RMQ[ b-(1<<l)+1 ][ l ] );
		// stim nivelul LCA-ului

		// pentru a afla rezultatul, trebuie sa parcurgem pana la acel nivel sa vedem ce valori intalnim, si sa o luam pe cea maxima.
		a = Query[ i ].fi;
		b = Query[ i ].se;
		result = go_deeper( a, Level[ a ]-target );
		result = max( result, go_deeper( b, Level[ b ]-target ) );
		printf("%d\n",result);
	}
}

int main(){
	read();
	make_apm();
	make_rmq();
	solve();
	return 0;
}
