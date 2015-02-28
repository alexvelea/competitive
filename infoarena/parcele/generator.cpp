#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
#define maxval 20
int V[maxval][maxval];
int main(){

	freopen ("parcele.in","w",stdout);
	int x,y,n,i; 
	srand ( time(NULL) );
	x=rand()%maxval;
	y=rand()%maxval;
	n=10;
	printf("%d %d %d\n",x,y,n);
	for ( i=1; i<=n; i++ ){
		do {
			x=rand()%maxval;
			y=rand()%maxval;
		}while ( V[x][y] );
		V[x][y]=1;
		printf("%d %d\n",x,y);
	}
	return 0;
}
