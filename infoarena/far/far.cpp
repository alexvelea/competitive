#include <cstdio>
#include <vector>
using namespace std;

#define max_p 2000000000
#define pb push_back
bool V[ 100000 ];
vector<int> Div;
int n,m,p,c,ok,d,i,t,j;

int calc( int a, int b ){
	long long i;
	int rez=0;
	for( i=b; 1LL*i<=1LL*a; i=1LL*i*b )
		rez+= a/i;
	return rez;
}

bool check( int val ){
	if( calc( n,val ) + calc( m,val) == calc( n+m,val) )
		return 0;
	return 1;
}

int main(){
 	freopen("far.in","r",stdin);
	freopen("far.out","w",stdout);
    // facem ciur
	for( i=2; i*i < max_p; ++i ){
		if( !V[ i ] ){
			Div.pb(i);
			for( j=i*i; 1LL*j*j < 1LL*max_p; j+=i )
				V[j]=1;
		}
	}

	scanf("%d", &t );
	for( ; t; --t ){
		scanf("%d %d %d", &n, &m, &p );
        n--;
		m--;
		c=p;
		d=0;
		ok=1;
		while( 1LL*Div[d]*Div[d] <= 1LL*c && c!=1 ){
			if( c%Div[d]==0 ){
            	if ( ok )
					ok = check( Div[d] );
				while( c%Div[d] == 0 )
					c/=Div[d];
			}
			d++;
		}
		if( c!=1 && ok )
			ok = check( c );
		printf("%d\n",ok);
	}
	return 0;
}
