#include <cmath>
#include <cstdio>

using namespace std;

int n=2,t[15],val[15],rez, viz[15];

void bt ( int k ){
	if ( k == 2*n+1 ){
		int i;
		for ( i=1; i<=2*n; ++i ){
			t[i]=0;
		}
		for ( i=1; i<=n; ++i ){
			t[i]=t[i-1]+val[i];
		}
		for ( i=n+1; i<=2*n; ++i ){
			t[i]=t[i-n]+val[i];
		}
		bool ok=1;
		for ( i=n+2; i<=2*n; ++i ){
			if ( abs ( t[i]-t[i-1] ) > 1 )
				ok=0;
		}
		rez+=ok;
		return ;
	}
	if ( viz[ k ] ){
		bt ( k+1 );
		return ;
	}
	for ( int i=-1; i<=1; ++i ){
		val[ k ] = i;
		bt ( k+1 );
	}
	return ;
}

int main(){

	viz[ 1 ] = 1;
    bt ( 1 );
	printf("%d\n",rez);

	return 0;
}

