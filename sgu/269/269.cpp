#include <cstdio>

#include <algorithm>
#include <iostream>

using namespace std;

struct nrmare {
	int val[600];
	nrmare (){
		int i=1;
		for ( ; i<600; ++i )
			val[i]=0;
		val[0]=1;
	}
} Sol[ 3 ][ 260 ];
int Nr[ 260 ];

int n,m,i,j;

void sum_prod ( int j, int val ){
	int l=0,t=0,o=0;
	for ( l=1; l <= max ( Sol[ 0 ][ j-1 ].val[ 0 ] , Sol[ 1 ][ j ].val[ 0 ] ) || t || Sol[ 1 ][ j ].val[ l ] || l<o; ++l ){
		Sol[ 1 ][ j ].val[l] += val * Sol[ 0 ][ j-1 ].val[l] ;
		t = Sol[ 1 ][ j ].val[l] / 10;
		Sol[ 1 ][ j ].val[l] %= 10;
		int ct=t;
		o=l+1;
		while ( ct ){
			Sol[ 1 ][ j ] .val[o] += ct%10;
			o++;
			ct/=10;
		}
	}
	Sol[ 1 ][ j ].val[ 0 ] = l-1;
	return ;
}

int main(){
    scanf ("%d %d", &n, &m );
	for ( i=1; i<=n; ++i ){
		scanf ("%d", &Nr[ i ] );
	}
	Sol[ 0 ][ 0 ].val[1] = 1;
	sort ( Nr+1, Nr+n+1 );
	for ( i=1; i<=n; ++i ){
		Sol[ 0 ][ 0 ].val[1] = 1;
		for ( j=1; j<=i && j<=m; ++j ){
			Sol[1][j]=Sol[0][j];
			if ( Nr[ i ] >= j ){
				sum_prod ( j, Nr[i]-j+1 );
			}
		}
		for ( j=1; j<=i && j<=m; ++j ){
			Sol[0][j]=Sol[1][j];
			Sol[1][j]=Sol[2][j];
		}
	}
	for ( i=Sol[0][m].val[0]; i>0; --i )
		printf("%d", Sol[0][m].val[i]);

	return 0;
}
