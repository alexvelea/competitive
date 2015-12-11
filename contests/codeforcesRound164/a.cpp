#include <cstdio>
using namespace std;
int main(){

    int n,rez=0,i,j,A[105],H[105];

	scanf ("%d", &n );
	for ( i=1; i<=n; ++i ){
		scanf ("%d %d", &H[i], &A[i] );
	}
	for ( i=1; i<=n; ++i ){
		for ( j=1; j<=n; ++j ){
			if ( H[i]==A[j] )
				rez++;
		}
	}
	printf("%d\n",rez);
	return 0;
}
