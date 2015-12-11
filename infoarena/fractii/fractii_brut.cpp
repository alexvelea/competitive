#include <cstdio>
#include <iostream>
using namespace std;
int i,j,n,rez;
int gcd( int a, int b ){
	if( b == 0 )
		return a;
	return gcd( b, a%b );
}
int main(){
	freopen("fractii.in","r",stdin);
//	freopen("fractii.out","w",stdout);
	cin>>n;
	for( i=1; i<=n; ++i ){
		for( j=1; j<=n; ++j ){
			if( gcd(i,j) == 1 )
				rez++;
		}
	}
	cout<<rez;
	return 0;
}
