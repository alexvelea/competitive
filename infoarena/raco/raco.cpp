#include <cstdio>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


	ifstream in("raco.in");
	ofstream out("raco.out");

	#define MaxChar 1000000
	#define verf ( (++CharB==MaxChar) ? ( in.read(Buffer,MaxChar),CharB=0 ) : (1) )

	long CharB=MaxChar-1;
	char Buffer [ MaxChar ];

	void cit ( int &a )
	{
	    bool ok=0;
	    for ( ; !( (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9') || ( Buffer[ CharB ] == '-' ) ); verf )
		;
	    if ( Buffer[ CharB ] == '-' ){
		CharB++;
		ok=1;
	    }
	    for ( a=0; (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9'); a*=10,a+=( Buffer[ CharB ]-'0'), verf )
		;
	    if ( ok ){
		a=-a;
	    }
	}

	#define MOD 1000003
	#define mod(a,b) ((a>=b)?(a-b):(a))
	#define max_m 305

int pow ( int a, int p ){
	int rez=1;
	while ( p ){
		if ( p&1 ){
			rez = (1LL*rez*a)%MOD;
		}
		p>>=1;
		a=(1LL*a*a)%MOD;
	}
	return rez;
}

int Last[ max_m ], New[ max_m ], Nr[ max_m ], Add[ max_m ];
int s,i,n,m,a,rest;

int Fact[ MOD ], InvFact[ MOD ];
int Invers ( int k ){
	if ( !InvFact[ k ] )
		InvFact[ k ] = pow ( Fact[ k ], MOD-2 );
	return InvFact[ k ];
}

int main(){

	verf;
	
	cit(n);
	cit(m);
	for ( i=1; i<=n; ++i ){
		cit(a);
		Nr[ a%m ] ++;
	}

	Fact[ 0 ] = 1;
	Fact[ 1 ] = 1;
	Last[ 0 ] = 1;
	for ( i=2; i<=n; ++i ){
		Fact[ i ] = ( 1LL*i*Fact[ i-1 ] ) % MOD;
	}

	for ( rest = 0; rest < m; ++rest ){
    	for ( i=0; i<m; ++i ){
			Add[ i ] = 0;
		}
		for ( i=0; i<=Nr[ rest ]; ++i ){
			Add[ (i*rest) % m ] = ( 1LL*Add[ (i*rest) % m ] + 1LL*Fact[ Nr[ rest ] ] * Invers ( i ) * Invers ( Nr[ rest ] - i ) ) % MOD;
		}
        for ( s=0; s<m; ++s ){
			for ( i=0; i<m; ++i ){
				New[ mod(i+s,m) ] = mod ( New[ mod(i+s,m) ] + ( ( 1LL*Last[ i ]*Add[ s ] ) %MOD ) , MOD ); 
			}
		}
		for ( s=0; s<m; ++s ){
			Last[ s ] = New[ s ];
			New[ s ] = 0;
		}
	}	
	Last[ 0 ]--;
	if ( Last[ 0 ]<0 )
		Last[ 0 ] += MOD;
	out<<Last[ 0 ]<<"\n";
	return 0;
}
