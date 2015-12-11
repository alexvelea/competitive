#include <cstdio>
#include <algorithm>
using namespace std;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define INF 0x3f3f3f3f
#define max_n 105

struct triplet{
	int a,b,c;
	triplet(){
		a=b=c=0;
	}
	triplet( int _a, int _b, int _c ){
		a=_a;
		b=_b;
		c=_c;
	}
} Parent[max_n][max_n];
int i,n,target;
pair<int,int> El[max_n],Rez[max_n];

bool solve( int timp ){
	int Best[105],BestNou[105];
	int i,j,l,o;
	for( i=0; i<=target; ++i ){
		Best[i]=-1;
		BestNou[i]=-1;
	}
	Best[0]=0;
	for( i=1; i<=n; ++i ){
 		for( j=0; j*El[i].fi <= timp; ++j ){
			l = (timp-j*El[i].fi)/El[i].se;
            for( o=0; o+j<=target; ++o ){
				if( Best[o] != -1 && ( Best[o+j] < min(l+Best[o],target) ) && ( BestNou[o+j] < min(target,l+Best[o]) ) ){
					BestNou[o+j]=Best[o]+l;
					if( BestNou[o+j] > target ){
						BestNou[o+j]=target;
					}
					Parent[o+j][ BestNou[o+j] ] = triplet(o,Best[o],i);
				}
			}
		}
		for( j=0; j<=target; ++j ){
			Best[j]=max(Best[j],BestNou[j]);
			BestNou[j]=-1;
		}
	}
	if( Best[target] == target )
		return 1;
	return 0;
}

int main(){
	freopen("lapte.in","r",stdin);
	freopen("lapte.out","w",stdout);
	scanf("%d %d", &n, &target );
	for( i=1; i<=n; ++i ){
		scanf("%d %d", &El[i].fi, &El[i].se );
	}
	int t,p;
	t=0;
	p=64;
	for( ; p; p>>=1 ){
		if( !solve( t+p ) )
			t+=p;
	}
	t++;
 	solve( t );
	
	int a,b;
	a=target;
	b=target;

	while( a!=0 || b!=0 ){
		Rez[ Parent[a][b].c ]=mp( a-Parent[a][b].a, b-Parent[a][b].b );
		int c,d;
		c=a;
		d=b;
		a=Parent[c][d].a;
		b=Parent[c][d].b;
	}
	printf("%d\n",t);	
	for( i=1; i<=n; ++i )
		printf("%d %d\n",Rez[i].fi,Rez[i].se);
	return 0;
}
