#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

#define max_n 200005
int El[max_n];
int i,n,a;
bool solve( int x ){
	int xc=x-n+1;
	long long p=0;
 	for( int i=1; i<=n; ++i ){
		p+=El[i]-max(0,xc);
		xc++;
		if( p<0 )
			return 0;
	}
	return 1;
}

int main(){
	freopen("lumanari.in","r",stdin);
	freopen("lumanari.out","w",stdout);
	scanf("%d", &n );
 	for( i=1; i<=n; ++i ){
		scanf("%d", &a );
		El[i]=min(n,a);
	}
	sort( El+1, El+n+1 );
	int p=(1<<17), rez=0;
	for( ; p; p>>=1 )
		if( p+rez<=n && solve(p+rez) )
			rez+=p;
	printf("%d",rez);
	return 0;
}
