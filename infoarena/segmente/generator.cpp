#include <cstdio>
using namespace std;
int main(){
	int i,n;
	freopen("segmente.in","w",stdout);
	printf("1000\n");
	n=500;
	for( i=1; i<=500; ++i ){
		printf("%d %d %d %d\n", i, 500, i, 600);
	}
	for( i=1; i<=500; ++i ){
		printf("%d %d %d %d\n", 500, i, 600, i);
	}
	return 0;
}
