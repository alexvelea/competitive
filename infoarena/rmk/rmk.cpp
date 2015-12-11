#include <cstdio>
#include <algorithm>
using namespace std;

#define max_n 100005 

int RMK[20][max_n];
int n,m,a,b,i,l,d;

int main(){
	freopen("rmq.in","r",stdin);
	freopen("rmq.out","w",stdout);
	scanf("%d %d", &n, &m );
	for ( i=1; i<=n; ++i ){
		scanf("%d", &a );
		RMK[0][i]=a;
	}
	for( l=1; (1<<l) <= n; ++l ){
		for ( i=1; i+(1<<l)-1 <= n; ++i ){
			RMK[l][i]=min( RMK[l-1][i], RMK[l-1][i+(1<<(l-1))] );
		}
	}
	for( ; m; --m ){
		scanf("%d %d", &a, &b );
		d = b-a+1;
		i=0;
		while( (1<<i) <= d )
			++i;
		--i;
		printf("%d\n", min( RMK[i][a], RMK[i][b-(1<<i)+1] ) );
	}
	return 0;
}
