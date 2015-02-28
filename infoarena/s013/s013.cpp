#include <cstdio>
#include <algorithm>
#include <fstream>
#include <vector>
//#include <iostream>
using namespace std;

ifstream cin("s013.in");
ofstream cout("s013.out");
 
#define max_n 55
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

bool T[max_n][max_n];
int L[max_n][max_n], C[max_n][max_n];

vector<int> Vertex[2*max_n*max_n];
bool Viz[2*max_n*max_n];
int Other[2*max_n*max_n];

int i, j, n, m;
int nod, cuplaj;
char c;

bool find_cuplaj( int nod ){
	if( Viz[nod] || !nod )
		return 0;        
	Viz[nod] = true;
	FORIT( it, Vertex[nod] ){
		if( !Other[*it] || find_cuplaj(Other[*it]) ){
			Other[nod]=*it;
			Other[*it]=nod;
			return 1;
		}
	}
	return 0;
}

int main(){
	int lin,finish;
	cin>>n>>m;
	for( i=1; i<=n; ++i )
		for( j=1; j<=m; ++j ){
			cin>>c;
			if( c=='*' )
				T[i][j]=1;
		}
	nod=1;
	// facem pt linii 
	for( i=1; i<=n; ++i )
		for( j=1; j<=m; ++j )
			if( T[i][j]==1 ){
 				while( T[i][j] )
					L[i][j++]=nod;
				++nod;
			}
	lin=nod-1;
	// facem pt coloane
	for( j=1; j<=m; ++j )
		for( i=1; i<=n; ++i )
			if( T[i][j] ){
				while( T[i][j] )
					C[i++][j]=nod;
				++nod;
			}	
	for( i=1; i<=n; ++i )
		for( j=1; j<=m; ++j )
			if( T[i][j] ){
				Vertex[L[i][j]].push_back(C[i][j]);
				Vertex[C[i][j]].push_back(L[i][j]);
			}
	for( i=1; i<=nod; ++i ){
		sort( Vertex[i].begin(), Vertex[i].end() );
		Vertex[i].resize( unique(Vertex[i].begin(), Vertex[i].end()) - Vertex[i].begin() );
	}
	finish=nod-1;
	bool ok=1;
	while( ok ){
		ok=0;
		for( i=1; i<=lin; ++i )
			if( !Other[i] && find_cuplaj( i ) ){
				ok=1;
				cuplaj++;
			}
		for( i=1; i<=lin; ++i )
			Viz[i]=0;
	}
	cout<<cuplaj<<"\n";
	return 0;
}
