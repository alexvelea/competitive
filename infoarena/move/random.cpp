#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

#define max_n 100005

bool Viz[ max_n ];
int x,i,n;
int main(){
	freopen("move.in","w",stdout);
	srand( time( NULL ) );
	n = 100000;
	printf("%d\n",n);
	for( i=1; i<=n; ++i ){
		x=rand()%n;
		x++;
		while( x<=n && Viz[ x ] == 1 )
			x++;
		if( x>n ){
			i--;
			continue;
		}
		else{
			printf("%d ",x);
			Viz[ x ] = 1;
		}
	}
	return 0;
}
