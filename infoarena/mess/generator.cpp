#include <cstdio>
using namespace std;
int main(){
	int i, n, m;
	freopen("mess.in","w",stdout);
 	n = 65536;
	m = 100000;
//	m = 1;
	printf("%d %d\n", n, m);
	for( i=1; i<=n; ++i )
		printf("%d ", i );
	printf("\n");
	for( i=1; i<=m; ++i ){
 		printf("%d %d %d %d\n", 2, 1, n-1, n-1 );
	}
	return 0;
}
