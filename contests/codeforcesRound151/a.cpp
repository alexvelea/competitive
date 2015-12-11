#include <cstdio>
using namespace std;
int main(){
	int n;
	scanf ("%d", &n );
	if ( n <= 2 ){
		printf("-1");
	}
	else{
		int i;
		printf("%d %d ",n-1,n);
		for ( int i=1; i<=n-2; i++ )
			printf("%d ",i);
	}
}
