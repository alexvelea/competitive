#include <cstdio>
#include <vector>
using namespace std;

	#define pb push_back

int n,m,a,b,i,nr;
bool Viz[ 100005];
vector<int> V[ 100005 ];

void df ( int nod ){
	Viz[ nod ] = 1;
	for ( int i=0; i<V[nod].size(); ++i ){
		if ( !Viz[ V[nod][i] ] ){
			df ( V[nod][i] );
		}
	}
}

int main(){
	freopen ("grarb.in","r",stdin);
	freopen ("grarb.out","w",stdout);
	scanf ("%d%d", &n, &m );
	for ( i=1; i<=m; ++i ){
		scanf ("%d%d", &a, &b );
		V[a].pb ( b );
		V[b].pb ( a );
	}
	for ( i=1; i<=n; ++i ){
		if ( !Viz[ i ] ){
			df ( i );
			nr++;
		}
	}
	printf("%d\n%d\n",m+nr-n,nr-1);
	return 0;
}

