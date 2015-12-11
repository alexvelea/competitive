#include <cstdio>

#include <algorithm>
#include <vector>

using namespace std;

#define pb push_back
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

const int max_n=100005;

vector<int> Vertex[max_n], Reverse[max_n], ElCtc[max_n], Order;
int nrCtc;

int n,m,a,b,i,nod;
bool Viz[max_n];


void df( int nod ){
	Viz[nod]=true;
	FORIT( it, Vertex[nod] ){
		if( !Viz[*it] )
			df(*it);
	}
	Order.pb(nod);
}

void df2( int nod ){
 	ElCtc[nrCtc].pb(nod);
	Viz[nod]=true;
	FORIT( it, Reverse[nod] )
		if( !Viz[*it] )
			df2(*it);
}
int main(){
	freopen("ctc.in","r",stdin);
	freopen("ctc.out","w",stdout);
	scanf("%d %d", &n, &m );
	for( i=1; i<=m; ++i ){
		scanf("%d %d", &a, &b );
		Vertex[a].pb(b);
		Reverse[b].pb(a);
	}
	for( i=1; i<=n; ++i )
		if( !Viz[i] )
			df(i);
	for( i=1; i<=n; ++i )
		Viz[i]=false;
	for( i=n-1; i>=0; --i ){
		nod=Order[i];
		if( !Viz[nod] ){
			nrCtc++;
			df2(nod);
		}
	}
	printf("%d\n",nrCtc);
	for( i=1; i<=nrCtc; printf("\n"), ++i ){
		sort( ElCtc[i].begin(), ElCtc[i].end() );
		FORIT( it, ElCtc[i] )
			printf("%d ", *it );
	}
	return 0;
}
