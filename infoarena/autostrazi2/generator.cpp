#include <cstdio>
#include <iostream>
using namespace std;
int main(){
	int n, i, j, sum=0;
	freopen("autostrazi2.in","w",stdout);
	n = 40;
	printf("%d %d\n", 2*n, (n*n)+(n)*(n-1)/2);
 	for( i=1; i<=n; ++i ){
		for( j=1; j<=n; ++j ){
			printf("%d %d\n", i, j+n );
			sum++;
		}
	}
	for( i=1; i<=n; ++i )
		for( j=i+1; j<=n; ++j ){
			printf("%d %d\n", i+n, j+n );
			sum++;
		}
	cerr<<2*n<<"\t"<<sum;
	return 0;
}
