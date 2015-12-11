#include <cassert>
#include <cstdio>
#include <algorithm>
using namespace std;

#define Sigma 100000000
#define max_nr 1005
#define nr_cif 250

int i,j,n,x;

struct NrMare{
	int Cif[nr_cif],NrCif;
	bool empty;
	NrMare(){
		empty=0;
		NrCif=1;
		for( int i=0; i<nr_cif; ++i )
			Cif[i]=0;
	}
	NrMare( int _nr ){
		empty=_nr;
		NrCif=1;
		for( int i=0; i<nr_cif; ++i )
			Cif[i]=0;
		Cif[0]=_nr;
	}
	void add( NrMare right ){
		empty=1;
 		int i,t=0;
		for( i=0; i<max( NrCif, right.NrCif ); ++i ){
 			Cif[i]+=right.Cif[i]+t;
			t=0;
			while( Cif[i] >= Sigma ){
				Cif[i]-=Sigma;
				t++;
			}
		}
		NrCif=max( NrCif, right.NrCif );
		if( t ){
			Cif[ NrCif ]=t;
			NrCif++;
		}
		assert(NrCif<nr_cif-10);
	}
	void afisare(){
		int j,C[8];
		for( int i=NrCif-1; i>=0; --i ){
			if( i==NrCif-1 ){
				printf("%d",Cif[i]);
			}else{
 				for( j=0; j<8; ++j )
					C[j]=0;
				j=0;
				do{
					C[j]=Cif[i]%10;
					Cif[i]/=10;
					++j;
				}while( Cif[i] );
				for( j=7; j>=0; --j )
					printf("%d",C[j]);
			}
		}
		printf("\n");
	}
} Dp[max_nr],NrMareUnu(1);

int gcd( int a, int b ){
	if( !a ) return b;
	if( !b ) return a;
	return gcd( b, a%b );
}

int main(){
	freopen("indep.in","r",stdin);
	freopen("indep.out","w",stdout);
	scanf("%d", &n );
	for( i=1; i<=n; ++i ){
		scanf("%d", &x );
		for( j=1; j<max_nr; ++j ){
			if( Dp[j].empty )
	 			Dp[gcd(x,j)].add(Dp[j]);
		}
		Dp[x].add(NrMareUnu);
	}
	NrMare Rez(0);
	Dp[1].afisare();
	return 0;
}
