#include <cstdio>
using namespace std;

	#define max_n 1005

bool El[ max_n ][ max_n ];
int Down[ max_n ][ max_n ], Up[ max_n ][ max_n ];

int n,m,i,j;
int rez;
int StUp[ max_n ], StDown[ max_n ], DrUp[ max_n ], DrDown[ max_n ];
int last, Deq[ max_n ];

int main(){

	freopen ("dreptunghiuri5.in","r",stdin);
	freopen ("dreptunghiuri5.out","w",stdout);

	scanf ("%d %d", &n, &m );
	for ( i=1; i<=n; ++i ){
		for ( j=1; j<=m; ++j ){
			scanf ("%d", &El[ i ][ j ]);
		}
	}
/*	for ( i=1; i<=n; ++i ){
	printf("\n");
		for ( j=1; j<=m; ++j ){
			printf("%d",El[i][j]);
		}
	}
	printf("\n\n\n");*/
	for ( i=1; i<=n; ++i ){
		for ( j=1; j<=m; ++j ){
			if ( !El[ i ][ j ] ){
				Up[ i ][ j ] = Up[ i-1 ][ j ] + 1;
			}
		}
	}
	for ( i=n; i; --i ){
		for ( j=1; j<=m; ++j ){
			if ( !El[ i ][ j ] ){
				Down[ i ][ j ] = Down[ i+1 ][ j ] + 1;
			}
		}
	}
/*	for ( i=1; i<=n; ++i )
	{
		printf("\n");
		for ( j=1; j<=m; ++j ){
			printf("%d ",Down[i][j]);
		}
	}*/
	for ( i=1; i<=n; ++i ){
//		printf("%d\n",rez);
		// facem valorile
		// cat de mult putem merge la stanga ca h-ul nostru sa fie minim
		int poz;
		last=0;
		Deq[ 0 ] = 0;
		for ( j=1; j<=m; ++j ){
			bool ok=1;
			while ( last && Up[ i ][ j ] <= Up[ i ][ Deq[ last ] ] ){
				if ( Up[ i ][ j ] == Up[ i ][ Deq[ last ] ] )
					ok=0;
				last--;
			}
			if ( ok ){
				StUp[ j ] = j - Deq[ last ];
			}
			else{
				StUp[ j ] = 0;
			}
			Deq[ ++last ] = j;
		}
		// cat de mult putem merge la dreapta ca h-ul nostru sa fie minim
		last=0;
		Deq[ 0 ] = m+1;
		for( j=m; j; --j ){
			while ( last && Up[ i ][ j ] <= Up[ i ][ Deq[ last ] ] ){
				last--;
			}
			DrUp[ j ] = Deq[ last ] - j;
			Deq[ ++last ] = j; 
		}

		// care e primul '1' care il intalnim daca mergem la stanga :)
		poz=-1;
		for ( j=1; j<=m; ++j ){
			if ( Down[ i ][ j ] <= 1 )
				poz = j;
			StDown[ j ] = j-poz;
		}
		poz=n+2;
		// care e primul '1' care il intalnim daca mergem la dreapta
		for ( j=m; j>=1; --j ){
			if ( Down[ i ][ j ] <= 1 )
				poz=j;
            DrDown[ j ] = poz-j;
		}

		// verificam fiecare punct
/*		for ( j=1; j<=m; ++j ){
			printf("%d ",StUp[j]);
		}
		printf("\n");
		for ( j=1; j<=m; ++j ){
			printf("%d ",DrUp[j]);
		}
		printf("\n");
		printf("-------\n");
 		for ( j=1; j<=m; ++j ){
			printf("%d ",StDown[j]);
		}
		printf("\n");
		for ( j=1; j<=m; ++j ){
			printf("%d ",DrDown[j]);
		}
		printf("\n");*/
		for ( j=1; j<=m; ++j ){
			if ( !El[ i ][ j ] ){
//				printf("%d @ \t%d\t%d\t%d\t%d\n",j,StUp[j],DrUp[j],StDown[j],DrDown[j]);
	            int ok=0;
	 			if ( StUp[ j ] > StDown[ j ] )
					ok=1;
				if ( DrUp[ j ] > DrDown[ j ] )
					ok=1;
				if ( !StUp[ j ] )
					ok=0;
				rez+=ok;
			}
		}
	}
	printf("%d\n", rez);
	return 0;
}
