#include <cstdio>
#include <iostream>
using namespace std;

int n,k,i,act,j,El[25];
int Sol[ (1<<21) ];
bool nr[ (1<<21) ];
long long sol;

int gcd ( int a, int b ){
	int c;
	if ( a < b )
		swap(a,b);
	while ( b ){
		c = a%b;
		a = b;
		b = c;
	}
	if ( a )
		return a;
	return 1;	
}
int solve( int a, int b ){
	int c = gcd( a,b );
	if ( 1LL*a*b>1LL*c*n ){
		return int ( n+1 );
	}
	else
		return int ( a/c*b );
}

int main(){

	freopen("suman.in","r",stdin);
	freopen("suman.out","w",stdout);
	scanf("%d %d", &n, &k );
	for ( i=1; i<=k; ++i ){
		scanf("%d", &El[ i ] );
	}
	Sol[ 0 ] = 1;
	for ( j=0; j<k; ++j ){
		Sol[ 1 << j ] = El[ j+1 ];
	}
	for ( i=1; i<(1<<k); ++i ){
		act = 1;
		for ( j=0; !(i&(1<<j)); ++j )
			;
		Sol[ i ] = solve( El[ j+1 ], Sol[ i^(1<<j) ] );
		nr[i] = 1^nr[ i^(1<<j) ];
		int x = n/Sol[ i ];
		if ( nr[i] )
			sol = sol + 1LL*x*(x+1)/2*Sol[i];
		else
			sol = sol - 1LL*x*(x+1)/2*Sol[i];
	}
	printf("%lld\n",sol);
	return 0;
}
