#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

const int max_n=1000005;

#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

bool Viz[max_n], St[max_n];
vector<int> Vertex[max_n];

int a, b, i;
int n, m, p, rez;

void df( int nod ){
	if( !nod || Viz[nod] )
		return ;
	rez--;
	Viz[nod]=true;
	FORIT( it,Vertex[nod] )
		if( !Viz[*it] )
			df( *it );
}

int main(){

	assert( freopen("berarii2.in","r",stdin) );
	assert( freopen("berarii2.out","w",stdout) );

	scanf("%d %d %d", &n, &m, &p );
	for( i=1; i<=m; ++i ){
		scanf("%d %d", &a, &b );
		Vertex[b].push_back(a);
	}
	for( i=1; i<=p; ++i ){
		scanf("%d ", &a );
		St[a]=1;
	}
	rez=n;
	for( i=1; i<=n; ++i )
		if( St[i] && !Viz[i] )
			df( i );
	printf("%d\n",rez);
	for( i=1; i<=n; ++i )
		if( !Viz[i] )
			printf("%d\n",i);
	return 0;
}
