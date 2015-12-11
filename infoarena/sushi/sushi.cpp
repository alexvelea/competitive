#include <cstdio>
using namespace std;
int main(){

	freopen ("sushi.in","r",stdin);
	freopen ("sushi.out","w",stdout);

	int n;

	scanf ("%d", &n );

	int mx = -1;
	int st,dr;
	int ok=1;

	for ( int i=1; i<=n ; ++i ){
		int a;
		scanf ("%d", &a );
		if ( a > mx ){
			ok=1;
			st=i;
			mx=a;
		}
		if ( a == mx && ok ){
			dr = i;
		}
		else{
			ok=0;
		}
	}
	printf("%d %d %d\n",st,dr,2*mx );
	return 0;
}
