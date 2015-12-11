#include <cstdio>
using namespace std;
int gcd( int a, int b ){
	if( !b ) return a;
	return gcd( b, a%b );
}
int main(){
    freopen("dreptunghiuri.in","r",stdin);
	freopen("dreptunghiuri.out","w",stdout); 
	long long rez=0;
	int n,m,i,j,a,b;
	scanf("%d %d", &n, &m );
	for( i=1; i<n; ++i )
		for( j=0; j<m; ++j ){
			if( gcd(i,j) == 1 ){
				for( a=1; i*a<=n; ++a ){
					for( b=1; i*a+b*j<n && j*a+i*b<m; ++ b ){
						rez+=1LL*(n-i*a-j*b)*(m-j*a-i*b);
					}
				}
			}
		}
	printf("%lld\n",rez);
	return 0;
}
