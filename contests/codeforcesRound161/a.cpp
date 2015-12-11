#include <cstdio>

using namespace std;

int i,j,x;
int abs ( int a ){
	if ( a < 0 )
		return -a;
	return a;
}

int main(){
	for ( i=1; i<=5; ++i ){
		for ( j=1; j<=5; ++j ){
			scanf ("%d", &x );
			if ( x ){
				printf("%d\n", abs(3-i)+abs(3-j) );
			}
		}
	}
	return 0;
}
