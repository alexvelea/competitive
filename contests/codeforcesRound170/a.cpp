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

vector<int>Vertex[ 205 ];
bool Viz[ 205 ];
int i,j,k,n,m,rez,x;

struct edge {
    int a,b,c;
} ;

void df( int nod ){
	if( Viz[ nod ] )
		return ;
	Viz[ nod ] = 1;
	for( int j=0; j<Vertex[nod].size(); ++j )
		df(Vertex[nod][j]);
}

int main(){
	bool ok=0;
	scanf("%d %d", &n, &m );
	for( i=1; i<=n; ++i ){
		scanf("%d", &k );
		for( j=1; j<=k; ++j ){
			scanf("%d", &x );
			x+=n;
			Vertex[ i ].pb(x);
			Vertex[ x ].pb(i);
			ok=1;
		}
	}
	for( i=1; i<=n; ++i ){
		if(!Viz[i]){
			df(i);
			rez++;
		}
	}
	rez--;
	printf("%d\n",rez+1-ok);
	return 0;
}

