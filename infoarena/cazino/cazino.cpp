#include <cstdio>
int main(){
	freopen("cazino.in","r",stdin);
	freopen("cazino.out","w",stdout);
	int t, a, b;
	int A, B;
 	scanf("%d", &t );
	while( t-- ){
		scanf("%d %d", &a, &b );
		B = ( b-a+1 ) / 2;
		A = a/2;
		printf("%.5lf\n", 1.0*A/(B+A) );
	}
	return 0;
}
