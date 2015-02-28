#include <cstdio>

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
#define max_n 100005

bool mysort ( pair<int,int> a, pair<int,int> b ){
	if ( a.fi == b.fi )
		return a.se < b.se;
	return a.fi < b.fi;
}

struct edge {
    int a,b,c;
} ;

long long rez = 1;
int n,i,nr,j, MOD;
pair<int,int> A[ 2*max_n ];

int main(){
	scanf ("%d", &n );
	for ( i=1; i<=n; ++i ){
		scanf ("%d", &A[ i ].fi );
		A[ i ].se = i;
	}
	for ( i=1; i<=n; ++i ){
		scanf ("%d", &A[ i+n ].fi );
		A[ i+n ].se = i;
	}
	n*=2;
	scanf ("%d", &MOD );
	sort ( A+1, A+n+1, mysort );
	for ( i=1; i<=n; ){
		j=i;
 		nr = 0;
		while ( i<=n && A[ j ].fi == A[ i ].fi ){
			++i;
		    ++nr;
		}
		while ( j < i ){
			if ( ( j+1 == i ) || A[ j ].se != A[ j+1 ].se ){
				rez = ( 1LL*rez*nr ) % MOD;
				nr--;
				j++;
			}
			else{
				if ( nr & 1){
					rez = ( ( ( 1LL * rez * nr ) % MOD ) * 1LL * ( ( nr-1 ) /2 ) ) % MOD;
				}
				else{
					rez = ( ( ( 1LL * rez * ( nr /2 ) ) % MOD ) * 1LL * ( nr-1 ) ) % MOD;
				}
			    j+=2;
				nr-=2;
			}
		}
	}
	printf("%I64d\n", rez);      
	return 0;
}
