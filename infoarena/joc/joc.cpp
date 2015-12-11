#include <cstdio>
using namespace std;

#define max_n 1005
#define INF 0x3f3f3f3f

int Best[max_n][max_n], El[max_n];
int n, m, i, j;
int mx, l, c;

int max( int a, int b ){
	if( a > b )
		return a;
	return b;
}

int main(){
	freopen("joc.in","r",stdin);
	freopen("joc.out","w",stdout);
	mx=-INF;
 	scanf("%d %d", &n, &m );
    for( i=0; i<=n; ++i )
		for( j=0; j<=m; ++j )
			Best[i][j]=-INF;
	for( i=1; i<=n; ++i ){
		for( j=1; j<=m; ++j ){
			scanf("%d", &El[j]);
		}
		for( j=1; j<=m; ++j ){
			if( j!=1 )
				Best[i][j]=max( Best[i][j], Best[i][j-1] );
			if( i!=1 )
				Best[i][j]=max( Best[i][j], Best[i-1][j] );
			if( i!=1 && j!=1 )
				Best[i][j]=max( Best[i][j], Best[i-1][j-1] );
			if( Best[i][j] == -INF )
				Best[i][j] = El[j];
			else
				Best[i][j]=max( Best[i][j], El[j]-Best[i][j] );

			if( Best[i][j] > mx ){
				mx=Best[i][j];
				l=i;
				c=j;
			}
		}
	}
	printf("%d %d %d\n",mx,l,c);
	return 0;
}
