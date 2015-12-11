#include <cstdio>
using namespace std;
int main(){

    scanf ("%d %d %d", &n, &m, &k );
	for ( i=1; i<=n; ++i ){
		for ( j=1; j<=m; ++j ){
			scanf ("%d", &El[ n+i ][ j+m ] );
		}
	}          

	// facem sumele partiale.
	for ( i=1; i<=2*n; ++i ){
		for ( j=1; j<=2*m; ++j ){
			StUp[ i ][ j ] = El[ i ][ j ] + StUp[ i-1 ][ j-1 ];
		}
	}
	for ( i=n; i<=3*n; ++i ){
		for ( j=1; j<=2*m; ++j ){
			DrUp[ i ][ j ] = El[ i ][ j ] + DrUp[ i-1 ][ j+1 ];
		}
	}
	for ( i=

	return 0;
}
