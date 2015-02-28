#include <cstdio>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define FORIT( it,v ) for(typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define pb push_back

const int half=605, start=305, max_s=1500, INF=1000, rangeSt=-300, rangeDr=+300;
const int empty=-1, Source=0, Sink=max_s-1;

queue<int> Q;
vector<int> Vertex[max_s];

int C[max_s][max_s], F[max_s][max_s], Cost[max_s][max_s], From[max_s], Best[max_s];
bool InQ[max_s];

int i,j,cost;
int a,b,n,k,El[max_s];
vector<int> Rez[max_s];

int abs( int a ){
	if( a>0 )
		return a;
	return -a;
}

void bfs(){
	int nod;
	InQ[Source]=1;
	Q.push(Source);
	From[Source]=Source;
	Best[Source]=0;
	while( !Q.empty() ){
		nod=Q.front();
		InQ[nod]=false;
		Q.pop();
		FORIT( it, Vertex[nod] ){
			if( C[nod][*it] > F[nod][*it] ){
				if( Best[*it] > Best[nod]+Cost[nod][*it] ){
					Best[*it]=Best[nod]+Cost[nod][*it];
					From[*it]=nod;
					if( !InQ[*it] ){
						Q.push(*it);
						InQ[*it]=true;
					}
				}
			}
		}
	}
	for( nod=Sink; nod!=Source; nod=From[nod] ){
		F[From[nod]][nod]++;
		F[nod][From[nod]]--;
	}
 	cost+=Best[Sink];
}

int main(){
	freopen("smen.in","r",stdin);
	freopen("smen.out","w",stdout);
	scanf("%d %d %d %d", &n, &k, &a, &b );
	a+=start;
	b+=start;
	for( i=1; i<=n; ++i ){
		scanf("%d", &El[i] );
		assert( El[i] >= rangeSt );
		assert( El[i] <= rangeDr );
		El[i]+=start;
		C[Source][El[i]]++;
	}
	for( i= rangeSt+start; i<= rangeDr+start; ++i ){
		if( C[Source][i] ){
			Vertex[Source].pb(i);
			Vertex[i].pb(Source);
			for( j=a; j<=b; ++j ){
				C[i][half+j]=INF;
				Cost[i][half+j]=+abs(i-j);
				Cost[half+j][i]=-abs(i-j);
				Vertex[i].pb(half+j);
				Vertex[half+j].pb(i);
			}
		}
	}
	for( i=a; i<=b; ++i ){
		C[i+half][Sink]=1;
		Vertex[i+half].pb(Sink);
	}
	for( ; k; --k, bfs() ){
		for( i=0; i<max_s; ++i ){
			Best[i]=INF;
			From[i]=empty;
		}
	}
	printf("%d\n",cost);
	for( i= rangeSt+start; i<=rangeDr+start; ++i ){
		for( j=a+half; j<=b+half; ++j ){
			while( F[i][j]>0 ){
				Rez[i].pb(j-half);
				F[i][j]--;
			}
		}
	}
	for( i=1; i<=n; ++i ){
		if( Rez[El[i]].size() ){
			printf("%d ", Rez[El[i]].back()-start);
			Rez[El[i]].pop_back();
		}else
			printf("%d ", El[i]-start);
	}
	return 0;
}
