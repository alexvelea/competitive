#include <cstdio>
using namespace std;
int min( int a,int b ){
	if ( a < b )
		return a;
	return b;
}
int main(){
	int n,m,i;
	scanf ("%d%d", &n, &m );
	printf("%d\n",min(n,m)+1);
	for ( i=n; i>=0 && ( ( n-i ) <= m); --i ){
		printf("%d %d\n",i,n-i);
	}
	return 0;
}
