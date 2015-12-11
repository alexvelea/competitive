#include <cstdio>
#include <cassert>


#include <vector>
using namespace std;

	#define FORIT( it, v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
	#define max_n 100005

int St[ max_n ],Dr[ max_n ];
bool Viz[ max_n ];
vector<int> Edge[ max_n ];

int n,a,b,i;

bool find_path ( int nod ){
	if ( Viz[ nod ] )
		return 0;
	Viz[ nod ] = 1;
	FORIT ( it, Edge[ nod ] ){
		if ( !Dr[ *it ] || find_path( Dr[ *it ] ) ){
			St[ nod ] = *it;
			Dr[ *it ] = nod;
			return 1;
		}
	}
	return 0;
}

int main(){

    freopen ("circulatie.in","r",stdin);
	freopen ("circulatie.out","w",stdout);

	scanf ("%d", &n );
	for ( i=1; i<=3*n; ++i ){
		scanf ("%d %d", &a, &b );
		Edge[ a ]. push_back ( b );
	}

	int nr=0;
	bool ok=1;

	do {
		ok=0;
		for ( i=1; i<=n; ++i ){
			if ( !St[ i ] ){
				if ( find_path( i ) ){
					nr++;
					ok=1;
				}
			}
		}
		for ( i=1; i<=n; ++i )
			Viz[ i ] = 0;
	}while ( ok );
	assert ( nr == n );
	for ( i=1; i<=n; ++i ){
		FORIT ( it, Edge[ i ] ){
			if ( St[ i ] != *it ){
				printf("%d %d -1\n",i,*it);
			}
			else{
				printf("%d %d 2\n",i,*it);
			}
		}
	}
	return 0;
}
