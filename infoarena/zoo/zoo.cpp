#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


	#define MaxChar 1000000
	#define verf ( (++CharB==MaxChar) ? ( cin.read(Buffer,MaxChar),CharB=0 ) : (1) )
	
	long CharB=MaxChar-1;
	char Buffer [ MaxChar ];
	
	void cit ( int &a ){
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


	#define max_n 20000
	#define max_m 100005
	#define INF 2000000005
	#define pb push_back


	vector<int> El;

	struct event {
		int x,y,tip,ind; 
		event ( int a, int b, int t, int in ){
			x=a;
			y=b;
			tip=t;
			ind=in;
		}
		event ( ){
			x=y=tip=ind=0;
		}
	} Ev[5*max_m];

	bool mysort ( event a, event b ){
		if ( a.y == b.y ){
			return a.tip<b.tip;
		}
		return a.y < b.y;
	}

    int Rez[4*max_m];
	int n,m,i,j,rez;

	int a,b,c,d,task;
	int Aib[5*max_m];

	int val,val2;

	void add ( int ind, int val ){
		for ( ; ind < val2; ind+=(ind)&(-ind) )
			Aib[ind]+=val;
	}
	int query ( int ind ){
		int rez=0;
		for ( ; ind; ind-=(ind)&(-ind) )
			rez+=Aib[ind];
		return rez;
	}

int main(){
	freopen ("zoo.in","r",stdin);
	freopen ("zoo.out","w",stdout);
verf;

	El.pb(INF);
	El.pb(-INF);

//	scanf ("%d", &n );
cit(n);
	for ( i=1; i<=n; i++ ){
//		scanf ("%d %d", &a, &b );    
cit(a);
cit(b);
    	Ev[ ++task ] = event ( a, b, 0, 0 );
		El.pb( Ev[task].x );
	}

//	scanf ("%d", &m );
cit(m);
	for ( i=1; i<=m; i++ ){
//		scanf ("%d %d %d %d", &a, &b, &c, &d );
cit(a);
cit(b);
cit(c);
cit(d);

		a--;
		b--;

		El.pb(a);
		El.pb(c);



		Ev[ ++task ] = event ( a, b, 1, i );
		Ev[ ++task ] = event ( c, d, 1, i );
		Ev[ ++task ] = event ( a, d, 2, i );
		Ev[ ++task ] = event ( c, b, 2, i );
	}

	sort ( El.begin(), El.end() );
	El.resize ( unique ( El.begin(), El.end() ) - El.begin() );
	sort ( Ev+1, Ev+task+1, mysort );

	val=El.size()+5;
	for ( val2=1; val2<=val; val2<<=1 )
		;

	for ( i=1; i<=task; i++ ){
		int x;
		if ( Ev[i]. tip == 0 ){
			add ( lower_bound( El.begin(), El.end(), Ev[i].x ) - El.begin() , 1 );
		}
		else{
			x = query ( lower_bound ( El.begin(), El.end(), Ev[i].x ) - El.begin()  );
            if ( Ev[i].tip == 1 ){
				Rez[ Ev[i].ind ] += x;
			}
			else{
				Rez[ Ev[i].ind ] -= x;
			}
		}
	}
	for ( i=1; i<=m; i++ ){
		printf("%d\n",Rez[i]);
	}
	return 0;
}
