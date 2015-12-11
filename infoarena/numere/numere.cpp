#include <cstdio>
#include <algorithm>
using namespace std;
int main(){
	freopen("numere.in","r",stdin);
 	freopen("numere.out","w",stdout);
	int t, a, b, ind;
 	scanf("%d", &t );
	while( t-- ){
		scanf("%d %d", &a, &b );
		if( a < b )
			swap( a,b );
		ind = 0;
		while( 1 ){
			if( a%b == 0 || ( int( a/b ) > 1 ) )
				break;
			a -= b;
			swap( a,b );
			ind ^= 1;
		}
 		printf("%d\n", ind+1 );
	}
}
