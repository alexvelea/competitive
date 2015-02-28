#include <cstdio>
using namespace std;

const int max_cif=100, sigma=100000000, max_n=105;

int k, p, n;
int i, j;

int max( int a, int b ){
	if( a>b )
		return a;
	return b;
}

struct nrmare{
	int nrcif, Cif[max_cif];
 	nrmare(){
		nrcif=1;
		for( int i=0; i<max_cif; ++i )
			Cif[i]=0;
	}
	nrmare( int el ){
		nrcif=1;
		Cif[0]=el;
		for( int i=1; i<max_cif; ++i )
			Cif[i]=0;
	}
	void sum( nrmare &other ){
		int t=0;
		for( int i=0; i<max( nrcif, other.nrcif ); ++i ){
			Cif[i]+=t+other.Cif[i];
			t=0;
			while( Cif[i] >= sigma ){
				t++;
				Cif[i] -= sigma;
			}
		}
		nrcif = max( other.nrcif, nrcif );
		if( t )
			Cif[nrcif++] = t;
	}
	void inm( int x ){
		int t=0, tp;
		for( int i=0; i<nrcif; ++i ){
			tp = ( 1LL * x * Cif[i] + t ) / sigma;
			Cif[i] = (1LL * x * Cif[i] + t) % sigma;
			t = tp;
		}	
		if( t )
			Cif[nrcif++]=t;
	}
	void afisare() {
		int C[8], x, j, ok=0;
		for( int i=nrcif-1; i>=0; --i ){
			for( j=0; j<8; ++j )
				C[j]=0;
			x=Cif[i];
			j=0;
			while( x ){
				C[j++]=x%10;
				x/=10;
			}
			for( j=7; j>=0; --j ){
				if( C[j] != 0 )
					ok=1;
				if( ok )
					printf("%d",C[j]);
			}
		}
		printf("\n");
	}
} Rez[max_n][max_n];

int main(){
	freopen("ex.in","r",stdin);
	scanf("%d %d %d", &n, &k, &p );
	Rez[k][k]=nrmare(1);
	for( i=k+1; i<=n; ++i ){
		for( j=k; j<=p; ++j )
			Rez[i][j].sum( Rez[i-1][j-1] );
		for( j=k; j<=p; ++j )
			Rez[i-1][j].inm( j );
		for( j=k; j<=p; ++j )
			Rez[i][j].sum( Rez[i-1][j] );
	}
	freopen("ex.out","w",stdout);
	Rez[n][p].afisare();
	return 0;
}
