#include <cstdio>

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define pb push_back
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

const int INF=0x3f3f3f3f, max_n=66, Sink=65, Source=0, empty=-1;

int n,m;
int a,b,c;
int i,j,k;

int Nr[max_n];
vector<int> Vertex[max_n];
int Cost[max_n][max_n];
int C[max_n][max_n], F[max_n][max_n], Best[max_n], Father[max_n]; // flux
bool Inside[max_n];
queue<int> Qu;

int maxFlow, flowCost;

void get_min( int &a, int b ){
	if( a>b )
		a=b;
}

bool bfs(){
	int nod;
	Inside[Source]=true;
	Qu.push(Source);
	Best[Source]=0;
	Father[Source]=Source;
	while( !Qu.empty() ){
		nod=Qu.front();
		Inside[nod]=false;
		Qu.pop();
		FORIT( it, Vertex[nod] ){
			if( Best[*it] > Best[nod]+Cost[nod][*it] && ( C[nod][*it] > F[nod][*it]  ) ){
				Best[*it] = Best[nod]+Cost[nod][*it];
				Father[*it] = nod;
				if( !Inside[*it] ){
					Inside[*it]=true;
					Qu.push(*it);
				}
			}
		}
	}
	if( Father[Sink] == empty )
		return 0;
	int mn=INF;
	for( nod=Sink; nod!=Source; nod=Father[nod] ) get_min( mn, C[Father[nod]][nod] - F[Father[nod]][nod] );
	for( nod=Sink; nod!=Source; nod=Father[nod] ){
		F[Father[nod]][nod]+=mn;
		F[nod][Father[nod]]-=mn;
	}
	flowCost+=mn*Best[Sink];
	maxFlow+=mn;
	return 1;
}

int main(){

	freopen("traseu.in","r",stdin);
	freopen("traseu.out","w",stdout);

	scanf("%d %d", &n, &m);
	for( i=1; i<=n; Cost[i][i]=0,++i )
		for( j=1; j<=n; ++j )
			Cost[i][j]=INF;

	for( i=1; i<=m; ++i ){
		scanf("%d %d %d", &a, &b, &c );
 		Cost[a][b]=c;
		flowCost+=c;
		Nr[a]--;
		Nr[b]++;
	}
    for( k=1; k<=n; ++k )
		for( i=1; i<=n; ++i )
			for( j=1; j<=n; ++j )
				get_min( Cost[i][j], Cost[i][k]+Cost[k][j] );
   for( i=1; i<=n; ++i ){
		if( Nr[i]>0 ){
			// ajung mai multe
			Vertex[Source].push_back(i);
			Vertex[i].push_back(Source);
			C[Source][i]=Nr[i];
		}
		if( Nr[i]<0 ){
			// pleaca mai multe .. 
 			Vertex[i].push_back(Sink);
			Vertex[Sink].push_back(i);
			C[i][Sink]=-Nr[i];
		}
	}

	for( i=1; i<=n; ++i )
		if( Nr[i]>0 )
			for( j=1; j<=n; ++j )
				if( Nr[j]<0 ){
					Cost[j][i]=-Cost[i][j];
					Vertex[i].push_back(j);
					Vertex[j].push_back(i);
					C[i][j]=INF;
				}
/*	for( i=1; i<=n; ++i,cerr<<"\n" )
		for( j=1; j<=n; ++j )
			cerr<<Cost[i][j]<<"\t";*/
 
/*	for( i=1; i<=n; ++i )
		cerr<<Nr[i]<<"\t";
	cerr<<"\n\n";*/
	for( i=0; i<=Sink; ++i ){
		Father[i]=empty;
		Best[i]=INF;
		Inside[i]=false;
	}
	while( bfs() ){
		for( i=0; i<=Sink; ++i ){
			Father[i]=empty;
			Best[i]=INF;
			Inside[i]=false;
		}
	}
 //   cerr<<maxFlow<<"\n";
    printf("%d\n",flowCost);
	return 0;
}
