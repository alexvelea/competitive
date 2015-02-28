#include <cstdio>

#include <algorithm>
#include <vector>

using namespace std;

	#define max_n 1000005

int n,a,b,c;
int i,j;
char Buffer[ max_n ];
int first=0;

int Color[ max_n ], Next[ max_n ];


void insert_char ( char c ){
	Buffer[ first++ ] = c;
	if ( first == max_n-2 ){
		Buffer[ first ] = '\0';
		printf("%s", Buffer );
		first=0;
	}
	Buffer[ first ] = '\0';
}

void insert_number ( int  val ){
	int i=0,T[20];
	do{
		T[ ++i ] = val%10;
		val/=10;
	} while ( val );
	for ( ; i; i-- )
		insert_char ( char ( T[i]+'0' ) );
}

struct triplet {
	int a,b,c;
	triplet ( int x, int y, int z ){
		a=x;
		b=y;
		c=z;
	}
} ;
vector <triplet> Plank;

int main(){

	freopen ("curcubeu.in","r",stdin);
	freopen ("curcubeu.out","w",stdout);

    scanf ("%d%d%d%d", &n, &a, &b, &c );
	n--;
	Plank.push_back( triplet ( a,b,c ) );
	for ( i=2; i<=n; ++i ){
		Plank.push_back( 
			triplet( 
				( 1LL*Plank.back().a * i )%( n+1 ), 
				( 1LL*Plank.back().b * i )%( n+1 ), 
				( 1LL*Plank.back().c * i )%( n+1 ) 
			) );
	}
	for ( i=Plank.size()-1; i>=0; --i ){
		if ( Plank[ i ].a > Plank[ i ].b ){
			swap ( Plank[ i ].a , Plank[ i ].b );
		}
		for ( j = Plank[ i ].a; j<= Plank[ i ].b; ){
            if ( !Color[ j ] ){
				Color[ j ] = Plank[ i ].c;
				Next[ j ] = Plank[ i ].b+1;
				++j;
			}
			else{
				int aux = Next[ j ];
				if ( Next[ j ] < Plank[ i ].b+1 ){
					Next[ j ] = Plank[ i ].b+1;
				}
				j = aux;
			}
		}
	}
	for ( i=1; i<=n; ++i ){
		insert_number( Color[i] );
		insert_char ( '\n' );
	}
	printf("%s",Buffer);
	return 0;
}
