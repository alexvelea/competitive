#include <cstdio>
using namespace std;

	int a[20],b[20];

void doit ( int *a ){
	for ( int i=1; i<=5; ++i ){
		*(a+i) = i;
	}
	return ;
}

int main(){
	doit( &a[0] );
	doit( &b[0] );
	for ( int i=0; i<=10; ++i ){
		printf("%d -) %d\n", i, a[i] );
	}
	return 0;
}
