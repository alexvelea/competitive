#include <cstdio>
using namespace std;

	#define max_n 50005

	int Aib[max_n];
	int n,i,last;

int query ( int s ){
	int ind = ( 1<< 15 );
	int rez=0, act=0;
	for ( ; ind; ind>>=1 ){
		if ( Aib[rez+ind]+act < s ){
			act+=Aib[ind+rez];
			rez+=ind;
		}
	}
	return rez+1;
}

void update ( int ind, int val ){
	for ( ; ind<=(1<<15); ind+=(ind)&(-ind) ){
		Aib[ind]+=val;
	}
}

int main(){
	freopen ("order.in","r",stdin);
	freopen ("order.out","w",stdout);
	scanf ("%d", &n );
	for ( i=1; i<=n; i++ ){
		update ( i,1 );
	}
	last = 2;
	printf("2 ");
	int x=2;
	for ( i=1; i<n; i++ ){
		update ( x, -1 );
		last += i;           
		last %= (n-i);
		if ( last == 0 ){
			last = n-i;
		}	
		x= query ( last );

		printf("%d ", x);

	}
	return 0;
}
