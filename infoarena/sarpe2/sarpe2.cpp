#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

	#define MOD 666013
	#define pb push_back
	#define max_n 1005
	#define max_val 100005
	#define max_m 100005
	#define mod(a) ((a>=MOD)?(a-MOD):(a))

	int d;
	int dx[8]={0,0,1,1,1,-1,-1,-1};
	int dy[8]={1,-1,0,1,-1,0,1,-1};

	int n,m,a,i,j;
	int Q[max_m];

	struct point {
		int x,y;
		point (){
			x=0;
			y=0;
		}
		point ( int a, int b ){
			x=a;
			y=b;
		}
	} ;

 	vector <point> El;
 	point Ap[max_m];

	int Val[max_n][max_n], Rez[max_n][max_n];

	bool mysort ( point a, point b ){
		return Val[ a.x ][ a.y ]<Val[ b.x ][ b.y ];
	}

int main(){
	freopen ("sarpe2.in","r",stdin);
	freopen ("sarpe2.out","w",stdout);

	scanf ("%d %d", &n, &m );
	for ( i=1; i<=m; i++ ){
		scanf ("%d", &Q[i] );
		Q[i]++;
	}
	for ( i=1; i<=n; i++ ){
		for ( j=1; j<=n; j++ ){
			scanf ("%d", &Val[i][j] );
			Val[i][j]++;
			El.pb( point(i,j) );
		}
	}

	sort ( El.begin(), El.end(), mysort );
    for ( i=0; i<El.size(); ){
		j=i;
		while ( Val[ El[i].x ][ El[i].y ] == Val[ El[j].x ][ El[j].y ] )
			i++;
		Ap[ Val[ El[j].x ][ El[j].y ] ].x=j;
		Ap[ Val[ El[j].x ][ El[j].y ] ].y=i;
	}

	i=1;

	for ( j = Ap[ Q[1] ].x; j< Ap[ Q[1] ].y; j++ ){
    	Rez[ El[j].x ][ El[j].y ]=1;
	}

	for ( i=1; i<m; i++ ){
        for ( j= Ap[ Q[i] ].x; j< Ap[ Q[i] ].y; j++ ){
			for ( d=0; d<8; d++ ){
				if ( Val[ dx[d]+El[j].x ][ dy[d]+El[j].y ] == Q[i+1] ){
					Rez[ dx[d]+El[j].x ][ dy[d]+El[j].y ] += Rez[ El[j].x ][ El[j].y ];
 					Rez[ dx[d]+El[j].x ][ dy[d]+El[j].y ] = mod ( Rez[ dx[d]+El[j].x ][ dy[d]+El[j].y ] ); 
				}
			}
		}
	}

	int rez=0;
	for ( j=Ap[ Q[m] ].x; j<Ap[ Q[m] ].y; j++ ){
		rez += Rez[ El[j].x ][ El[j].y ];
		rez = mod ( rez );
	}
	printf("%d\n",rez);
	return 0;
}
