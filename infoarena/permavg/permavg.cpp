#include<cstdio>
using namespace std;

const int max_n=33000;

int n,cn;
int i,Perm[max_n];

void solve( int st, int dr, int start, int pas ){
	if( st == dr ){
		Perm[st]=start;
		return ;
	}
	int m=(st+dr)/2;
	solve( st, m, start, pas<<1 );
	solve( m+1, dr, start+pas, pas<<1 );
}

int main(){
	freopen("permavg.in","r",stdin);
	freopen("permavg.out","w",stdout);
	scanf("%d", &n );
 	for( i=1; i<=n; ++i )
		Perm[i]=i;
	cn=1;
	while( cn<n )
		cn<<=1;
	solve(1,cn,1,1);
	for( i=1; i<=cn; ++i ){
		if( Perm[i]<=n )
			printf("%d ",Perm[i]);
	}
	return 0;
}
