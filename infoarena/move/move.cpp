#include <cstdio>

#include <algorithm>
#include <fstream>

using namespace std;

#define max_n 100005
#define fi first
#define se second

ifstream in("move.in");
ofstream out("move.out");

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

pair< int,int > Aib[ max_n ], x, mx;
int El[ max_n ], P[ max_n ], n, i;
bool Viz[ max_n ];

void search( int ind ){
	for( ; ind; ind-=(ind)&(-ind) ){
		if( Aib[ ind ].fi > x.fi ){
			x=Aib[ ind ];
		}
	}
}
void update( int ind ){
	for( ; ind<=n; ind+=(ind)&(-ind) ){
		if( ( Aib[ ind ].fi < x.fi ) || ( Aib[ ind ].fi == x.fi && Aib[ ind ].se > x.se ) ){
			Aib[ ind ] = x;
		}
	}
}

int main(){
	verf;
	cit(n);
	for( i=1; i<=n; ++i ){
		cit(El[i]);
	}
	for( i=1; i<=n; ++i ){
		x.fi=x.se=0;
		search( El[ i ] );
		x.fi++;
		P[ El[ i ] ] = x.se;
		x.se = El[ i ];
		update( El[ i ] );
		if( x.fi > mx.fi )
			mx=x;
	}
	int nod = mx.se, nr=0;
	while( nod != 0 ){
		nr++;
		Viz[ nod ] = 1;
		nod = P[ nod ];
	}
	out<<n-nr<<"\n";
	for( i=1; i<=n; ++i ){
		if( !Viz[ i ] ){
			out<<i<<" "<<i-1<<"\n";
		}
	}
	return 0;
}
