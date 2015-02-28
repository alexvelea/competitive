#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

	#define INF 0x3f3f3f3f


	#define MaxChar 1000000
	#define verf ( (++CharB==MaxChar) ? ( cin.read(Buffer,MaxChar),CharB=0 ) : (1) )

	long CharB=MaxChar-1;
	char Buffer [ MaxChar ];

	void cit ( int &a )
	{
	    for ( ; !(Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9'); verf )
		;
	    for ( a=0; (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9'); a*=10,a+=( Buffer[ CharB ]-'0'), verf )
		;
	}


	int min ( int a, int b ){
		if ( a < b )
			return a;
		return b;
	}

	int i,n,Sol[200005],val;
	int Aib[300000];


	struct arbore{
		int poz,x,y;
	} T[200005];


	bool mysort ( arbore a, arbore b ){
		return a.y > b.y ;
	}

int query ( int ind ){
	int rez=INF;
	int ok=0;
	for ( ; ind <= 260005; ind+=ind&(-ind) ){
		if ( Aib[ind] ){
			ok=1;
			rez=min(rez,Aib[ind] );
		}
	}
	if ( ok )
		return rez;
	return -1;
}

void update ( int ind, int val ){
	for ( ; ind; ind-=ind&(-ind) ){
		if ( Aib[ind] == 0 )
			Aib[ind]=val;
		else
			Aib[ind]=min(Aib[ind],val);
	}
}

int main(){

   	freopen ("sea2.in","r",stdin);
	freopen ("sea2.out","w",stdout);

	verf;
	cit(n);
	for ( i=1; i<=n; i++ ){
		cit(T[i].x);
		cit(T[i].y);
		T[i].poz=i;
	}
	sort ( T+1, T+n+1, mysort );
	for ( i=1; i<=n; i++ ){
		// query
		val = query ( T[i].x );
		if ( val == -1 || val > T[i].poz ){
			// nu moare cand apare			
			Sol[val]++;
            update ( T[i].x, T[i].poz );
		}
		else{
			Sol[ T[i].poz ]=-1;
		}
	}
	int nr=0;
	for ( i=1; i<=n; i++ ){
		nr++;
		if ( Sol[i] == -1 ){
			printf("%d\n",Sol[i]);
			nr--;
		}
		else{
			nr-=Sol[i];
			printf("%d\n",nr);
		}
	}
	return 0;
}
