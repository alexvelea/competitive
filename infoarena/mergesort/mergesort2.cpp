#include <cstdio>

#include <iostream>
#include <fstream>

using namespace std;

	#define MOD 1000003
	#define max_n 1000005

int Fact[ max_n ],inv_Fact[ max_n ], Sol[ max_n ];
int n;

int invers ( int val, int p ){
	if ( p == 0 )
		return 1;
	if ( p == 1 )
		return val;
	if ( p&1 ){
		return (1LL*val*invers( (1LL*val*val)%MOD, p/2 ) )%MOD;
	}
	else
		return invers ( (1LL*val*val)%MOD, p/2 );
}

int inv_fact ( int val ){
	if ( inv_Fact[ val ] != -1 ){
		return inv_Fact[ val ];
	}
	inv_Fact[ val ] = invers ( Fact[ val ], MOD-2 );
	return inv_Fact[ val ];
}

int C( int n, int k ){
	int rez=Fact[ n ];
	rez=(1LL*rez*inv_fact(k) ) % MOD;
	rez=(1LL*rez*inv_fact(n-k) ) % MOD;
	return rez;
}


int solve ( int n ){
	if ( n == 0 ){
		return 0;
	}
	if ( n == 1 ){
		return 1;
	}
	if ( Sol[ n ] != -1 )
		return Sol[ n ];
	int a=(n/2);
	int b=n-a;
	Sol[ n ] = ( 1LL*C(n,a)*( (1LL*solve(a)*Fact[ b ])%MOD + (1LL*solve(b)*Fact[ a ])%MOD + (1LL*Fact[ a ]*Fact[ b ])%MOD ) ) % MOD - 2;
	if ( Sol[ n ] < 0 )
		Sol[ n ] += MOD;
	return Sol[ n ];
}
int main(){

    ifstream in("mergesort.in");
	ofstream out("mergesort.out");

	in>>n;
	int i;
	for ( i=1; i<=n; ++i ){
		inv_Fact[ i ] = Sol[ i ] = -1 ;
	}
	Fact[ 1 ] = 1;
	Fact[ 0 ] = 1;
	for ( i=2; i<=n; ++i ){
		Fact[ i ] = ( 1LL * Fact[ i-1 ] * i ) % MOD;
	}
 
/* 	for ( i=1; i<=n; ++i ){
		printf("%d ", solve(i));
	}*/

    out<<solve( n )<<"\n";
}
