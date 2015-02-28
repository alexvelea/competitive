#include <cstdio>
#include <algorithm>
using namespace std;

	#define max_n 100005

int n,i,l;

struct box{
	int nr,k;
} T[ max_n ];

bool mysort ( box a, box b ){
	return a.k < b.k;
}

int main(){
	scanf ("%d", &n );
	for ( i=1; i<=n; ++i ){
		scanf ("%d %d", &T[i].k, &T[i].nr );
	}
	sort ( T+1, T+n+1, mysort );
	int act=0;
	for ( i=1, l=0; i<=n; ++i ){
		while ( l < T[ i ].k && act ){
			act = (act+3)>>2;         
			++l;
		}
		l = T[ i ].k;
		act = max ( T[ i ].nr, act );
	}
	int rez=T[n].k;
	if ( act == 1 )
		rez++;
	while ( act != 1 ){
		rez++;
		act = ( act+3 ) >>2;
	}
	printf("%d\n",rez);
	return 0;
}
