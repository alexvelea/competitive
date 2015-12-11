#include<cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

const int max_n=200000,max_val=200000;

int main(){
	freopen("lumanari.in","w",stdout);
	int n,i;
	srand( time(NULL) );
	n=rand()%max_n;
	n++;
	printf("%d\n",n);
	for( i=1; i<=n; ++i ){
		printf("%d ",(rand()%max_val)+1);
	}
}
