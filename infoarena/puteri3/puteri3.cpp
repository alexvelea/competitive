#include <cstdio>

#include <iostream>

using namespace std;

const int max_k = 105, Mod = 1000000007;

int Sum[max_k], k, N;
int Fact[max_k], InvFact[max_k];

int pow( int a, int p ){
	int rez = 1;
	while( p ){
		if( p&1 )
			rez = ( 1LL * rez * a ) % Mod;
		a = ( 1LL * a * a ) % Mod;
		p >>= 1;
	}
	return rez;
}

int Comb( int n, int k ){
	if( n < k )
		return Comb( k, n );
	return ( 1LL * 
	( ( 1LL * Fact[n] * InvFact[k] ) % Mod ) 
	* InvFact[n-k] ) % Mod;
}

void Init(){
 	Fact[0] = InvFact[0] = 1;
	for( int i=1; i<max_k; ++i )
		Fact[i] = ( 1LL * i * Fact[i-1] ) % Mod;
	for( int i=1; i<max_k; ++i )
		InvFact[i] = pow( Fact[i], Mod-2 );
	// termina de calculat factorialele
	return ;
}

int CalcSum( int k ){
	k++;
	int rez = pow( N+1, k );
	rez--;
	for( int i=2; i<=k; ++i ){
		rez -= ( 1LL * Comb( k, i ) * Sum[k-i] ) % Mod;
		while ( rez<0 )
			rez += Mod;
	}
	while( rez<0 )
		rez += Mod;
	rez = ( 1LL * rez * pow( k, Mod-2 ) ) % Mod;
	return rez;
}

int main(){
	freopen("puteri3.in","r",stdin);
	freopen("puteri3.out","w",stdout);
	Init();
	scanf("%d %d", &N, &k );
	Sum[0] = N % Mod;
	Sum[1] = ( 1LL * N * ( N+1 ) / 2 ) % Mod;
	for( int i=2; i<=k; ++i )
		Sum[i] = CalcSum( i );
	printf("%d\n", Sum[k] );
	return 0;
}
