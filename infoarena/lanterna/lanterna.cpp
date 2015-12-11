#include <cstdio>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
const int max_n=55, max_m=2500, max_c=1005, INF=0x3f3f3f3f;

struct edge{
	int a, b, t, c;
	edge(){
		a = b = t = c = 0;
	}
	edge( int _a, int _b, int _t, int _c ){
		a = _a;
		b = _b;
		t = _t;
		c = _c;
	}
	int other( int nod ){
		return a + b - nod;
	}
} Edge[max_m];

int n, k, m, i, j, a, b, c, t;
bool Tip[max_n];
int Best[max_n][max_n][max_c];

vector<int> Vertex[max_n];

void get_min( int &a, int b ){
	if( a>b )
		a = b;
}

void make_graph( int nod ){
	int i, t;
	int tt, b, c;
	for( i=1; i<=n; ++i )
		for( t=0; t<max_c; ++t )
			Best[nod][i][t] = INF;
	for( t=0; t<max_c; ++t )
		Best[nod][nod][t] = 0;
	for( t=0; t<max_c; ++t ){
		for( i=1; i<=n; ++i )
 			if( t == 0 || Best[nod][i][t] < Best[nod][i][t-1] )
				FORIT( it, Vertex[i] ){
					b = Edge[*it].other(i);
					c = Edge[*it].c;
					tt = Edge[*it].t;
 					if( c + t < max_c )
						get_min( Best[nod][b][t+c], Best[nod][i][t] + tt );
				}
		if( t>0 )
			for( i=1; i<=n; ++i )
				get_min( Best[nod][i][t], Best[nod][i][t-1] );
	}
}

int get_time( int k ){
	int Rez[max_n];
    bool Viz[max_n];
	int mn, ind;
	int i;
 	for( i=1; i<=n; ++i ){
		Rez[i] = INF;
		Viz[i] = false;
	}
	Rez[1] = 0;
	for( ; ; ){
		mn = INF;
		ind = -1;
 		for( i=1; i<=n; ++i )
			if( !Viz[i] && mn > Rez[i] ){
				ind = i;
				mn = Rez[i];
			}
		if( ind == -1 )
			break;
		Viz[ind] = true;
		for( i=1; i<=n; ++i )
			if( !Viz[i] && Tip[i] )
				get_min( Rez[i], Rez[ind] + Best[ind][i][k] );
	}
	return Rez[n];
}

int main(){
	freopen("lanterna.in","r",stdin);
	freopen("lanterna.out","w",stdout);
	scanf("%d %d", &n, &k );
	for( i=1; i<=n; ++i )
		scanf("%d", &Tip[i] );
	Tip[1] = Tip[n] = 1;
 	scanf("%d", &m );
	for( i=1; i<=m; ++i ){
		scanf("%d %d %d %d", &a, &b, &t, &c );
		Edge[i] = edge( a, b, t, c );
		Vertex[a].push_back( i );
		Vertex[b].push_back( i );
	}
	for( i=1; i<=n; ++i )
		if( Tip[i] )
			make_graph( i );	
	int mn = get_time( k );
	int p = 1024, rez = 0;
	for( ; p; p>>=1 )
		if( p+rez <= k ){
			if( get_time( p+rez ) == mn )
				;
			else{
				rez += p;
			}
		}
	if( get_time( 0 ) == mn )
		rez = -1;
	printf("%d %d\n", mn, rez+1 );
	return 0;
}

