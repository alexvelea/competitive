#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

	#define max_n 10005
	#define INF (1<<30)

	int n,m,k;
	int a,b;
	int P[2*max_n],D[2*max_n];
	int Urm[2*max_n];

	struct arbore {
		int val,max;
	} Arb[(1<<18)];

	int bs ( int val ){
		int ind = (1<<16),rez=0;
		for ( ; ind; ind>>=1 )
			if ( ( rez+ind <=m ) && ( D[rez+ind] <= val ) )
				rez+=ind;
		return rez;
	}
	struct point {
		int x,y;
	} T[max_n];
	bool mysort ( point a, point b ){
		return a.y<b.y;
	}

void update ( int a, int b, int st, int dr, int nod, int val ){
	if ( ( a == st ) && ( b == dr ) ){
		Arb[nod].val+=val;
	}
	else{
		int m=(st+dr)/2;
		if ( a<=m && m+1<=b ){
			update ( a, m, st, m, 2*nod, val );
			update ( m+1, b, m+1, dr, 2*nod+1, val );
		}
		if ( b<=m ){
			update ( a, b, st, m, 2*nod, val );
		}
		if ( m+1<=a ){
			update ( a, b, m+1, dr, 2*nod+1, val );
		}
	}
	if ( st == dr )
		Arb[nod].max = Arb[nod].val;
	else
		Arb[nod].max = max ( Arb[2*nod].max, Arb[2*nod+1].max ) + Arb[nod].val;
	return ;
}

bool solve ( int d ){
	// calculam sirul "urm"
	// unde Urm[x] = Ultima pozitie a.i. D[i]+d>=D[ Urm[i] ]
	// unde e e sirul cu valorile normalizate
	int ist,idr=1;
	for ( ist=1; ist<=m; ist++ ){
    	while ( ( idr<=m ) && ( D[ist]+d >= D[idr] ) ){
			idr++;
		}
		Urm[ist]=idr-1;
	}
	ist=1;
	idr=1;
	for ( ; idr<=n; idr++ ){
		while ( D[ T[ist].y ]+d < D[ T[idr].y ] ){
			update ( T[ist].x, Urm[ T[ist].x ], 1, m, 1, -1 );
			ist++;
		}
		update ( T[idr].x, Urm[ T[idr].x ], 1, m, 1, 1 );
		if ( Arb[1].max >=k ){
			for ( ; ist<=idr; ist++ ){
				update ( T[ist].x, Urm[T[ist].x], 1, m, 1, -1 );
			} 
			return 1;
		}
	}
	for ( ; ist<=n; ist++ ){
		update ( T[ist].x, Urm[T[ist].x], 1, m, 1, -1 );
	}
	return 0;
}



int main(){
		
		freopen ("castori.in","r",stdin);
		freopen ("castori.out","w",stdout);

	int i;
	scanf ("%d %d", &n, &k);
    for ( i=1; i<=n; i++ ){
		scanf ("%d %d", &a, &b );
		T[i].x=b+a;
		T[i].y=b-a;
		P[++m]=b+a;
		P[++m]=b-a;
	}
	P[++m]= INF;
	P[++m]=-INF;
	sort ( P+1, P+m+1 );
	int l=0;
	for ( i=1; i<=m; ){
		int j=i;
		while ( ( P[i]==P[j] ) && ( i<=m ) )
			i++;
		D[++l]=P[j];			
	}
	m=l;
	for ( i=1; i<=n; i++ ){
		T[i].x=bs(T[i].x);
		T[i].y=bs(T[i].y);
	}                   
	sort ( T+1, T+1+n, mysort );
 	// cautam binar dimensiunea patratului
	long long ind=(1<<30),rez=0;
	for ( ; ind; ind >>= 1 ){
    	if ( !solve(ind+rez) ){
			rez+=ind;
		}
	}

	rez++;
	printf("%d\n",rez);
	return 0;
}
