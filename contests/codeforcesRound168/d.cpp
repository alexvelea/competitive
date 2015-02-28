#include <cstdio>

#include <algorithm>
#include <queue>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

#define pb push_back
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define mp make_pair
#define fi first
#define se second
#define INF 0x3f3f3f3f
#define max_n 100005

struct edge {
    int a,b,c;
} ;
bool Viz[ 4*max_n ];
vector<int> Edge[ 4*max_n ], Rez;
vector< pair<int,int>  > Nr;
int i,j,n,m,l,o=1;
int A[ 4*max_n ],a;


void df ( int nod ){
	if ( Viz[ nod ] )
		return ;
	Viz[ nod ] = 1;
	if ( nod <= m )
		Rez.push_back( nod );
	FORIT( it, Edge[ nod ] ){
		A[ *it ]--;
		if ( A[ *it ] == 0 )
			df ( *it );
	}
	return ;
}
int main(){
	scanf("%d %d", &n, &m );

	for ( i=1; i<=n; ++i ){
		Nr.clear();
		for ( j=1; j<=m; ++j ){
	 		scanf("%d", &a );
			Nr.push_back(make_pair(a,j));
		}
		sort( Nr.begin(), Nr.end() );
		j=0;
		while( j<m && Nr[ j ].fi == -1 )
			j++;
		while( j<m ){
 			l = j;
			while ( j<m && Nr[ l ].fi == Nr[ j ].fi ){
				if ( l > 0 ){
					Edge[ m+o ].push_back( Nr[ j ].se );
					A[ Nr[ j ].se ] ++;
				}
				j++;
			}
			o++;
			while ( j<m && l<m && l < j ){
				Edge[ Nr[ l ].se ].push_back( m+o );
				A[ m+o ]++;
				++l;
			}
		}
	}
    for ( i=1; i<=m+o; ++i ){
		if( A[ i ] == 0 ){
			df ( i );
		}
	}
	if ( Rez.size() == m ){
		FORIT( it, Rez )
			printf("%d ",*it);
	} else
		printf("-1");
}
