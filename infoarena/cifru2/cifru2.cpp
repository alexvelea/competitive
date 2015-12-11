#include <cstdio>
#include <cassert>
using namespace std;

	#define max_n 200005
	#define max_m 10005

int Coded[ max_n ], UnCoded[ max_n ];
int CodedSpace[ max_n ], UnCodedSpace[ max_n ];
int i,n,m,Pi[max_n];



void MakeSpacing ( int From[], int *Dest ){
	int i=0;
	int First[ max_m ],Last[ max_m ];
	for ( i=0; i<=m; ++i ){
		First[ i ] = Last[ i ] = 0;
	}
	for ( i=1; i<=n; ++i ){
		if ( !First[ From[ i ] ] ){
			First[ From[ i ] ] = i ;
		}
		if ( Last[ From[ i ] ] ){
			*( Dest+Last[ From[ i ] ] )  = i - Last[ From[ i ] ];
		}
		Last[ From[ i ] ] = i;
	}
	for ( i=1; i<=m; ++i ){
		*( Dest+Last[i] ) = n - Last[ i ] + First[ i ];
	}
	return ;
}

void write ( int d ){
	printf("%d\n", d );
	int Res[ max_m ];
	for ( i=1; i<=n; ++i ){
		Res[ UnCoded[ i ] ] = Coded[ i+d ];
	}
	for ( i=1; i<=m; ++i ){
		printf("%d ", Res[ i ] );
	}
	return ;
}

void prefix (){
	int k=0;
	for ( int i=2; i<=n; ++i ){
		while ( k && UnCodedSpace[ k+1 ] != UnCodedSpace[ i ] )
			k = Pi[ k ];
		if ( UnCodedSpace[ k+1 ] == UnCodedSpace[ i ] )
			k++;
		Pi[ i ] = k;
	}
	return ;
}

int main(){

	freopen ("cifru2.in","r",stdin);
	freopen ("cifru2.out","w",stdout);

	scanf ("%d %d", &n , &m );
	for ( i=1; i<=n; ++i ){                    
		scanf ("%d", &UnCoded[ i ] );
	}
	for ( i=1; i<=n; ++i ){
		scanf ("%d", &Coded[ i ] );
	}
	MakeSpacing ( UnCoded, &UnCodedSpace[0] );
	MakeSpacing ( Coded, &CodedSpace[0] );
 	for ( i=1; i<=n; ++i ){
		CodedSpace[ i+n ] = CodedSpace[ i ];
		Coded[ i+n ] = Coded[ i ];
	}
	
	// debug
/*	for ( i=1; i<=n; ++i ){
		printf("%d ", UnCodedSpace[ i ]);
	}
	printf("\n");
	for ( i=1; i<=2*n; ++i ){
		printf("%d ",CodedSpace[ i ]);
	}
	printf("\n");*/

	prefix();

/*    for ( i=1; i<=n; ++i ){
		printf("%d ", Pi[i] );
	}*/

	int k=0;
	for ( i=1; i<=2*n; ++i ){
		while ( k && UnCodedSpace[ k+1 ] != CodedSpace[ i ] )
			k = Pi[ k ];
		if ( UnCodedSpace[ k+1 ] == CodedSpace[ i ] )
			++k;
		if ( k == n ){
			write ( i-n );
			return 0;
		}
	}
	assert(0);
	return 0;
}
