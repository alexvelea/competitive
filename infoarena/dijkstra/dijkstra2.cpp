#include <cstdio>

#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

#define max_n 50005
#define max_c 1005

int next( int a, int b ){
	a+=b;
	while( a >= max_c )
		a-=max_c;
	return a;
}

int Best[max_n];
bool Viz[max_n];
vector<int> Cost[max_c];
vector< pair<int,int> > Vertex[max_n];
int i,j,nod,a,b,c,n,m,CostAct,Remain,Time;

int main(){
	freopen("dijkstra.in","r",stdin);
	freopen("dijkstra.out","w",stdout);
	scanf("%d %d", &n, &m );
	for( i=1; i<=m; ++i ){
		scanf("%d %d %d", &a, &b, &c );
		Vertex[a].pb(mp(b,c));
	}
 	Remain=1;
	Time=0;
	CostAct=0;
	Cost[0].pb(1);
	while( Remain>0 ){
		for( i=0; i<Cost[CostAct].size(); ++i ){
			Remain--;
			nod = Cost[CostAct][i];
			if(!Viz[nod]){
				Viz[nod]=1;
				Best[nod]=Time;
				// ne extindem din el
				for( j=0; j<Vertex[nod].size(); ++j ){
                	if(!Viz[Vertex[nod][j].fi]){
						Cost[ next(CostAct,Vertex[nod][j].se) ].pb( Vertex[nod][j].fi );
						Remain++;
					}
				}    
			}
		}
		Cost[CostAct].erase( Cost[CostAct].begin(), Cost[CostAct].end() );
		CostAct=next(CostAct,1);
		Time++;
	}
	for( i=2; i<n; ++i ){
		printf("%d ",Best[i]);
	}
	printf("%d\n",Best[n]);
	return 0;
}
