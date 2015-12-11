
#include <fstream>
#include <iostream>

using namespace std;

	ifstream in("x.in");
	ofstream out("x.out");
	#define max_n 1000005

int n,m,q,i,j,k;
int a,b;

int Pre[ max_n ], St[ max_n ], Dr[ max_n ];
char A[ max_n ], B[ max_n ];

void prefix (){
	int k=0,i;
	for ( i=2; i<=m; ++i ){
		while ( k && B[ i ] != B[ k+1 ] ){
			k = Pre[ k ];
		}
		if ( B[ i ] == B[ k+1 ] )
			k++;
		Pre[ i ] = k;		
	}
	return ;
}

void max ( int &a, int b ){
	if ( b > a )
		a=b;
	return ;
}
int main(){
	
	in>>n>>m>>q;
	for ( i=1; i<=n; ++i ){
		in>>A[i];
	}
	A[ 0 ] = '$';
	for ( i=1; i<=m; ++i ){
		in>>B[i];
	}
	prefix();
	k=0;
	for ( i=1; i<=n; ++i ){
		while ( St[ i ] < m && ( A[ i + St[ i ] ] == B[ St[ i ] + 1 ] ) ){
			St[ i ] ++;
		}
		max ( St[ i + St[ i ] - Pre[ St[ i ] ] ] , Pre[ St[ i ] ] );
	}
	for ( i=n; i; --i ){
		while ( Dr[ i ] < m && ( A[ i - Dr[ i ] ] == B[ Dr[ i ] +1 ] ) ){
			Dr[ i ] ++;
		}
		max ( Dr[ i - ( Dr[ i ] - Pre[ Dr[ i ] ] ) ] , Pre[ Dr[ i ] ] );
	}
/*	for ( i=1; i<=m; ++i ){
		printf("%d\t",St[ i ] );
	}
	printf("\n");
	for ( i=1; i<=m; ++i ){
		printf("%d\t",Dr[ i ] );
	}*/
	for ( ; q; --q ){
		in>>a>>b;
		a--;
		++b;
		out<<min( Dr[ a ], St[ b ])<<"\n";
	}
	return 0;
}
