#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;


#define MaxChar 1000000
#define verf ( (++CharB==MaxChar) ? ( cin.read(Buffer,MaxChar),CharB=0 ) : (1) )

long CharB=MaxChar-1;
char Buffer [ MaxChar ];

void cit ( int &a )
{
	bool ok=0;
	for ( ; !( (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9') || ( Buffer[ CharB ] == '-' ) ); verf )
		;
	if ( Buffer[ CharB ] == '-' ){
		verf;
		ok=1;
	}
    for ( a=0; (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9'); a*=10,a+=( Buffer[ CharB ]-'0'), verf )
        ;
    if ( ok ){
        a=-a;
    }
}



	#define pb push_back
	#define se second
	#define fi first
	#define max_n 100005
	#define max_m 500005

	int n,m,i,a,b;

	bool Viz[max_n];
	int R[max_n],L[max_n];
	int nr;
	vector<int> T[max_n];

void df ( int nod ){
	L[nod]=++nr;
	Viz[nod]=1;
	for ( int i=0; i<T[nod].size(); i++ )
		if ( !Viz[T[nod][i]] )
			df ( T[nod][i] );
	R[nod]=++nr;
}

int main(){

    	freopen ("maimute.in","r",stdin);
		freopen ("maimute.out","w",stdout);

	verf;
	cit(n);
	for ( i=1; i<n; i++ ){
		cit(a);
		cit(b);
		T[a].pb(b);
		T[b].pb(a);
	}
	df(1);
	cit(m);
	for ( i=1; i<=m; i++ ){
		cit(a);
		cit(b);
		if ( ( L[a]<L[b] && R[a]>R[b] ) || ( L[b]<L[a] && R[b]>R[a] ) )
			printf("DA\n");
		else
			printf("NU\n");
	}
	return 0;
}
