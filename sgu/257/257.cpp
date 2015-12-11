#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int nodA=10, nodB=11, nodC=12, Sink=13;
const int INF=0x3f3f3f3f;

#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define max_n 100005
#define max_f 15
char Character[3]={'P', 'O', 'S'};

int C[max_f][max_f], F[max_f][max_f], Father[max_f];
int It[max_f];
vector<int> Vertex[max_f];
vector<int> Where[max_f];
int Target[3], Final[max_n];
int i,j,nod;

void get_min( int &a, int b ){
	if( a>b )
		a=b;
}

int Qu[max_f], maxFlow;
bool bfs(){
	int st,dr,nod;
	st=dr=1;
	Father[1]=Qu[1]=1;
	while( st<=dr ){
		if( Father[Sink] )
			break;
		nod=Qu[st++];
		FORIT( it, Vertex[nod] ){
			if( !Father[*it] && ( C[nod][*it]-F[nod][*it] > 0 ) ){
				Qu[++dr]=*it;
				Father[*it]=nod;
			}
		}
	}
	if( !Father[Sink] )
		return 0;
	int mn=INF;
	for( nod=Sink; nod!=1; nod=Father[nod] ) get_min( mn, C[Father[nod]][nod]-F[Father[nod]][nod] );
	for( nod=Sink; nod!=1; nod=Father[nod] ){
		F[Father[nod]][nod] += mn;
		F[nod][Father[nod]] -= mn;
	}
	maxFlow+=mn;
	return 1;
}

int main(){
	int n;
	char a,b,c;

	scanf("%d %d %d", &Target[0], &Target[1], &Target[2] );
	scanf("%d ", &n );
	for( i=1; i<=n; ++i ){
		scanf("%c%c%c ", &a, &b, &c);
 		nod=0;
		if( a == 'B' ) nod++;
		nod<<=1;
		if( b == 'B' ) nod++;
		nod<<=1;
		if( c == 'B' ) nod++;
		nod++;
		Where[nod].push_back(i);
		if( nod == 1 )
			continue;
		if( a == 'B' ) C[nod][nodA]++;
		if( b == 'B' ) C[nod][nodB]++;
		if( c == 'B' ) C[nod][nodC]++;
		C[1][nod]++;
	}
	C[nodA][Sink]=Target[0]/2;
	C[nodB][Sink]=Target[1]/2;
	C[nodC][Sink]=Target[2]/2;
	for( i=1; i<=Sink; ++i )
		for( j=i+1; j<=Sink; ++j )
			if( C[i][j] ){
				Vertex[i].push_back(j), Vertex[j].push_back(i);
			}
	while( bfs() ){
		for( i=0; i<=Sink; ++i )
			Father[i]=0;
	}
 	for( i=2; i<=8; ++i ){
		nod=i-1;
		for( j=0; j<3; ++j ){
			if( nod&(1<<(2-j)) ){
				for( int l=1; l<=F[i][nodA+j]; ++l ){
					Final[ Where[i][ It[i]++ ] ]=j;
					Target[j]-=2;
				}
			}
		}
	}
	nod=1;
	for( i=0; i<3; ++i ){
		while( nod<9 && Target[i] ){
			if( !( It[nod] < int(Where[nod].size()) ) ){
				nod++;
			}else{
				Final[ Where[nod][ It[nod]++ ] ]=i;
				Target[i]--;
			}
		}
	}
	if( Target[0]+Target[1]+Target[2]>0 ){
		printf("no solution\n");
	}else{
		// totul e ok
		for( i=1; i<=n; ++i )
			printf("%c", Character[ Final[i] ] );
	}
	return 0;
}
