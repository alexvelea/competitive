#include <cstdio>

#include <algorithm>
using namespace std;

	int A[100],n,k,i,nr,j;

int main(){
	scanf ("%d %d", &n, &k );
	for ( i=1; i<=n; ++i ){
		scanf ("%d", &A[i] );
	}
	sort ( A+1, A+n+1 );
	nr=n;
	for ( i=1; i<=n; ){
 		if ( nr == k ){
			printf("%d %d\n", A[i], A[i] );
			return 0;
		}                         	j=i;
		while ( i<=n && A[i] == A[j] ){
			nr--;
			i++;
		}

	}
	if ( nr == k ){
		printf("%d %d\n", A[i], A[i] );
		return 0;
	}                      
	printf ("-1\n");
	return 0;
}
