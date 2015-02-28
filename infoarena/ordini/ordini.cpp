#include <cassert>
#include <cstdio>

#include <iostream>
#include <vector>

using namespace std;

#define pb push_back

const int max_n=1005, max_div=20;
int Mod, Phi, n, LastDiv, Ap[10], rez=0;
int c, d;
int i, j;
int act, nrMod[max_div], RezMid[10], NrDivAp[max_div];

int Fact[max_n], InvFact[max_n], ModAp[max_n][max_div];
vector<int> PrimeDesc;

int max( int a, int b){
	if( a>b )
		return a;
	return b;
}

int pow( int a, int p ){
	int rez=1;
	while( p ){
		if( p&1 )
			rez = (1LL * rez * a) % Mod;
		p>>=1;
		a = (1LL * a * a) % Mod;
	}
	return rez;
}

int main(){
	freopen("ordini.in","r",stdin);
	freopen("ordini.out","w",stdout);
 	for( i=0; i<10; ++i ){
		scanf("%d", &Ap[i] );
		n += Ap[i];
	}

	scanf("%d", &Mod );
	c=Mod;
	Phi=Mod;
 	for( d=2; c!=1 && d*d<=c; ++d ){
		if( !(c%d) ){

			Phi/=d;
			Phi*=(d-1);
			while( !(c%d) ){
				c/=d;
				NrDivAp[ PrimeDesc.size() ]++;
			}
 			PrimeDesc.pb( d );
		}
	}
	if( c!=1 ){
		NrDivAp[ PrimeDesc.size() ]++;
		PrimeDesc.pb( c );
		Phi/=c;
		Phi*=(c-1);
	}
	Fact[1]=1;
	for( i=2; i<=n; ++i ){
		c=i;
	    for( d=0; d<int( PrimeDesc.size() ); ++d ){
			ModAp[i][d]=ModAp[i-1][d];
	 		while( !(c%PrimeDesc[d]) ){
				c/=PrimeDesc[d];
				ModAp[i][d]++;
			}
		}
		Fact[i]=(1LL*c*Fact[i-1])%Mod;
	}
	for( i=1; i<=n; ++i )
		InvFact[i]=pow( Fact[i], Phi-1 );
 	InvFact[0]=Fact[0]=1;

 	for( i=1; i<10; ++i ){
		for( j=1; j<10; ++j ){
			// un element din mijloc i si la inceput e j
			Ap[i]--;
			Ap[j]--;
			if( Ap[i] >= 0 && Ap[j] >= 0 ){
				for( d=0; d<int( PrimeDesc.size() ); ++d )
					nrMod[d] = ModAp[n-2][d];
				act = Fact[n-2];
				for( c=0; c<10; ++c ){
					for( d=0; d<int( PrimeDesc.size() ); ++d )
						nrMod[d] -= ModAp[ Ap[c] ][d];
					act = ( 1LL * act * InvFact[ Ap[c] ] ) % Mod;
				}
				bool ok = true;
				for( d=0; d<int( PrimeDesc.size() ); ++d ){
					assert( nrMod[d] >= 0 );
//					if( nrMod[d]<NrDivAp[d] )
//						ok = false;
					act = ( 1LL * act * pow( PrimeDesc[d], nrMod[d] ) ) % Mod;
				}
//				if( ok )
//					act = 0;
				RezMid[i]+=act;
				RezMid[i] %= Mod;
			}
			Ap[i]++;
			Ap[j]++;
		}
	}
	act=0;
	c=1;
	for( i=1; i<n; ++i ){
		act = (act+c) % Mod;
		c = (1LL*c*10) % Mod;
	}
    for( i=1; i<10; ++i ){
		rez = ( 1LL*i*RezMid[i]*act + rez ) % Mod;
	}
	// daca e la inceput :)
	c=pow(10,n-1);
	for( i=1; i<10; ++i ){
		if( !Ap[i] )
			continue;
		Ap[i]--;
		for( d=0; d<int( PrimeDesc.size() ); ++d )
			nrMod[d] = ModAp[n-1][d];
		act = Fact[n-1];
		for( j=0; j<10; ++j ){
			for( d=0; d<int( PrimeDesc.size() ); ++d )
				nrMod[d] -= ModAp[ Ap[j] ][d];
			act = (1LL * act * InvFact[ Ap[j] ]) % Mod;
		}
		bool ok=true;
		for( d=0; d<int( PrimeDesc.size() ); ++d ){
			assert( nrMod[d]>= 0 );
//			if( nrMod[d]<NrDivAp[d] )
//				ok = false;
			act = ( 1LL * act * pow( PrimeDesc[d], nrMod[d] ) ) % Mod;
		}
//		if( ok )
//			act=0;
		rez = ( 1LL*rez + 1LL*act*c*i ) % Mod;
		Ap[i]++;
	}
	printf("%d", rez );
	return 0;
}
