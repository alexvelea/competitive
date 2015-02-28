#include <cstdio>

#include <algorithm>
#include <vector>

using namespace std;

	#define max_n 100005
	#define pb push_back

struct trio {
	int a,b,c;
	trio ( int x, int y, int z ){
		a=x;
		b=y;
		c=z;
	}
	trio (){
		a=b=c=0;
	}
} Segment[ max_n ];

vector<int> Normal;

int n,a,b,c;
int l,i,j;

int St[ 2*max_n ], Dr[ 2*max_n ];

bool mysort ( trio a, trio b ){
	return a.a < b.a;
}
bool mysort2 ( trio a, trio b ){
	return a.b > b.b;
}

int main(){

	freopen ("troll.in","r",stdin);
	freopen ("troll.out","w",stdout);

	scanf ("%d", &n );
	for ( i=1; i<=n; ++i ){
		scanf ("%d %d %d", &a, &b, &c );
		Normal.pb ( a );
		Normal.pb ( b );
		Segment[ i ] = trio ( a, b, c );
	}

	sort ( Normal.begin(), Normal.end() );
	Normal.resize( unique( Normal.begin(), Normal.end() ) - Normal.begin() );

	for ( i=1; i<=n; ++i ){
		Segment[ i ].a = lower_bound( Normal.begin(), Normal.end(), Segment[ i ].a ) - Normal.begin() +1;
		Segment[ i ].b = lower_bound( Normal.begin(), Normal.end(), Segment[ i ].b ) - Normal.begin() +1;
	}

/*  for ( i=1; i<=n; ++i ){
		printf("%d - %d\n",Segment[ i ].a, Segment[ i ].b );
	}*/

	sort ( Segment+1, Segment+n+1, mysort );
	for ( i=1,l=1; l <= Normal.size()+1; ++l ){
		St[ l ] = max ( St[ l ], St[ l-1 ] );
		while ( i<=n && Segment[ i ].a == l ){
        	St[ Segment[ i ].b ] = max ( St[ Segment[ i ].b ], 1+St[ l-1 ] );
			i++;
		}
	}	

	sort ( Segment+1, Segment+n+1, mysort2 );

	for ( i=1,l=Normal.size()+1; l>=0; --l ){
		Dr[ l ] = max ( Dr[ l ], Dr[ l+1 ] );
		while ( i<=n && Segment [ i ].b == l ){
			Dr[ Segment[ i ].a ] = max ( Dr[ Segment[ i ].a ], 1+Dr[ l+1 ] );
			i++;
		}
	}

	int mx=-1338;
	for ( i=1; i<=n; ++i ){
		if ( mx < Segment[ i ].c )
			mx = Segment[ i ].c;
	}
/*	for ( i=0; i<=Normal.size()+1; ++i ){
		printf("%d) - %d\n", i, St[ i ] );
	}
	printf("\n\n");
	for ( i=0; i<=Normal.size()+1; ++i ){
		printf("%d) - %d\n", i, Dr[ i ] );
	}                                     */
	int maxim=0;
	for ( i=1; i<=n; ++i ){
		if ( Segment[ i ].c == mx ){
			if ( maxim < St[ Segment[ i ].a -1 ] + Dr[ Segment[ i ].b +1 ] ){
				maxim = St[ Segment[ i ].a -1 ] + Dr[ Segment[ i ].b +1 ] ;
			}
		}
	}
	printf("%d %d\n",mx, maxim+1);
	return 0;
}
                          
