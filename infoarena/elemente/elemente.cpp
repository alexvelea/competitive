#include <cstdio>

#include <algorithm>

using namespace std;

const int max_n = 100005, Mod=1000003;

int El[max_n], Ap[max_n];
int n, k, rez, i;
int p;
int st, dr;

int main(){
	freopen("elemente.in","r",stdin);
	freopen("elemente.out","w",stdout);
	scanf("%d %d", &n, &k );
	for( i=1; i<=n; ++i )
		scanf("%d", &El[i] );
	sort( El+1, El+n+1 );
 	st = dr = 1;
	for( ; st<=n; ++st ){
		while( dr <= n && El[dr] - El[st] <= k )
			++dr;
		--dr;
 		// rez += 2^(dr-st)
 		Ap[dr-st] ++;
	}
	p = 1;
	for( i=0; i<=n; ++i ){
		// avem p = 2^i
		// adunam la rezultat
		if( Ap[i] )
			rez = ( 1LL * Ap[i] * p + rez ) % Mod;
		p *= 2;
		while( p >= Mod )
			p-=Mod;
	}
	printf("%d\n", rez );
	return 0;
}
