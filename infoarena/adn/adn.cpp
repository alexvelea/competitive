#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>
using namespace std;

	#define max_l 30005
	#define max_n 20

int Cost[ max_n ][ max_n ];
int Prefix[ max_n ][ max_l ];
char Text[ max_n ][ max_l ];
bool Erase[ max_n ];
int Lenght[ max_n ];

int Best[ (1<<18) +1 ][ 18 ];
int From[ (1<<18) * 18 + 100 ];

int last,first;
int Bfs[ (1<<18) * 18 + 100 ];

int n,i,j,l;


void prefix ( int ind ){
    int k=0;
	for ( int i=2; i< Lenght[ ind ]; ++i ){
    	while ( k && Text[ ind ][ k+1 ] != Text[ ind ][ i ] ){
			k = Prefix[ ind ][ k ];
		}
		if ( Text[ ind ][ k+1 ] == Text[ ind ][ i ] )
			++k;
		Prefix[ ind ][ i ] = k;
	}
}

int main(){

    freopen ("adn.in","r",stdin);
 	freopen ("adn.out","w",stdout);

	scanf ("%d", &n );
	for ( i=0; i<n; ++i ){
		scanf ("%s", Text[i]+1 );
        for ( Lenght[ i ]=1; Text[ i ][ Lenght[ i ] ] != 0; ++Lenght[ i ] )
			;
	}

	for ( i=0; i<n; ++i ){
		prefix( i );
	}
	
	// facem distantele.
	for ( i=0; i<n; ++i ){
		if ( !Erase[ i ] )
		for ( j=0; j<n; ++j ){
			if ( !Erase[ j ] && i != j ){

                int k=0;
				for ( l=1; l< Lenght[ i ]; ++l ){
					while ( k && Text[ i ][ l ] != Text[ j ][ k+1 ] )
						k = Prefix[ j ][ k ];
					if ( Text[ i ][ l ] == Text[ j ][ k+1 ] )
						++k;
					if ( k == Lenght[ j ] - 1 ){
						Erase[ j ] = 1;
						k = Prefix[ j ][ Lenght[ j ] -1 ];
					}
				}
				if ( Erase[ j ] )
					Cost[ i ][ j ] = Lenght[ j ] -1 ;
				else
					Cost[ i ][ j ] = k;

			}
		}
	}
	int start=0;
	for ( i=0; i<n; ++i ){
		start |= ( Erase[ i ] <<(i) );
	}
	Best[ 0 ][ 0 ] = 1;
	for ( i=0; i<n; ++i ){
		if ( !Erase[ i ] ){
        	Bfs[ ++last ] = ( ( start | (1<<i) )<<5 ) + i;
			Best[ start | ( 1<<i ) ][ i ] = 1;
		}
	}
	first=1;
	while ( first <= last ){

        int nod, stare;
		nod = Bfs[ first ] & ( ( 1<<5 ) - 1 );
		stare = Bfs[ first ] >> 5;

		for ( i=0; i<n; ++i ){
			if ( !( (1<<i) & stare ) ) {
				int stare_n = stare | (1<<i);
				if ( !Best[ stare_n ][ i ] ){
					Best[ stare_n ][ i ] = Best[ stare ][ nod ] + Cost[ nod ][ i ];
					From[ (stare_n << 5) + i ] = Bfs[ first ];
					Bfs[ ++last ] = ( ( stare_n ) << 5 ) + i;
				}
				else{
					if ( Best[ stare_n ][ i ] < Best[ stare ][ nod ] + Cost[ nod ][ i ] ){
 						Best[ stare_n ][ i ] = Best[ stare ][ nod ] + Cost[ nod ][ i ];
						From[ ( stare_n << 5 ) + i ] = Bfs[ first ];                   	
					}
				}
			}
		}
		++first;
	}
	int act = ( ( 1<<n )-1 ) << 5; 
	for ( i=0; i<n; ++i ){
		if ( !Erase [ i ] ){
			if ( Best[ act>>5 ][ act&( (1<<5)-1 ) ] < Best[ ( 1<<n ) -1 ][ i ] )
				act= ( ( (1<<n)-1)<<5 ) + i; 
		}
	}
	int Rez[20][2];
	i=0;
	while ( act ){
		int father = From[ act ];
		i++;
		Rez[ i ][ 0 ] = act&((1<<5)-1);
		Rez[ i ][ 1 ] = 1+Best[ act>>5 ][ act&(31) ] - Best[ father>>5 ][ father&(31) ];
		act=father;
	}
	for ( ; i; --i ){
		for ( j=Rez[i][1]; j< Lenght[ Rez[i][0] ]; ++j )
			printf("%c", Text[ Rez[i][0] ][ j ] );
	}
	return 0;
}
