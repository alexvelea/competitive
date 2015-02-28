#include <cstdio>
using namespace std;

const int max_n=5005, Mod=31333;

int Next[max_n], Last[max_n];

int n, m, mx, i, j;

void mod( int &a ){
	while( a>= Mod )
		a-=Mod;
}

int main(){
	freopen("prietenie2.in","r",stdin);
	freopen("prietenie2.out","w",stdout);
	scanf("%d %d", &n, &m );
	if( n>2*m ){
		Last[1]=1;
		n--;
		mx=2;
	}else{
		n-=2;
		m--;
		mx=3;
		Last[2]=1;
	}
	// punem intai toate perechiile de cate 2
	for( i=1; i<=n-m; ++i, mx++ ){
		for( j=1; j<=mx; ++j ){
			Next[j] += Last[j-1];
			mod( Next[j] );
			Next[j] += Last[j]*(j);
			Next[j] %= Mod;
		}
		for( j=1; j<=mx; ++j ){
			Last[j]=Next[j];
			Next[j]=0;
		}
	}

	for( i=1; i<=m; ++i, mx++ ){
		for( j=1; j<=mx; ++j ){
			Next[j] += Last[j-1];
			mod( Next[j] );
			Next[j] += Last[j]*(j-1);
			Next[j] %= Mod;
		}
		for( j=1; j<=mx; ++j ){
			Last[j]=Next[j];
			Next[j]=0;
		}
	}
	int sum=0;
	for( i=1; i<=mx; ++i ){
		sum += Last[i];
		while( sum >= Mod )
			sum -= Mod;
	}
	printf("%d\n", sum );
	return 0;
}
