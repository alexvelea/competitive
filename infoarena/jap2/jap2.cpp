#include <cstdio>

#include <algorithm>
#include <iostream>
using namespace std;

const int max_mod = 1000010;

int Fact[max_mod], InvFact[max_mod];

long long a, b, ap;
int Mod, q, i;

int pow( int a, long long p ){
	int rez = 1;
	while( p ){
		if( p&1 )
			rez = (1LL * rez * a) % Mod;
		a = (1LL * a * a ) % Mod;
		p>>=1;
	}
	return rez;
}

int GetFact( long long a, bool tip ){
	if ( a == 0 )
		return 1;
	if( tip == 0 )
		ap += a/Mod;
	else
		ap -= a/Mod;

	if( tip == 0 )
		return Fact[ a%Mod ];
	else
		return InvFact[ a%Mod ];
}

long long Nr( long long a ){
	if( a<Mod )
		return 0;
	long long rez = a/Mod + Nr( a/Mod );
	return rez;
}

long long DifZero( long long a, long long b ){
	long long rez = 0;
	rez = Nr(a);
	rez -= Nr(b);
	rez -= Nr(a-b);
	return rez;
}

int GetThing( long long a, bool t ){
	int rez = 1;
	while( a ){
		rez = ( 1LL * rez * GetFact(a,t) ) % Mod;
		a /= Mod;
	}
	return rez;
}

int main(){
	freopen("jap2.in","r",stdin);
	freopen("jap2.out","w",stdout);
	scanf("%d %d", &Mod, &q );
	Fact[1]=Fact[0]=1;
	for( i=2; i<Mod; ++i )
		Fact[i] = (1LL * Fact[i-1] * i) % Mod;
    InvFact[Mod-1] = pow( Fact[Mod-1], Mod-2 );
	for( i=Mod-2; i; --i )
		InvFact[i] = ( 1LL * InvFact[i+1] * ( i+1 ) ) % Mod;
	InvFact[0] = InvFact[1] = 1;
 	while( q-- ){
		scanf("%lld %lld", &a, &b );
		if( a<b )
			swap( a,b );
		if( DifZero( a,b ) != 0 )
			printf("%d\n", 0);
		else{
			int rez = 1;
			ap = 0;
			rez = GetThing( a, 0 );
			rez = ( 1LL * rez * GetThing( b, 1 ) ) % Mod;
			rez = ( 1LL * rez * GetThing( a-b, 1 ) ) % Mod;
			rez = ( 1LL * rez * pow( Fact[Mod-1], ap ) ) % Mod;
			printf("%d\n",rez);
		}
	}
	return 0;	
}
