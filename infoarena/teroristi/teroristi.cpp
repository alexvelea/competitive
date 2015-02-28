#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#define startDr 750
#define Sink 780
#define max_n 800
#define Sigma 30
#define INF 0x3f3f3f3f
#define FORIT( it,v ) for(typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

ifstream in("teroristi.in");
ofstream out("teroristi.out");

int Ap[Sigma]; 
bool Viz[max_n][Sigma]; 
int C[max_n][max_n], F[max_n][max_n], Father[max_n];
int Qu[max_n];
int El[1000005];

vector<int> Vertex[max_n];
vector<int> Where[max_n];
vector<int> RezInd[Sigma];
int ItRez[Sigma];

void get_min( int &a, int b ){
	if( a>b )
		a=b;
}

bool bfs(){
	int st,dr,nod,ind;
	Father[1]=1;
	dr=1;
	Qu[1]=1;    
	st=1;
	while( st<=dr ){
		if( Father[Sink] )
			break;
		ind = rand()%dr;
		ind++;
		nod=Qu[ind];
		Qu[ind]=Qu[dr--];
		FORIT( it, Vertex[nod] ){
			if( !Father[*it] && ( C[nod][*it]-F[nod][*it] > 0 ) ){
   			Father[*it]=nod;
				Qu[++dr]=*it;
			}
		}
	}
	if( Father[Sink] )
		;
	else
		return 0;
	int mn=INF;
	for( nod=Sink; nod!=1; nod=Father[nod] ) get_min( mn, C[Father[nod]][nod]-F[Father[nod]][nod] );
	for( nod=Sink; nod!=1; nod=Father[nod] ){
		F[Father[nod]][nod]+=mn;
		F[nod][Father[nod]]-=mn;
	}
	return 1;
}

int main(){     
	srand(time(NULL));
	int n,m,i,nod;
	char c,d;
	in>>n>>m;
	for( i=1; i<=n; ++i ){
		in>>c;
		El[i]=c-'a';
		Ap[c-'a']++;
	}
	for( i=0; i<26; ++i ){
		if( Ap[i] ){
			C[startDr+i][Sink]=Ap[i];
		}
	}
	for( i=1; i<=m; ++i ){
		in>>c>>d;		
		nod=(c-'a'+1)*27+(d-'a'+1);
		assert(nod<max_n);
		Where[nod].push_back(i);
        C[1][nod]++;
		C[nod][startDr+c-'a']++;
		C[nod][startDr+d-'a']++;
	}
	int j;
	for( i=1; i<=Sink; ++i )
		for( j=i+1; j<=Sink; ++j ){
			if( C[i][j] || C[j][i] ){
				Vertex[i].push_back(j);
				Vertex[j].push_back(i);
			}
		}
 	while( bfs() ){
		for( i=0; i<max_n; ++i )
			Father[i]=0;
	}
	int l,ind;
	for( i=1; i<=26; ++i ){
		for( j=1; j<=26; ++j ){
			nod=i*27+j;
			ind=0;
			for( l=0; l<F[nod][startDr+i-1] && ind<int(Where[nod].size()); ++l,++ind ){
				RezInd[ i-1 ].push_back( Where[nod][ind] );
			}
			for( l=0; l<F[nod][startDr+j-1] && ind<int(Where[nod].size()); ++l,++ind ){				
				RezInd[ j-1 ].push_back( Where[nod][ind] );
			}
		}
	}
	for ( int i=1; i<=n; ++i ) {
		assert( ItRez[El[i]] < int(RezInd[El[i]].size()) );
		out<<RezInd[ El[i] ][ ItRez[El[i]]++ ]<<" ";	
	}
	return 0;
}
