#include <cstdio>
using namespace std;

int b2( int x ){
 	int i = -1;
	while( x ){
		i++;
		x >>= 1;
	}
	return i;
}
int cnt1( int x ){
	int i=0;
	while( x ){
		i++;
		x -= x & (-x);
	}
	return i;
}
void Make_Best( int ind, int n ){
	// facem zero
 	for( i=0; i<(1<<n); ++i ){
		Best[ind][i] = 0;
		Other[i] = 0;
		Bad[i] = 0;
	}
	for( i=1; i<(1<<n); ++i ){
		// facem din trecut
		st = i - ( i & (-i) );
		last = b2( i & (-i) );

		Bad[i] = Bad[st] | BadInside[ind][last];
		Other[i] = Other[st] | BadOther[last];

 		Best[ind][i] = Best[ind][st];
		st -= st & (-st);
		st += i & (-i);
		Best[ind][i] = max( Best[ind][i], Best[ind][st] );

		if( ( i & Bad[i] ) == 0 )
			// e ok
			Best[ind][i] = max( Best[ind][i], cnt1(i) );
	}
}

int main(){
	scanf("%d", &T );
	while( T-- ){
		scanf("%d %d", &n, &m );
		for( i=0; i<=n; ++i )
			for( j=0; j<=n; ++j )
				Ally[i][j] = true;
		while( m-- ){
			scanf("%d %d", &a, &b );
			a--;
			b--;
			Ally[a][b] = Ally[b][a] = false;
		}
		mid = n/2;
 		for( i=0; i<mid; ++i )
			for( j=0; j<mid; ++j )
				if( !Ally[i][j] )
					BadInside[0][i] |= ( 1<< (j) );
		for( i=mid; i<n; ++i )
			for( j=mid; j<n; ++j )
				if( !Ally[i][j] )
					BadInside[1][i-mid] |= ( 1<< (j) );
		for( i=mid; i<n; ++i )
			for( j=0; j<mid; ++j )
				if( !Ally[i][j] )
					BadOther[i-mid] |= ( 1<<j );

 		Make_Best(0, mid);
		Make_Best(1, n-mid);

	}
	return 0;
}
