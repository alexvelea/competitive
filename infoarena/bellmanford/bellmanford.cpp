#include <cstdio>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define INF 0x3f3f3f3f
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define max_n 50005
#define FORIT( it,v ) for(typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

int n,m;
int i,a,b,c;

queue<int> Deq;
vector< pair<int,int> > Vertex[max_n];
int Best[max_n], Nr[max_n];
bool Inside[max_n];

int main(){
	freopen("bellmanford.in","r",stdin);
	freopen("bellmanford.out","w",stdout);
	scanf("%d %d", &n, &m );
	for( i=1; i<=m; ++i ){
		scanf("%d %d %d", &a, &b, &c );
		Vertex[a].pb(mp(b,c));
	}
	for( i=1; i<=n; ++i )
		Best[i]=INF;
	Best[1]=0;
	Deq.push( 1 );
	int nod,cost;
	while( !Deq.empty() ){
		nod=Deq.front();
		cost=Best[nod];
		Inside[nod]=false;
		Deq.pop();

		FORIT( it, Vertex[nod] ){	
			if( cost+it->se < Best[it->fi] ){
				Best[it->fi]=cost+it->se;
 				if( !Inside[ it->fi ] ){
					Nr[it->fi]++;
					if( Nr[it->fi]>n ){
						printf("Ciclu negativ!\n");
						return 0;
					}    
					Inside[ it->fi ]=true;
					Deq.push( it->fi );
				}
			}
		}
	}
	for( i=2; i<=n; ++i ){
		printf("%d ",Best[i]);
	}
	return 0;
}                 
