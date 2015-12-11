#include <cstdio>

#include <algorithm>
#include <queue>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

#define pb push_back
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define mp make_pair
#define fi first
#define se second
#define INF 0x3f3f3f3f

#define max_n 3*100005

int Stare[ max_n ];
vector< max_n > V;

struct edge {
    int a,b,c;
} ;

int main(){
	scanf ("%d", &n );
	for ( i=1; i<=n; ++i ){
		scanf ("%d %d", &a, &b );
		V[a].pb(b);
		V[b].pb(a);
	}
	for ( i=1; i<=n; ++i ){
		R[0]=R[1]=R[2]=0;
		FORIT( it, V[i] ){
			R[ Stare[*it] ]++;
		}
		if ( R[1]>R[2] ){
			Stare[i]=2;
		}
		else{
			Stare[i]=1;
		}
	}
	for ( i=1; i<=n; ++i ){

	}
	return 1;
}
