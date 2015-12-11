#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

const int max_n=50005;

int El[max_n];
long long St[max_n], Dr[max_n], sum;
int i, x, y;
int n, m;

long long max( long long a, long long b ){
	if( a>b )
		return a;
	return b;
}
void get_max( long long &a, long long b ){
	if( a<b )
		a=b;
}

struct nod_tree{
	long long BestSt, BestMid, BestDr, Sum;
	nod_tree(){
		BestSt = BestDr = BestMid = Sum = 0;
	}
	nod_tree( long long val ){
		BestSt = BestDr = BestMid = Sum = val;
	}
	nod_tree( long long _BestSt, long long _BestMid, long long _BestDr, long long _Sum ){
		BestSt = _BestSt;
		BestMid = _BestMid;
		BestDr = _BestDr;
		Sum = _Sum;
	}
	void debug(){
		cerr<<BestSt<<"|"<<BestMid<<"|"<<BestDr<<"\t"<<Sum<<"\n";
	}
} Aint[140000], empty_tree(0);

void make_tree( int st, int dr, int nod ){
	if( st == dr ){
		long long val = max( El[st], 0 );
		Aint[nod] = nod_tree( Dr[dr+1]+val, St[st-1]+val+Dr[dr+1], St[st-1]+val, El[st] );
		return ;
	}
	int mid=(st+dr)/2;
	make_tree( st, mid, 2*nod );
	make_tree( mid+1, dr, 2*nod+1 );
	Aint[nod].BestMid = max( Aint[2*nod].BestMid, Aint[2*nod+1].BestMid );
	get_max( Aint[nod].BestMid, Aint[2*nod].BestDr + Aint[2*nod+1].BestSt );
	Aint[nod].BestSt = Aint[2*nod].BestSt;
	get_max( Aint[nod].BestSt, Aint[2*nod+1].BestSt + Aint[2*nod].Sum );
	Aint[nod].BestDr = Aint[2*nod+1].BestDr;
	get_max( Aint[nod].BestDr, Aint[2*nod].BestDr + Aint[2*nod+1].Sum );
	Aint[nod].Sum = Aint[2*nod].Sum + Aint[2*nod+1].Sum;
	return ;
}

nod_tree get_tree( int st, int dr, int c1, int c2, int nod ){
	int mid = (st+dr) / 2;
	if( c1<=st && dr<=c2 )
		return Aint[nod];
	if( mid<c1 )
		return get_tree( mid+1, dr, c1, c2, 2*nod+1 );
	if( mid+1 > c2 )
		return get_tree( st, mid, c1, c2, 2*nod );
   nod_tree s, d, act;
	s=get_tree( st, mid, c1, c2, 2*nod );
	d=get_tree( mid+1, dr, c1, c2, 2*nod+1 );
	
	act.BestMid = max( s.BestMid, d.BestMid );
	act.BestSt = s.BestSt;
	act.BestDr = d.BestDr;
	act.Sum = s.Sum + d.Sum;
 	
	get_max( act.BestMid, s.BestDr + d.BestSt );
	get_max( act.BestSt, d.BestSt + s.Sum );
	get_max( act.BestDr, s.BestDr + d.Sum );
	return act;
}
int main(){
	freopen("3max.in","r",stdin);
	freopen("3max.out","w",stdout);
	scanf("%d %d", &n, &m );
	for( i=1; i<=n; ++i )
		scanf("%d", &El[i] );
	long long sum;
	sum=0;
	for( i=1; i<=n; ++i ){
		sum+=El[i];
		get_max( sum, 0 );
		St[i]=St[i-1];
		get_max( St[i], sum );
	}
	sum=0;
	for( i=n; i; --i ){
		sum+=El[i];
		get_max( sum, 0 );
		Dr[i]=Dr[i+1];
		get_max( Dr[i], sum );
	} 
	make_tree( 1, n, 1 );
	while( m-- ){
		scanf("%d %d", &x, &y );
		if ( y == 1 || n == 2 ){
			printf("0\n");
			continue;
		}
		nod_tree act = get_tree( 1, n, x, y, 1 );
 		printf("%lld\n",act.BestMid);
	}
	return 0;
}
