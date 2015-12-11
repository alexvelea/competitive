#include <cstdio>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;

#define pb push_back
#define max_n 200005
#define max_m 400005
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define INF 0x3f3f3f3f

struct muchie {
	int a,b,c;
	muchie(){
		a=b=c=0;
	}
	muchie( int x, int y, int z ){
		a=x;
		b=y;
		c=z;
	}
	int other( int nod ){
		return a+b-nod;
	}
	bool operator < ( const muchie b ) const {
		return b.c > c;
	}
} Edge[ max_m ];

int n,m,i;
vector<int> Vertex[ max_n ], Rez;
int rez;
int Father[ max_n ];

int get_data_set( int nod ){
	if ( Father[ nod ] != nod ){
		Father[ nod ] = get_data_set( Father[ nod ] );
	}
	return Father[ nod ];
}
void data_set_union( int a, int b ){
	int c = rand()%2;
	if ( c )
		Father[ a ] = b;
	else
		Father[ b ] = a;
}

int main(){
	srand( time( NULL ) );
	freopen("apm.in","r",stdin);
	freopen("apm.out","w",stdout);
	scanf("%d %d", &n, &m );
	for ( i=1; i<=m; ++i ){
		scanf("%d %d %d", &Edge[ i ].a, &Edge[ i ].b, &Edge[ i ].c );
		Vertex[ Edge[ i ].a ].pb( i );
		Vertex[ Edge[ i ].b ].pb( i );
	}
	sort( Edge+1, Edge+m+1 );
	for ( i=1; i<=n; ++i ){
		Father[ i ] = i;
	}
	for ( i=1; i<=m; ++i ){
		if ( get_data_set( Edge[ i ].a ) != get_data_set( Edge[ i ].b ) ){
			rez += Edge[ i ].c;
            data_set_union( get_data_set( Edge[ i ].a ), get_data_set( Edge[ i ].b ) );
			Rez.pb( i );
		}
	}
	printf("%d\n%d\n",rez,n-1);
	FORIT( it, Rez )
		printf("%d %d\n", Edge[ *it ].a, Edge[ *it ].b );
	return 0;
}
