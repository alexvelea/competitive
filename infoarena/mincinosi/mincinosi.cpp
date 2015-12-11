#include <cstdio>
using namespace std;
	
	#define max_n 1000005
	int V[max_n],T[max_n],i,j,n;

int main(){
	freopen ("mincinosi.in","r",stdin);
	freopen ("mincinosi.out","w",stdout);
	scanf ("%d", &n );
	for ( i=1; i<=n; i++ ){
		scanf ("%d", &T[i] );
		V[T[i]]++;
	}
	for ( i=0; i<=n; i++ ){
		if ( V[i] == n-i ){
			// YEEE
			printf("%d\n",n-i);
			for ( j=1; j<=n; j++ ){
				if ( T[j] == i )
					printf("%d\n",j);

			}
			return 0;
		}
	}
	printf("0\n");
	return 0;
}
