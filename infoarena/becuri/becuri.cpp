#include <cassert>
#include <cstdio>

#include <iostream>
#include <vector>

using namespace std;

const int max_n = 505, INF = 0x3f3f3f3f;

bool Col[max_n], Lin[max_n];
int i, j, n, m, rez, mn;
bool El[max_n][max_n];

int abs( int a ){
	if( a > 0 )
		return a;
	return -a;
}

void make_lin_col(){
	int i;
   	for( i=1; i<=m; ++i )
		Col[i] = El[1][i] ^ Lin[1];
	for( i=2; i<=n; ++i )
		Lin[i] = El[i][1] ^ Col[1];
 
}

int solve(){
	make_lin_col();
	int a = 0, b = 0;
	for( i=1; i<=n; ++i ){
		a += Lin[i];
//		if( Lin[i] )
//			cerr<<"L->"<<i<<"\n";
	}
	for( i=1; i<=m; ++i ){
		b += Col[i];
//		if( Col[i] )
//			cerr<<"C->"<<i<<"\n";
	}
//	cerr<<"\n";
	bool ok = true;
	for( i=1; i<=n; ++i )
		for( j=1; j<=m; ++j ){
			if( (Lin[i] ^ Col[j] ^El[i][j]) == true )
				ok = false;
		}
 	if( ok && ( ( abs(a-b) % 2 ) == 0 ) )
		return max( a,b );
	else
		return INF;
}

void afiseaza(){
	bool ok = true;
	int i, rez;
	rez = solve();
	vector<int> L, C;
	for( i=1; i<=n; ++i )
		if( Lin[i] )
			L.push_back(i);
	for( i=1; i<=m; ++i )
		if( Col[i] )
			C.push_back(i);
	printf("%d\n", rez );
 	for( ; L.size() > 0 && C.size() > 0; ){
		printf("%d %d\n", L.back(), C.back() );
		L.pop_back();
		C.pop_back();
	}
	ok = false;
	for( ; L.size(); ){
		printf("%d 1\n", L.back() );
		L.pop_back();
	}
	for( ; C.size(); ){
		printf("1 %d\n", C.back() );
		C.pop_back();
	}
}

int main(){
	freopen("becuri.in","r",stdin);
	freopen("becuri.out","w",stdout);
	scanf("%d %d", &n, &m );
	for( i=1; i<=n; ++i )
		for( j=1; j<=m; ++j )
		   scanf("%d", &El[i][j] );
	int a, b;

	a = solve();
	Lin[1] = true;
	b = solve();
	
	if( b >= a )
		Lin[1] = false;
    	
    if( a == INF && b == INF )
		printf("-1\n");
	else
		afiseaza();
	return 0;
}
