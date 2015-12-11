#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

#define FORIT( it,v ) for(typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define max_n 355
#define INF 0x3f3f3f3f

vector<int> Vertex[max_n];
queue<int> Q;
int Best[max_n], Father[max_n];
int Cost[max_n][max_n], F[max_n][max_n], C[max_n][max_n];
bool Inside[max_n];
int n, S, D;

void get_min( int &a, int b ){
	if( a>b )
		a=b;
}

bool bfs(){
	int i,nod;
	for( i=1; i<=n; ++i )
		Best[i]=INF;
	Father[S]=0;
	Best[S]=0;
	Q.push(S);
	while( Q.size() ){
		nod=Q.front();
		Q.pop();
		Inside[nod]=0;
		FORIT( it, Vertex[nod] ){
			if( ( Best[*it] > Best[nod] + Cost[nod][*it] ) && ( C[nod][*it]-F[nod][*it] > 0 ) ){
				Best[*it] = Best[nod] + Cost[nod][*it];
				Father[*it]=nod;
				if( !Inside[*it] ){
					Q.push(*it);
					Inside[*it]=1;
				}
			}
		}
	}
	if( Father[D] )
		return 1;
	return 0;
}

int main(){
	freopen("fmcm.in","r",stdin);
	freopen("fmcm.out","w",stdout);
	int  i,m,a,b,c,cost;
	scanf("%d %d %d %d", &n, &m, &S, &D );
	for( i=1; i<=m; ++i ){
		scanf("%d %d %d %d", &a, &b, &c, &cost);
		C[a][b]=c;
		Cost[a][b]=cost;
		Cost[b][a]=-cost;
		Vertex[a].push_back(b);
		Vertex[b].push_back(a);
	}
	int nod,mn;
	int maxFlow=0, costFlow=0;
	while( bfs() ){
		nod=D;
		mn=INF;
		for( nod=D; nod!=S; nod=Father[nod] ) get_min( mn, C[Father[nod]][nod]-F[Father[nod]][nod] );
		for( nod=D; nod!=S; nod=Father[nod] ){
			F[Father[nod]][nod] += mn;
			F[nod][Father[nod]] -= mn;
		}
		costFlow += mn*Best[D];
		maxFlow += mn;
		for( i=1; i<=n; ++i )
			Father[i]=0;
	}
	printf("%d\n",costFlow);
	return 0;
}
