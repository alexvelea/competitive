#include <cstdio>
#include <vector>
using namespace std;

#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define pb push_back
int const max_n = 30005;

vector<int> Vertex[max_n], Reverse[max_n], Order;
bool Viz[max_n];
int Nr[max_n], Pion[max_n], Result[max_n];

int n,m,t,k,a,b;
int i;

void df( int nod ){
	if( Viz[nod] )
		return ;
	Viz[nod]=1;
	Order.pb( nod );
	FORIT( it, Reverse[nod] ){
		Nr[*it]--;
		if( !Nr[*it] )
			df(*it);
	}
	return ;
}
int main(){
	freopen("pioni.in","r",stdin);
	freopen("pioni.out","w",stdout);
 	scanf("%d %d %d", &t, &n, &m );
	for( i=1; i<=m; ++i ){
		scanf("%d %d", &a, &b );
		Vertex[a].pb(b);
		Reverse[b].pb(a);
		Nr[a]++;
	}
	for( i=1; i<=n; ++i )
		if( !Nr[i] )
			df( i );
    FORIT( it, Order ){
		FORIT( itC, Vertex[*it] ){
			if( !Result[*itC] )
				Result[*it] = *itC;
		}
	}
	while( t-- ){
		scanf("%d", &k );
		int nr=0;
		for( i=1; i<=k; ++i ){
			scanf("%d", &Pion[i]);
			if( Result[ Pion[i] ] )
				nr++;
		}
		if( nr ){
			printf("Nargy\n%d ", nr);
			for( i=1; i<=k; ++i ){
				if( Result[ Pion[i] ] )
					printf("%d %d ", Pion[i], Result[ Pion[i] ] );
			}
			printf("\n");
		}else{
			printf("Fumeanu\n");
		}
	}
	return 0;
}
