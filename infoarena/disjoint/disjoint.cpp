#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

#define max_n 100005

int Father[max_n];
int n,m,t,a,b,i,x;

int get_father( int nod ){
	if( Father[nod]!=nod )
		Father[nod]=get_father( Father[nod] );
	return Father[nod];
}

int main(){
	freopen("disjoint.in","r",stdin);
	freopen("disjoint.out","w",stdout);
	srand( time(NULL) );
	scanf("%d %d", &n, &m );
	for( i=1; i<=n; ++i ){
		Father[i]=i;
	}
	for( ; m; --m ){
		scanf("%d %d %d", &t, &a, &b );
 		a=get_father(a);
		b=get_father(b);
		if( t == 1 ){
			x=rand()%2;
			if(x)
				Father[a]=b;
			else
				Father[b]=a;
		}else{
			if( a == b )
				printf("DA\n");
			else
				printf("NU\n");
		}
	}
	return 0;
}
