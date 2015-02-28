#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define pb push_back
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define fi first
#define se second
#define mp make_pair
#define max_n 50005

int n,m,i,a,b,c;
int nod,cost;
vector< pair<int,int> > Vertex[ max_n ];
pair<int,int> Heap[ 4*max_n ];
int Where[ max_n ], Best[ max_n ], heapsize;
 
void push_heap( int ind ){
	int p = ind/2;
	if( p )
		;
	else
		return;
	if( Heap[ind].fi < Heap[p].fi || (!Heap[p].fi) ){
		swap( Where[ Heap[ind].se ] , Where[ Heap[p].se ] );
		swap( Heap[ind], Heap[p] );
		push_heap(p);
	}
	return ;
} 

void insert_heap( pair<int,int> val ){
	Heap[ ++heapsize ] = val;
	Where[ val.second ] = heapsize;
	push_heap( heapsize );
	return ;
}

void pop_heap( int ind ){
	int st,dr;
	Heap[ ind ].fi = Heap[ ind ].se = 0;

	st=ind*2;
	dr=ind*2+1;

	if( dr <= heapsize) 
		;
	else
		return ; 
	if( Heap[st].fi && Heap[dr].fi ){
		if( Heap[st].fi < Heap[dr].fi ){
			Heap[ind]=Heap[st];
			Where[ Heap[ind].se ] = ind;
			pop_heap( st );
			return ;
		}else{
			Heap[ind]=Heap[dr];
			Where[ Heap[ind].se ] = ind;
			pop_heap( dr );
			return ;
		}
	}
	if( Heap[st].fi ){
		Heap[ind] = Heap[st];
		Where[ Heap[ind].se ] = ind;
		pop_heap( st );
	}
	if( Heap[dr].fi ){
		Heap[ind] = Heap[dr];
		Where[ Heap[ind].se ] = ind;
		pop_heap( dr );
	}
}

int main(){
	freopen("dijkstra.in","r",stdin);
	freopen("dijkstra.out","w",stdout);

	scanf("%d %d", &n, &m );
	for( i=1; i<=m; ++i ){
		scanf("%d %d %d", &a, &b, &c );
		Vertex[ a ].pb( mp( b,c ) );
	}
	insert_heap( make_pair(1,1) );
	Best[1]=1;
	while( Heap[1].se ){
		cost = Heap[1].fi;
		nod = Heap[1].se;
		pop_heap(1);
		FORIT( it, Vertex[ nod ] ){
			if( !Best[ it->fi ] ){
				Best[ it->fi ] = cost + it->se;
				insert_heap( mp( it->se+cost, it->fi ) );
			}
			if( Best[ it->fi ] > it->se + cost ){
    			Heap[ Where[ it->fi ] ].fi = it->se + cost;
				Best[ it->fi ] = it->se + cost;
				push_heap( Where[ it->fi ] );
			}
		}
	}
	for( i=2; i<=n; ++i ){
		if( Best[i] )
			printf("%d ",Best[i]-1);
		else
			printf("0 ");
	}
	return 0;	
}
