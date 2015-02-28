#include <cstdio>
using namespace std;

const int max_n=505;

bool A[max_n][max_n], B[max_n][max_n], col[max_n], lin, el;
int i, j, n, rez;

int main(){
	freopen("panou.in","r",stdin);
	freopen("panou.out","w",stdout);
	scanf("%d", &n );
	for( i=1; i<=n; ++i )
		for( j=1; j<=n; ++j )
			scanf("%d", &A[i][j] );
	for( i=1; i<=n; ++i )
		for( j=1; j<=n; ++j )
			scanf("%d", &B[i][j] );
	for( i=n; i; --i ){
		lin=0;
		for( j=n; j; --j ){
			el = A[i][j]^lin^col[j];
			if( el != B[i][j] ){
				rez++;
				col[j] ^= 1;
				lin ^= 1;
			}
		}
	}
	printf("%d\n",rez);
	return 0;
}
