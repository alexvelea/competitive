#include <cassert>
#include <cstdio>
#include <iostream>
using namespace std;

const int max_n=200005, INF=0x3f3f3f3f;

void get_min( int &a, int b ){
	if( a>b )
		a=b;
}


int n,m;
int Inside[2*max_n], Outside[2*max_n];
int cntInside;
int i,j,a,del;

void go_down( int &a ){
	while( a && !Outside[a] )
		a--;
}

void debug(){
	int i;
	for( i=1; i<=del; ++i )
		cerr<<"0 ";
	for( i=6-del; i; i-- )
		cerr<<Inside[i]<<" ";
	cerr<<"\n";
	for( i=6; i; --i )
		cerr<<Outside[i]<<" ";
	cerr<<"\n";
}

int main(){
    int mx=0,st,dr,d;

	assert( freopen("lumanari.in","r",stdin) );
	assert( freopen("lumanari.out","w",stdout) );
	scanf("%d", &m );
	for( i=1; i<=m; ++i ){
		scanf("%d", &a );
		get_min(a,m);
		Outside[a]++;
		if( a>mx )
			mx=a;
	}
	
	if( mx == 0 ){
		printf("0\n");
		return 0;
	}

	Outside[mx]--;
	Inside[mx]++;
	st=dr=mx;
 	cntInside=1;
	for( del=1; ; ++del ){
		cntInside-=Inside[del];
		Outside[0]=0;
		Inside[del]=0;
//		debug();
		if( st-del<dr ){
 			Outside[st-del]+=Inside[st];
			cntInside-=Inside[st];
			Inside[st]=0;
			st=INF;
		}
//		debug();

        while( dr>0 && cntInside<del+1 ){
			d=del+1-cntInside;
 			get_min( d, Outside[dr] );
			cntInside+=d;
 			Outside[dr]-=d;
 			Inside[dr+del]+=d;
			get_min(st,dr+del);
			go_down(dr);
		}

		if( cntInside<del+1 ){
			printf("%d\n",del);
			return 0;
		}
	}
	return 0;
}
