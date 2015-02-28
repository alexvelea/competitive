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
#define max_n 100005

struct edge {
    int a,b,c;
} ;

long long AIB[ max_n ];
int n,m,i,w,a;
int h;


long long search ( int val ){
	long long rez=0;
	for ( ; val; val -= ( val & ( -val ) ) )
		rez = max( rez, AIB[ val ] );
	return rez;
}
void insert ( int ind, long long val ){
	for ( ; ind<=n; ind+= ( ind & (-ind) ) )
		AIB[ ind ] = max( AIB[ ind ], val );
	return ;
}

int main(){
	scanf ("%d", &n );
	for ( i=1; i<=n; ++i ){
		scanf ("%d", &a );
		insert( i, a );
	}
	scanf ("%d", &m );
	for ( i=1; i<=m; ++i ){
		scanf ("%d %I64d", &w, &h );
 		long long nr = search( w );
		printf("%I64d\n", nr);
		insert ( 1, nr+h );
	}
	return 0;
}
