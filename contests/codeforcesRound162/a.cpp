#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

	#define pb push_back
	#define fi first
	#define se second
	#define max_n 1000005


	int D1[max_n],D2[max_n],nr1,nr2,i;
	char Text[ max_n ];

struct edge {
    int a,b,c;
} ;

int main(){
	scanf ("%s", &Text );
	int n=strlen ( Text );
	for ( i=0; i<n; ++i ){
		if ( Text[ i ] == 'l' ){
			D2[ ++nr2 ] = i+1;
		}
		else{
			D1[ ++nr1 ] = i+1;
		}
	}
	for ( i=1; i<=nr1; ++i ){
		printf("%d\n", D1[ i ] );
	}
	for ( i=nr2; i>=1; --i ){
		printf("%d\n", D2[ i ] );
	}
	return 0;
}
