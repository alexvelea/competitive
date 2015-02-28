#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream in("ratphu.in");
ofstream out("ratphu.out");

#define FORIT( it, v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

const int max_n=(1<<18);

long long Best[20][max_n];
int El[20], M[305], Log[max_n];

int Mod, i, e, r, past, c;
long long n;

int main(){
	in>>n>>Mod;
	do{
		El[i++]=n%10;
		n/=10;
	}while(n);
	n=i;

	for( i=1; i<=250; ++i )
		M[i]=i%Mod;
	
	for( i=0; i<n; ++i ){
		Best[ El[i]%Mod ][ 1<<i ] = 1;
	}
	for( i=0; i<n; ++i )
		Log[1<<i]=i;
	for( i=1; i<(1<<n); ++i ){
		if( i & (i-1) )
			;
		else
			continue;
		c = i;
		while( c ){
			e = Log[c&(-c)];
			c-=c&(-c);
			past = i^(1<<e);
			// am selectat elementul e :)
			// mergem inapoi de la starea "past"
			for( r=0; r<Mod; ++r )
				Best[ M[ r*10 + El[e] ] ][i] += Best[r][past];
		}
	}
	out<< Best[0][(1<<n)-1];
	return 0;
}
