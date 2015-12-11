#include<cassert>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;

#define FORIT( it,v ) for(vector<int> :: iterator it=(v).begin(); it!=(v).end(); ++it )

const int max_n=100005;

bool InQ[max_n];
vector<int> Vertex[max_n];
vector<int> Ctc[max_n]; int nrCtc=0;
int Deep[max_n], Low[max_n], deep;
stack<int> Stack;

int n, m, a, b, i;

void get_min( int &a, int b ){
	if( a>b )
		a=b;
}

void tarjan( int nod ){
	if( Deep[nod] )
		return ;
	Stack.push( nod );
	InQ[nod]=true;
	Deep[nod]=++deep;
	Low[nod]=deep;
	FORIT( it, Vertex[nod] ){
		if( !Deep[*it] ){
			tarjan( *it  );
			get_min( Low[nod], Low[*it] );
		}else
			if( InQ[*it] )                        
				get_min( Low[nod], Low[*it] );
	}
	if( Deep[nod] == Low[nod] ){
		bool ok=true;
		nrCtc++;
		while( ok ){
	    	Ctc[nrCtc].push_back( Stack.top() );
			InQ[ Stack.top() ] = false;
			if( nod == Stack.top() )
				ok=false;
			Stack.pop();
		}
	}
	return ;
}

int main(){
	assert( freopen("ctc.in","r",stdin) );
	assert( freopen("ctc.out","w",stdout) );
	scanf("%d %d", &n, &m );
	for( ; m; --m){
		scanf("%d %d", &a, &b );
		Vertex[a].push_back(b);
	}
	for( i=1; i<=n; ++i )
		if( !Deep[i] ){
			tarjan( i );
			assert( Stack.empty() );
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
