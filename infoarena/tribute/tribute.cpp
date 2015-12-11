#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

	#define pb push_back
	vector<int> D[2];
	int n,dx,dy,a,b,i;

int solve ( int i, int l ){
	int ist=0,idr=0;
	int d=0;
	int rez=0,minim = 0x3f3f3f3f;
	sort ( D[i].begin(), D[i].end() );
	d=D[i][0];
	for ( ; idr<n && D[i][idr] <= d+l; idr++ )
		;
	for ( int p=idr; p<n; p++ ){
		rez+=(D[i][p]-d-l);
	}
	while ( D[i][ist] == d ){
		ist++;
	}
	minim=rez;
	D[i].push_back(0x3f3f3f3f);
	for ( ; ist<n;  ){
		int k = min ( D[i][ist]-d , D[i][idr]-d-l );
		d+=k;
		rez+=(ist)*k;
		rez-=(n-idr)*k;
		while ( D[i][ist] == d )
			ist++;
		while ( D[i][idr] == d+l )
			idr++;
		if ( minim > rez )
			minim=rez;
	}
	return minim;
}

int main(){

    	freopen ("tribute.in","r",stdin);
		freopen ("tribute.out","w",stdout);

	scanf ("%d %d %d", &n, &dx, &dy );
	for ( i=1; i<=n; i++ ){
		scanf ("%d %d", &a, &b );
		D[0].pb(a);
		D[1].pb(b);
	}
	int rez=0;
	rez+=solve(0,dx);
	rez+=solve(1,dy);                    
	printf("%d", rez);
	return 0;
}
