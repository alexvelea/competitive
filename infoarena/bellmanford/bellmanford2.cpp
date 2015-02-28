#include <cstdio>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define max_n 50005
#define INF 0x3f3f3f3f
#define FORIT( it,v ) for(typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define pb push_back
#define mp make_pair
#define fi first
#define se second


int Best[max_n], Ap[max_n], n;

struct heap{
	int El[max_n],Where[max_n];
	bool Inside[max_n];
	heap(){
		for( int i=0; i<max_n; ++i ){
			El[i]=i;
			Where[i]=i;
			Inside[i]=0;
		}
	}
	bool empty(){
		return !(Inside[El[1]]);
	}

	void push_heap( int nod ){
		if( nod == 1 )
			return ;
		if( Best[El[nod]] < Best[El[nod/2]] || Inside[ El[nod/2] ] == 0 ){
			swap( Where[El[nod]], Where[El[nod/2]] );
			swap( El[nod], El[nod/2] );
			push_heap( nod/2 );
		}
	}
	void pop_heap( int nod ){
		if( 2*nod+1 > max_n )
			return ; // ar iesi din heap .. nu pot avea atatea elemente -> nu fac KBS
		if( ( Best[El[2*nod]] < Best[El[2*nod+1]] && El[2*nod]<=n && Inside[El[2*nod]] ) || ( Inside[El[2*nod]] && !Inside[El[2*nod+1]] ) ){
			swap( Where[El[nod]], Where[El[2*nod]] );
			swap(El[nod], El[2*nod]);
			pop_heap(2*nod);
		}else{
			if( El[2*nod+1] <=n && Inside[El[2*nod+1]] ){
				swap( Where[El[nod]], Where[El[2*nod+1]]);
				swap( El[nod], El[2*nod+1]);
				pop_heap(2*nod+1);
			}
		}
		return ;
	}
	void insert( int nod ){
		Inside[nod]=1;
		push_heap(Where[nod]);
	}
	int top(){
		return El[1];
	}
	void pop(){
		Inside[El[1]]=0;
		pop_heap(1);
	}
} PQ;

vector< pair<int,int> > Vertex[max_n];

int main(){
	freopen("bellmanford.in","r",stdin);
	freopen("bellmanford.out","w",stdout);
	int a,b,c,m,i;
	scanf("%d %d", &n, &m );
	for( ; m; --m ){
		scanf("%d %d %d", &a, &b, &c );
		Vertex[a].pb(mp(b,c));
	}
   	for( i=1; i<=n; ++i )
		Best[i]=INF;
	Best[1]=0;
	PQ.insert(1);
	int nod;
	while( !PQ.empty() ){
		nod=PQ.top();
		PQ.pop();
		FORIT( it, Vertex[nod] ){
			if( Best[it->fi] > Best[nod]+it->se ){
				Best[it->fi]=Best[nod]+it->se;
 				PQ.insert(it->fi);
				Ap[it->fi]++;
				if( Ap[it->fi] > n ){
					printf("Ciclu negativ!\n");
					return 0;
				}
			}
		}
	}
	for( i=2; i<=n; ++i )
		printf("%d ",Best[i]);
	printf("\n");
	return 0;
}
