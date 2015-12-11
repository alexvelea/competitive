#include <cstdio>
#include <vector>
using namespace std;
	
	#define FORIT( it, v ) for( typeof( (v).begin() ) it=(v).begin(); it!=(v).end(); ++it )
	#define pb push_back
	#define nrcif 1200

struct nrmare {
	short val[ nrcif ];

	nrmare(){
		for ( int i=0; i<nrcif; ++i ){
			val[i]=0;
		}
	}
	nrmare( int a ){
		val[0]=1;
		val[1]=a;
		for ( int i=2; i<nrcif; ++i ){
			val[i]=0;
		}
	}

	void afisare (){
		for ( int i=val[0]; i; --i )
			printf("%d", val[i] );
		printf("\n");
	}
	void multiply ( int a ){
		int t=0,i;
		for ( i=1; i<=val[0] || t; ++i ){
			if ( i > val[0] )
				val[0]=0;
			val[i]*=a;
			val[i]+=t;
			t=val[i]/10;
			val[i]%=10;
		}
		val[0]=i-1;
	}

} T; 

vector<int> N[10];

int n,i,j;

int main(){

	freopen ("culori3.in","r",stdin);
	freopen ("culori3.out","w",stdout);

	scanf ("%d", &n );

	if ( n == 1 ){
		printf("5\n");
		return 0;
	}
	if ( n == 2 ){
		printf("8\n");
		return 0;
	}
	if ( n == 3 ){
		printf("14\n");
		return 0;
	}
	T.val[0]=T.val[1]=1;
	for ( i=1; i<n/2; ++i ){
		T.multiply( 3 );
	}
	if ( !( n%2 ) ){
		T.multiply( 8 );
		T.afisare();
		return 0;
	}
	else{
    	T.multiply( 14 );
		T.afisare();
	}
	return 0;
}
