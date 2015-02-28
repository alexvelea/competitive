#include <cstdio>
#include <cmath>

#include <algorithm>
#include <queue>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

#define pb push_back
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define mp make_pair
#define fi first
#define se second
#define INF 0x3f3f3f3f
#define multi 5000000


double alpha;
int x,y,n,m,i;

struct edge {
    int a,b,c;
} ;

int main(){
 	scanf("%d %d", &n, &m );
	n=n-m;
	if ( m == 3 && n >= 2 ){
		printf("-1\n");
		return 0;
	}
	for( i=1; i<=m; ++i ){
		alpha = 1.0*M_PI*((i+3*m/2)%(2*m))/m;
		x=sin(alpha)*multi;
		y=cos(alpha)*multi;
		printf("%d %d\n",x,y-6000000);
	}
	for( i=1; i<=n; ++i ){
		alpha = 1.0*M_PI*(i+n/2)/n;
		x=sin(alpha)*multi;
		y=cos(alpha)*multi;
		printf("%d %d\n",x,y+6000000);
	}
	return 0;
}
