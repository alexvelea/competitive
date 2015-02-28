#include <cstdio>

#include <iostream>

using namespace std;

long long sum;
int n, i, j, x;
int nr_empty, st, dr;

int main(){
	freopen("numere5.in","r",stdin);
	freopen("numere5.out","w",stdout);
	scanf("%d", &n);
	for( i=1; i<=n; ++i )
		for( j=1; j<=n; ++j ){
			scanf("%d", &x );
			if( x>0 )
				sum += x;
			else
				nr_empty++;
		}
	
	sum = 1LL*n*n*(n*n+1)/2 - sum;
	sum *= 2;
	sum /= nr_empty;
	
	dr = sum + nr_empty - 1;
	dr /= 2;
	st = dr - nr_empty + 1;
	printf("%d %d\n", st, dr );
	return 0;
}
