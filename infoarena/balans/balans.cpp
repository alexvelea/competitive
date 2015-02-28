#include <cstdio>
#include <iostream>
using namespace std;

const int max_n=305;
const double EPS=0.00000001;

int El[max_n][max_n];
int n,m,R,C;
int i,j;
double rez=0.0;

int penis=0;

void solve( ){
	int i,j,r,c;
	int act;

	for( i=1; i<=2*n; ++i )
		for( j=1; j<=2*m; ++j )
			El[i][j] = El[i][j-1] + El[i-1][j] - El[i-1][j-1] + El[i][j];
	for( c=max(1,C); c<=m; ++c )
		for( r=max(1,R); r<=n; ++r )
			for( i=n+1; i<=2*n; i++ )
				for( j=m+1; j<=2*m; ++j ){
					act=El[i][j]+El[i-r][j-c]-El[i][j-c]-El[i-r][j];
					if( act > rez*r*c )
						rez=1.0*act/r/c;
				}
}

int main(){
	freopen("balans.in","r",stdin);
	freopen("balans.out","w",stdout);
	scanf("%d %d %d %d", &n, &m, &R, &C );
	for( i=1; i<=n; ++i )
		for( j=1; j<=m; ++j ){
			scanf("%d", &El[i][j] );
			El[i+n][j]=El[i][j];
			El[i][j+m]=El[i][j];
			El[i+n][j+m]=El[i][j];
		}
	solve();
	printf("%.3lf", int(1000*rez)/1000.0 );
	return 0;
}
