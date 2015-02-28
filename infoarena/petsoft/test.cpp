#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
int main(){
	int i,n,ind;
	srand( time(NULL) );
	freopen("petsoft.in","w",stdout);
	n=1000;
	printf("%d\n",n);
	for( i=2; i<=n; ++i ){
		ind=rand()%(i-1);
		ind++;
 		printf("%d\n",ind);
	}
	return 0;
}
