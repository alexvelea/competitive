#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

	#define max_n 100005
	#define mod 666013

	int n,m,k,i,T[max_n];
	int a,b,nr;
	int Aib[max_n];
	int Last[max_n],Next[max_n];

	struct qu {
		int a,b,rez,nr;
	} Q[max_n];

	bool mysort ( qu a, qu b ){
		return a.a<b.a;
	}

	bool mysort2 ( qu a, qu b ){
		return a.nr<b.nr;
	}
void add ( int ind, int val ){
	for ( ; ind<=n; ind+=(ind&(-ind)) ){
		Aib[ind]+=val;
		if ( Aib[ind]<mod )
			Aib[ind]+=mod;
		if ( Aib[ind]>=mod )
			Aib[ind]-=mod;
	}
}
int query ( int ind ){
	int rez=0;
	for ( ; ind; ind-=(ind&(-ind)) )
		rez+=Aib[ind];
	return rez%mod;
}


int main(){

	    freopen ("distincte.in","r",stdin);
		freopen ("distincte.out","w",stdout);

	scanf ("%d %d %d", &n, &k, &m );
	for ( i=1; i<=n; i++ ){
		scanf ("%d", &a );
		T[i]=a;
		Next[ Last[a] ]=i;
		if ( !Last[a] ){
			// adaugam elementul 
			add(i,a);
		}
		Last[a]=i;
	}
	for ( i=1; i<=m; i++ ){
		scanf ("%d %d", &a, &b );
		Q[i].a=a;
		Q[i].b=b;
		Q[i].nr=i;
	}
	sort ( Q+1, Q+m+1, mysort );
	nr=1;
    for ( i=1; i<=n; i++ ){                 
      	while ( ( nr<=m ) && Q[nr].a == i ){
			Q[nr].rez=query ( Q[nr].b );
			nr++;
		}
    	// scoatem
		add(i,-T[i]);
	    if ( Next[ i ] ){
			add(Next[ i ],T[i]);
		}
	}
	sort ( Q+1, Q+m+1, mysort2 );
	for ( i=1; i<=m; i++ ){
		printf("%d\n",Q[i].rez);
	}
	return 0;
}
