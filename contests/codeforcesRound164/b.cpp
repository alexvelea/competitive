#include <cstdio>
using namespace std;

	int n,rez,i;

int main(){
	scanf ("%d", &n );
	for ( i=1; i<=n; ++i ){
		rez+=i*(n-i);
		rez++;
	}
	printf("%d", rez );
}
