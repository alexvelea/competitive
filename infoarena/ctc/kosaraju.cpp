#include <cassert>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

const int max_n=100005;

vector<int> Vertex[max_n], Vertex2[max_n], Ctc[max_n], Deq;
int nrCtc;

int n, m, a, b, i;
bool Viz[max_n];

void df( int nod ){
	if( Viz[nod] )
		return ;
	Viz[nod]=true;
	FORIT( it, Vertex[nod] )
		df( *it );
	Deq.push_back( nod );
}

void df2( int nod ){
 	if( Viz[nod] )
		return ;
	Viz[nod]=true;
	FORIT( it, Vertex2[nod] )
		df2( *it );
	Ctc[nrCtc].push_back(nod);
}

int main(){
	assert( freopen("ctc.in","r",stdin) );
	assert( freopen("ctc.out","w",stdout) );
	scanf("%d %d", &n, &m );
	for( ; m; --m ){
		scanf("%d %d", &a, &b );
		Vertex[a].push_back(b);
		Vertex2[b].push_back(a);
	}
	for( i=1; i<=n; ++i )
		df( i );
	for( i=1; i<=n; ++i )
		Viz[i]=false;
	for( i=n-1; i>=0; --i )
		if( !Viz[Deq[i]] ){
			nrCtc++;
			df2(Deq[i]);
		}
	printf("%d\n",nrCtc);
	for( i=1; i<=nrCtc; ++i ){
		sort( Ctc[i].begin(), Ctc[i].end() );
		FORIT( it, Ctc[i] )
			printf("%d ", *it );
		printf("\n");
	}
	return 0;
}
