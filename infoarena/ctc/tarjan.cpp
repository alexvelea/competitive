#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define pb push_back

const int max_n=200005;

vector<int> Vertex[max_n], Ctc[max_n];
stack<int> Q;
int NrCtc;
bool InQ[max_n];
int Deep[max_n],Low[max_n],deep;
int n,a,b,i;

void get_min( int &a, int b ){
	if( a>b )
		a=b;
}

void tarjan( int nod ){
	Deep[nod]=Low[nod]=++deep;
	Q.push(nod);
	InQ[nod]=true;
	FORIT( it, Vertex[nod] )
		if( !Deep[*it] ){
			tarjan( *it );
			get_min( Low[nod], Low[*it] );
		}else if( InQ[ *it ] )
			get_min( Low[nod], Low[*it] );
	if( Deep[nod] == Low[nod] ){
		NrCtc++;
		bool ok=1;
		while( ok ){		
			Ctc[NrCtc].pb( Q.top() );
 			InQ[ Q.top() ]=false;
			if( Q.top() == nod )
				ok=0;
 			Q.pop();
		}
	}
	return ;
}

int main(){  
	freopen("ctc.in","r",stdin);
 	freopen("ctc.out","w",stdout);
	int m;
	scanf("%d %d", &n, &m );
 	for( ; m; --m ){
		scanf("%d %d", &a, &b );
		Vertex[a].pb(b);
	}
	for( i=1; i<=n; ++i )
		if( !Deep[i] )
			tarjan(i);
	printf("%d\n", NrCtc );
	for( i=1; i<=NrCtc; ++i ){
		sort( Ctc[i].begin(), Ctc[i].end() );
		FORIT( it, Ctc[i] )
			printf("%d ", *it );
		printf("\n");
	}
		
	return 0;
}
