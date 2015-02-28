#include <cstdio>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int max_n = 3005, max_k = 505;

short Aint[max_k][10*max_n];
int El[max_n];
vector<int> Normalizare;

int n, k, i, j;
short act;

void get_max( short &a, short b ){
	if( a < b )
		a = b;
}

short AintQuery( int k, int st, int dr, int nod, int c1, int c2 ){
	if( c1 <= st && dr <= c2 )
		return Aint[k][nod];
	if( c2 < st || c1 > dr )
		return 0;
	short rez = 0, m = ( st + dr ) / 2;
 	rez = AintQuery( k, st, m, 2*nod, c1, c2 );
	get_max( rez, AintQuery( k, m+1, dr, 2*nod+1, c1, c2 ) );
	return rez;
}

void AintUpdate( int k, int st, int dr, int nod, int poz, int val ){
	if( st <= poz && poz <= dr )
		;
	else
		return ;
	get_max( Aint[k][nod], val );
	if( st == dr )
		return ;
	int m = ( st + dr ) / 2;
	if( poz <= m )
		AintUpdate( k, st, m, 2*nod, poz, val );
	else
		AintUpdate( k, m+1, dr, 2*nod+1, poz, val );
	return ;
}

int main(){
	freopen("ksecv2.in","r",stdin);
	freopen("ksecv2.out","w",stdout);
	scanf("%d %d", &n, &k );
 	for( i=1; i<=n; ++i ){
		scanf("%d", &El[i] );
		Normalizare.push_back( El[i] );
	}
	sort( Normalizare.begin(), Normalizare.end() );
	Normalizare.resize( unique( Normalizare.begin(), Normalizare.end() ) - Normalizare.begin() );
	for( i=1; i<=n; ++i )
		El[i] = lower_bound( Normalizare.begin(), Normalizare.end(), El[i] ) - Normalizare.begin();
	int mx = -1;
	for( i=1; i<=n; ++i ){
		for( j=1; j<=k; ++j ){
			act = AintQuery( j, 1, n, 1, 1, El[i] );
			get_max( act, AintQuery( j-1, 1, n, 1, El[i]+1, n ) );
			if( !act && j != 1)
				continue;
			act++;
 			if( j == k && mx < act )
				mx = act;
			AintUpdate( j, 1, n, 1, El[i], act );
		}
	}
	printf("%d\n",mx);
	return 0;
}
