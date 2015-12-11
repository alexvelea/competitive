#include <cassert>
#include <cstdio>
#include <iostream>
using namespace std;

const int max_n=200005;
void get_min( int &a, int b ){
	if( a>b )
		a=b;
}

int n,m;
int Inside[2*max_n], Outside[2*max_n];
int cntinside;
int i,j,a;

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
	Inside[0]=Outside[0]=0;
 	Inside[mx]++;
	st=dr=mx;
	Outside[mx]--;
	cntinside=1;
	for( i=1; i<=m; ++i ){
		// incercam sa mai punem in stiva 1 element
		if( st == i ){
			cntinside-=Inside[st];
			Inside[st]=0;
 			while( !Inside[st] && cntinside )
				st++;
		}
		while( !Outside[dr] )
			dr--;
		// stim sigur ca avem elementul dr
 		while( cntinside && dr+i > st ){
			Outside[ st-i ] += Inside[st];
			cntinside-=Inside[st];
			Inside[st]=0;
 			while( cntinside && !Inside[st] )
				st++;
		}
		while( cntinside < i+1 && dr>0 ){
			d=(i+1)-cntinside;
 			if( Outside[dr] >= d ){
				Inside[dr+i]+=d;
				cntinside+=d;
 				Outside[dr]-=d;
				if( st>dr+i )
					st=dr+i;
			}else{
				Inside[dr+i]+=Outside[dr];
				cntinside+=Outside[dr];
 				Outside[dr]=0;
				if( st>dr+i )
					st=dr+i;
			}
			while( dr>0 && !Outside[dr] )
				dr--;
		}
		// cazul de terminare.
		if( st-i-1<0 || cntinside<i+1 ){
//			printf("%d", i);
			cerr<<i<<"\n";
			return 0;
		}
	}
	cerr<<m<<"\n";
//	printf("%d\n",m);
	return 0;
}
