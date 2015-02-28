#include <cstdio>

#include <algorithm>

using namespace std;

	#define max_t 1005
	#define max_n 55

struct joc {
	int val,t;
} Game[ max_n ];

int BestSt[ 2 ][ max_t ], BestDr[ 2 ][ max_t ];
int n,x,t,i,maxim=0;
int Ts, Tf;

void FromSt( joc g, int ind ){
	for ( i=t; i-g.t >= 0 ; --i ){
		BestSt[ ind ][ i ] = max ( BestSt[ ind ][ i ] , BestSt[ ind ][ i-g.t ] + g.val );
	}
	return ;
}
void FromDr( joc g, int ind ){
	for ( i=1; i+g.t<=t; ++i ){
		BestDr[ ind ][ i ] = max ( BestDr[ ind ][ i ], BestDr[ ind ][ i+g.t ] + g.val );
	}
	return ;
}

int main(){
	scanf ("%d %d %d", &n, &x, &t);
	for ( i=1; i<=n; ++i ){
		scanf ("%d %d", &Game[ i ].t, &Game[ i ].val );
	}
	scanf ("%d %d", &Ts, &Tf );
	for ( i=1; i<=x; ++i ){
    	FromSt( Game[ i ] , 0 );
		FromDr( Game[ i ] , 0 );
	}
	for ( i=x; i<n; ++i ){
		FromSt( Game[ i ] , 1 );
		FromDr( Game[ i ] , 1 );
	}
	maxim = BestDr[ 0 ][ 1 ] + BestDr[ 1 ][ 1 ];
	for ( i=Ts; i+Game[ n ].t && i<=Tf; i++ ){
		int act;
		act = Game[ n ].val;
		act += BestSt[ 0 ][ i-1 ] + BestSt[ 1 ][ i-1 ];
		act += BestDr[ 0 ][ i+Game[ n ].t ] + BestDr[ 1 ][ i+Game[ n ].t ];
		if ( act > maxim )
			maxim = act;
	}
	printf("%d\n", maxim );
	return 0;
}
