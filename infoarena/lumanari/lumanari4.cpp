#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

const int INF=0x3f3f3f3f, max_n=200005;

int El[max_n], Last[max_n];
long long Sum[max_n];
int n,a,i;

int main(){
	freopen("lumanari.in","r",stdin);
	freopen("lumanari.out","w",stdout);
	scanf("%d", &n );
	for( i=1; i<=n; ++i ){
		scanf("%d", &a );
		El[i]=min(a,n);
	}
	sort( El+1, El+n+1 );
 	for( i=1; i<=n; ++i )
		Sum[i]=0LL+Sum[i-1]+El[i];
 	Last[n+1]=n+5;
	for( i=n; i; --i ){
		// calculam "expected time" ca sa avem negativ aici
		Last[i]=Last[i+1];
		while( Sum[i]-1LL*Last[i]*(Last[i]+1)/2 < 0 )
			Last[i]--;
		Last[i]++;
	}
 	int mn=INF;
	for( i=n; i; --i ){
		mn=min( mn, Last[i]+(n-i) );
 		if( mn-1<=(n-i+1 ) ){
			printf("%d\n",n-i+1);
			return 0;
		}
	}
	printf("%d\n", n);
	return 0;
}
