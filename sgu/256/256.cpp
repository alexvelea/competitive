#include <cstdio>
#include <algorithm>
using namespace std;

	int i,n,k;
	int Viz[500000];
	int P[500000];
	int prim,ultim;
	int Ti[30],sum,Ti2[30];

	class vol {
		public:
			int a,b;
	} T[20];
	struct bfs {
		int val,t;
	} B[500000];

	bool mysort ( vol g, vol h ){
		if ( g.a == h.a )
			return g.b < h.b;
		return g.a > h.a;
	}

	int min ( int a, int b ){
		if ( a < b )
			return a;
		return b;
	}

void roll_back ( int as ){
	int i,aux=B[prim].val;
	for ( i=5; i>0; i-- ){
    	Ti[i]=aux%5;
		aux/=5;
	}
	if ( as ){
		printf("%d\t",aux);
		for ( i=1; i<=5; i++ ){
			printf("%d\t",Ti[i]);
		}
		printf("\n");
	}
	sum=aux;

}
void roll_over ( int nr ){
	int aux=0,i;
	aux= sum+T[nr].a;
	for ( i=1; i<=5; i++ ){
		Ti2[i]=Ti[i];
		Ti[i]--;
		if ( Ti[i] == -1 )
			Ti[i]=0;
	}
	Ti[ nr ]=T[nr].b;
	for ( i=1; i<=5; i++ ){
		aux*=5;
		aux+=Ti[i];
	}
	if ( !Viz[ aux ] ){
		ultim++;
		Viz[aux]=1;
		B[ultim].val=aux;
		B[ultim].t=B[prim].t+1;
		P[aux]=B[prim].val;
	}
/*	printf("%d\t",sum+T[nr].a);
	for ( i=1; i<=5; i++ ){
		printf("%d\t",Ti[i]);
	}
	printf("\n"); */
	for ( i=1; i<=5; i++ )
		Ti[i]=Ti2[i];
}

int main(){
	scanf ("%d %d", &k, &n );
	for ( i=1; i<=n; i++ ){
		scanf ("%d %d", &T[i].a, &T[i].b );
	}
	sort ( T+1, T+n+1, mysort );
	n = min(n,5);
	
    Viz[0]=1;
	B[0].val=0;
	B[0].t=0;
	while ( prim <= ultim ){
		roll_back(0);
		if ( sum >= k ){
			printf("%d\n", B[prim].t);
			return 0;
		} 
		roll_over(0);
		for ( i=1; i<=n; i++ ){
			if ( !Ti[i] ){
				roll_over(i);
			}
		}
		prim++;
	}

	return 0;
}
