#include <cstdio>
#include <iostream>
using namespace std;

#define max_n 1<<22

int Rez[ max_n ], Bfs[ max_n ],st,dr, Pow[30];
int i,l,j,act,n;


int main(){
 	freopen("coins.in","r",stdin);
	freopen("coins.out","w",stdout);

	for( i=0; i<=22; ++i ){
		Pow[ i ] = (1<<i);
	}
	for( i=1; i<=22; ++i ){
		Rez[ Pow[i]-1 ] = 1;
	}
    for( i=1; i<(1<<22); ++i ){
		// luam bitii normal
		if( !Rez[ i ] ){
			l=0;
			while( i&(Pow[l]) )
				++l;
			for( j=0; j<22; ++j ){
				if( !( i&(Pow[j]) ) )
					l=j+1;
				else{
					while( i&(Pow[l]) )
						++l;
					if( l<22 ){
						Rez[ i^(Pow[l])^(Pow[j]) ] = 1;
					}
				}
			}
		}
	}

	int n,x,nr,r=0,act;
    scanf("%d", &n );
	for( i=1; i<=n; ++i ){
		act=0;
		nr=0;
		for( l=0; l<22; ++l ){
			scanf("%d", &x );
			if( x ){
				act^=(1<<l);
				nr++;
			}
		}
		if( Rez[ act ] )
			r+=nr;
	}                
	printf("%d\n",r);
	return 0;
}
