#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

	#define pb push_back
	#define fi first
	#define se second
	#define MOD 666013
	#define max_n 1005
	#define max_m 100005

int Nr[13]={0,31

int get_date ( int a, int b ){
	return Sum[a-1]+b;
}

int main(){

	scanf ("%d", &n );
	for ( i=1; i<=n; i++ ){
		scanf ("%d %d %d %d", &a, &b, &T[i].p, &T[i].t );
		T[i].s = get_date ( a,b );
	}
	
	return 0;
}

