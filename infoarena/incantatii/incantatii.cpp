#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define max_n 1000005

char Text[ max_n ][ 10 ];
int Viz[ 200 ], El[ 50 ],nr;
int n,i,j;

vector <int> V;

int main(){

	freopen ("incantatii.in","r",stdin);
	freopen ("incantatii.out","w",stdout);

	scanf ("%d", &n );
	for ( i=1; i<=n; ++i ){
		scanf ("%s", &Text[ i ] );
		for ( j=0; Text[ i ][ j ] != '\0'; ++j ){
			Viz[ Text[ i ][ j ] - char ( 0 )] = 1;
		}
	}
	Viz[ '|' - char ( 0 ) ] = 1;
	for ( i=65; i<=127; ++i ){
 		if ( Viz[ i ] ){
			El[ ++nr ] = i;
            Viz[ i ] = nr;
		}
	}
	nr++;
	for ( i=1; i<=n; ++i ){
		int act = 0, j=0, x=0, o=0;
 		for ( ; Text[i][ j ] >= 'a'; ++j ){
			act*=nr;
			act+= Viz[ Text[i][ j ] - char ( 0 ) ];
			o++;
			x++;
		}
		for ( ; Text[i][ j ] <= 'Z'; ++j ){
			act*=nr;
			act+= Viz[ Text[i][ j ] - char ( 0 ) ];
			o++;		
		}
		for ( ; o<6; ++o ){
			act*=nr;
			act+= Viz[ '|' - char ( 0 ) ];   
		}
		V.push_back ( act );
	}
	sort ( V.begin(), V.end() );
	for ( i=0; i<n; ++i ){
		int E[ 7 ];
		int act = V[i];
		for ( j=6; j>=1; --j ){
			E[ j ] = act%nr;
			act/=nr;
		}
/*		for ( j=1; j<=6; ++j )
			printf("%d@\t",E[ j ]);
		printf("\n");*/
		for ( j=1; j<=6; ++j ){
			if ( E[j] != nr-1 )
				printf("%c",char ( El[ E[ j ] ] ) );
		}
		for ( j=3; j>=1; --j ){
			if (( E[j] != nr-1 ) && ( El[ E[j] ]>='a' ) ) 
				printf("%c", char ( El[ E[ j ] ] ) );
		}
		printf("\n");
	}
	return 0;
}
