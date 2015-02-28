#include <cstdio>

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

const int max_n = 100005, INF = 0x3f3f3f3f;

int n, m, i;
int El[max_n];
bool Inside[max_n];

vector<int> IntEl[ 260*1030 ], IntAib[ 260*1030 ];

void make_int( int st, int dr, int nod ){
	int m = ( st + dr ) / 2;
 	IntEl[nod].reserve( dr-st+2 );
	IntAib[nod].reserve( dr-st+2 );
	IntEl[nod].insert( IntEl[nod].begin(), El+st, El+dr+1 );
	sort( IntEl[nod].begin(), IntEl[nod].end() );
 	for( i=0; i<=dr-st+1; ++i )
		IntAib[nod][i] = ( (i) & ( -(i) ) );
	if( st == dr )
		return ;
	make_int( st, m, 2*nod );
	make_int( m+1, dr, 2*nod+1 );
}

void IntAdd( int st, int dr, int nod, int poz, int val ){
 	int m = ( st + dr ) / 2;
	int ind = lower_bound( IntEl[nod].begin(), IntEl[nod].end(), El[poz] ) - IntEl[nod].begin();
	ind++;
	while( ind <= int(IntEl[nod].size()) ){
		IntAib[nod][ind] += val;
		ind += ind & (-ind);
	}
	if( st == dr )
		return ;
	if( m >= poz )
		IntAdd( st, m, 2*nod, poz, val );
	else
		IntAdd( m+1, dr, 2*nod+1, poz, val );
}

int get_lower( int st, int dr, int nod, int c1, int c2, int target ){
	if( c1 > dr || c2 < st )
		return 0;
	int m = ( st + dr ) / 2;
 	if( c1 <= st && dr <= c2 ){
		int ind = lower_bound( IntEl[nod].begin(), IntEl[nod].end(), target ) - IntEl[nod].begin();
		int rez = 0;
		while( ind ){
			rez += IntAib[nod][ind];
			ind -= ind&(-ind);
		}
		return rez;
	}
	int rez = 0;
	rez += get_lower( st, m, 2*nod, c1, c2, target );
	rez += get_lower( m+1, dr, 2*nod+1, c1, c2, target );
	return rez;
}

int main(){ 
	freopen("mess.in","r",stdin);
	freopen("mess.out","w",stdout);
	vector<int> Normalizare;
	scanf("%d %d", &n, &m );
 	for( i=1; i<=n; ++i ){
		scanf("%d", &El[i] );
 		Normalizare.push_back( El[i] );
	}
	sort( Normalizare.begin(), Normalizare.end() );
 	for( i=1; i<=n; ++i ){
		El[i] = lower_bound( Normalizare.begin(), Normalizare.end(), El[i] ) - Normalizare.begin() + 1;
		Inside[i] = true;
	}
	make_int( 1, n, 1 );
	int p, q, k, t;
	int mx=0, aa;
	while( m-- ){
		scanf("%d", &t );
		if( t == 1 ){
			scanf("%d", &p );
 			if( Inside[p] )
				IntAdd( 1, n, 1, p, -1 );
			else
				IntAdd( 1, n, 1, p, +1 );
			Inside[p] ^= 1;
		}else{
			scanf("%d %d %d", &p, &q, &k );
			int pd = (1<<20);
 			int rez = 0;
 			for( ; pd; pd>>=1 )
				if( pd + rez <= n )
					if( get_lower( 1, n, 1, p, q, pd+rez ) < k )
 		   				rez += pd;
			printf("%d\n", Normalizare[rez-1] );
		}
	}
	return 0;
}
