#include <cassert>
#include <cstdio>
#include <ctime>
#include <cstdlib>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define max_n 1005
#define max_m 10005
#define FORIT( it, v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define pb push_back

struct edge{
	int a,b,c,f;
	edge(){
		a=b=c=f=0;
	}
	edge( int x, int y, int z ){
		a=x;
		b=y;
		c=z;
		f=0;
	}
	int length( int p ){
		if ( b == p ){
			return c-f;
		}
		return c+f;
	}
	void increase( int p, int val ){
		if ( p == b ){
			f+=val;
		}
		else{
			f-=val;
		}
	}
	int other( int nod ){
		return a+b-nod;
	}
	void debug( ){
		cerr<<a<<"\t"<<b<<"\t"<<c<<"\t"<<f<<"\n";
		cerr<<length(b)<<"\t"<<length(a)<<"\n\n";
	}
} Edge[ max_m ];

vector<int> Vertex[ max_n ], Rez;
int Father[ max_n ], Bfs[ max_n ];
int n,m,i,a,b,c,maxflow;
bool Viz[ 3 ][ max_n ];

bool bfs (){
	int nod,st,dr,next,last,val;
	edge mu, mu1;
	st=1;
	dr=1;
	Bfs[1]=1;
	while ( st <= dr ){
		nod = Bfs[ st++ ];
		if ( nod == n )
			continue;
		FORIT( it, Vertex[ nod ] ){
			mu = Edge[ *it ];
			next = mu.other( nod );
			if ( !Father[ next ] && mu.length( next ) > 0 ){
				Father[ next ] = *it;
				Bfs[ ++dr ] = next;
			}
		}
	}
	bool ok=0;
	FORIT( it, Vertex[ n ] ){
		mu = Edge[ *it ];
		last = mu.other( n );
 		if( Father[ last ] ){
			// AM GASIT DRUM - URA
 			val = mu.length( n );
			if ( val > 0 ){
				// mergem inapoi sa vedem minimul
				nod = last;
				while ( nod != 1 ){
	            	mu = Edge[ Father[ nod ] ];
					last = mu.other( nod );
					val = min( val, mu.length( nod ) );
					nod = last;
				}
				nod = Edge[ *it ].other( n );
				// actualizam muchia mu1
				if ( val > 0 ){
					ok=1;
					Edge[ *it ].increase( n, val );
					while ( nod != 1 ){
						last = Edge[ Father[ nod ] ].other( nod );
						Edge[ Father[ nod ] ].increase( nod, val );
						nod = last;
					}
					maxflow+=val;
				}
			}
		}
	}
	return ok;
}

void solve ( int nod, int color ){
	int st,dr,l;
	edge mu;
	st = dr = 1;
	Bfs[ 1 ] = nod;
	Viz[ color ][ nod ] = 1;
	while ( st <= dr ){
		nod = Bfs[ st++ ];
		FORIT( it, Vertex[ nod ] ){
			mu = Edge[ *it ];
			if ( color == 1 )
				l = mu.length( mu.other( nod ) );
			else
				l = mu.length( nod );
			if( !Viz[ color ][ mu.other( nod ) ] && l != 0 ){
				Bfs[ ++dr ] = mu.other( nod );
				Viz[ color ][ mu.other( nod ) ] = 1;
			}
		}
	}
	return ;
}
int main(){
    srand( time(NULL) );

	freopen("critice.in","r",stdin);
	freopen("critice.out","w",stdout);

	scanf ("%d%d", &n, &m );
	for ( i=1; i<=m; ++i ){
		scanf("%d%d%d", &a, &b, &c );
	   	Edge[ i ] = edge( a,b,c ); 
		Vertex[ a ].pb( i );
		Vertex[ b ].pb( i );
	}
	Father[ 1 ] = 1;
	while ( bfs () ){
 		for ( i=2; i<=n; ++i ){
			Father[ i ] = 0;
		}
	}

/*	for ( i=1; i<=m; ++i ){
		Edge[ i ].debug();
	}*/

//	cerr<<maxflow<<"\n";
	solve ( 1, 1 );
	solve ( n, 2 );

	edge mu; 
	for ( i=1; i<=n; ++i ){
		FORIT ( it, Vertex[ i ] ){
			mu = Edge[ *it ];
			if ( Viz[ 1 ][ i ] == 1 && Viz[ 2 ][ mu.other( i ) ] == 1 )
				Rez.pb( *it );
		}
	}
	sort( Rez.begin(), Rez.end() );
	Rez.resize( unique( Rez.begin(), Rez.end() ) - Rez.begin() );

	printf("%d\n",Rez.size());
    FORIT( it, Rez ){
		printf("%d\n",*it);
	}
	return 0;
}
