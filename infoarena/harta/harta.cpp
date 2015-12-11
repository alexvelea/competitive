#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define mp make_pair
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define Sink 205
#define max_n 210

int i,j,n;
int C[max_n][max_n], F[max_n][max_n], Father[max_n];
vector<int> Vertex[max_n];
vector< pair<int,int> > Rez;

void muchie( int a, int b ){
	Vertex[a].push_back(b);
	Vertex[b].push_back(a);
}
void get_min( int &a, int b ){
	if( a>b )
		a=b;
}

int Qu[max_n], maxFlow;
bool bfs(){
	int dr=0,ind,nod;
	Qu[0]=1;
	Father[1]=1;
	while( dr>=0 ){
		if( Father[Sink] )
			break;
		ind=rand()%(dr+1);
		nod=Qu[ind];
		Qu[ind]=Qu[dr--];
		FORIT( it, Vertex[nod] ){
			if(!Father[*it] && ( C[nod][*it]-F[nod][*it] > 0 )){
				Qu[++dr]=*it;
				Father[*it]=nod;
			}
		}
	}
	int mn=0x3f3f3f3f;
	if( !Father[Sink] )
		return 0;
	for( nod=Sink; nod!=1; nod=Father[nod] ) get_min( mn, C[Father[nod]][nod] - F[Father[nod]][nod] );
	for( nod=Sink; nod!=1; nod=Father[nod] ){
		F[Father[nod]][nod] += mn;
		F[nod][Father[nod]] -= mn;
	}
	maxFlow+=mn;
	return 1;
}

int main(){
	freopen("harta.in","r",stdin);
	freopen("harta.out","w",stdout);
	srand(time(NULL));
	scanf("%d", &n );
	n++;
	int a,b;
	for( i=2; i<=n; ++i ){
		scanf("%d %d", &a, &b);
		C[1][i]=a;
		C[n+i][Sink]=b;
		muchie(1,i);
		muchie(n+i,Sink);
	}
	for( i=2; i<=n; ++i ){
		for( j=2; j<=n; ++j ){
			if( j!=i ){
				C[i][n+j]=1;
				muchie(i,n+j);
			}
		}
	}
	while( bfs() ){
		for( i=0; i<=Sink; ++i )
			Father[i]=0;
	}
    for( i=2; i<=n; ++i ){
		for( j=n+2; j<=2*n; ++j ){
			if( F[i][j] ){
				Rez.push_back(mp(i,j-n));
			}
		}
	}
	sort( Rez.begin(), Rez.end() );
	printf("%d\n",int(Rez.size()) );
	FORIT( it, Rez )
		printf("%d %d\n", it->fi-1, it->se-1 );
	return 0;
}
