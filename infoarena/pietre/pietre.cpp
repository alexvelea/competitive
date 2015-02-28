#include <cstdio>
#include <algorithm>

using namespace std;

#define max_n 1005005

int Viz[ max_n ],Rez[ max_n ];

int main(){
	freopen("pietre.in","r",stdin);
	freopen("pietre.out","w",stdout);
	int d,i;
	int t,a,b;
	i=1;
	for( d=1; i+d<max_n; ++d ){
		while( i<max_n && Viz[i] )
			i++;
		if( i<max_n ){
			Rez[d]=i;
			Viz[i]=1;
		}
		if( i+d<max_n )
			Viz[i+d]=1;
	}
	scanf("%d", &t );
	for( ; t; --t ){
 		scanf("%d %d", &a, &b );
		if( a > b )
			swap(a,b);
		if( Rez[ b-a ] == a && b-a<=d )
			printf("2\n");
		else
			printf("1\n");
	}
	return 0;
}


