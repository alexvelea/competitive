#include <cstdio>
using namespace std;

int El[1001][1001],i,j,nr,k,n,p;
bool Viz[10000005];

int main(){
	freopen("tablete.in","r",stdin);
	freopen("tablete.out","w",stdout);
	scanf("%d %d", &n, &k );
	nr=1;
	for( j=1; j<k-1; ++j ){
		for( i=1; i<=n; ++i ){
			Viz[ nr ] = 1;
			El[i][j]=nr++;

		}
	}
	// completam coloanele k-1,k
	if( nr&1 ){
 		for( i=1; i<=n; ++i ){
			for( j=k-1; j<=k; ++j ){
				while( Viz[ nr ] )
					nr++;
				Viz[ nr ] = 1;
				El[i][j]=nr++;
			}
		}
		for( j=k+1; j<=n; ++j ){
			for( i=1; i<=n; ++i ){
				while( Viz[ nr ] )
					nr++;
				Viz[ nr ] = 1;
				El[i][j]=nr++;
			}
		} 
	}else{
		Viz[ nr ] = 1;
		El[ 1 ][ k-1 ] = nr;
		j=k;
		p=nr+2;
		for( i=1; i<=n; ++i ){
			Viz[ p ] = 1;
			El[ i ][ k ] = p;
			p+=2;
		}
		j=k-1;
		for( i=2; i<=n; ++i ){
			while( Viz[ nr ] )
				nr++;
			El[ i ][ j ] = nr;
			Viz[ nr++ ] = 1;
		}
		for( i=1; i<=n; ++i ){
			for( j=k+1; j<=n; ++j ){
				while( Viz[ nr ] )
					nr++;
				El[i][j]=nr;
				Viz[nr++]=1;
			}
		}
	}

	for( i=1; i<=n; ++i ){
		for( j=1; j<=n; ++j )
			printf("%d ",El[i][j]);
		printf("\n");
	}
	return 0;
}
