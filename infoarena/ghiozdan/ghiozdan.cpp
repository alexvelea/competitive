#include<cstdio>

#include <algorithm>

using namespace std;

#define max_g 75005
#define fi first
#define se second
#define th third
#define fo forth

struct trio {
	int first,second,third,forth;
	trio(){
		first=second=third=forth=0;
	}
	trio( int a, int b, int c, int d ){
 		first=a;
		second=b;
		third=c;
		forth=d;
	}
} Deq[ max_g ];

int Ap[ 205 ],n,g,i,a;
int st,dr, Min[ max_g ], From[ max_g ];

void read( ){
	freopen("ghiozdan.in","r",stdin);
	freopen("ghiozdan.out","w",stdout);
	scanf("%d %d", &n, &g );
	for ( i=1; i<=n; ++i ){
		scanf("%d", &a );
		++Ap[ a ];
	}
}
void getmin( int &a, int b ){
	if( b < a )
		a=b;
	if( a == 0 )
		a=b;
}

void solve( int c1, int c2, int g ){
	// scriem suma g din valorile de la st la dr inclusiv
    int d,r,st,dr,ind,step,target=(c1+c2)/2,i,f;

	for( i=0; i<=g; ++i )
		From[ i ] = i, Min[ i ] = 0;
	Min[ 0 ] = 1;
	for( d=c1; d<=c2; ++d ){
 		if( Ap[ d ] ){
			for( r=0; r<d; ++r ){
				st=dr=1;
				dr=0;
				ind=r+d;
				step=1;
				Deq[ 1 ] = trio();
				if( Min[ r ] )
					Deq[ ++dr ]=trio( r, 0, Min[ r ], From[ r ] );
				for( ; ind<=g; ind+=d,++step ){
					if( Deq[ st ].se + Ap[ d ] < step ){
						st++;
					}
					if( Min[ ind ] ){
						// scoatem din stiva cat putem.
						while( st<=dr && Min[ ind ] <= Min[ Deq[ dr ].fi ] + ( step - Deq[ dr ].se ) )
							--dr;
						Deq[ ++dr ] = trio( ind, step, Min[ ind ], From[ ind ] );
					}
					if( st <= dr ){
						if( Min[ ind ] == 0 || Min[ ind ] > step - Deq[ st ].se + Deq[ st ].th ){
							Min[ ind ] = step - Deq[ st ].se + Deq[ st ].th;
							if( d > target ){
								From[ ind ] = Deq[ st ].fo;
							}
						}
					}
				}
			}
		}
	}
	if( c1 == c2 ){
		for( i=g; i; --i ){
			if( Min[ i ] ){
				f=i;
				while( f ){
					printf("%d\n",c1);
					f-=c1;
				}
				return ;
			}
		}
	}
	for( i=g; i; --i ){
		if( Min[ i ] ){
			if( c1 == 1 && c2 == 200 ){
				printf("%d %d\n",i,Min[i]-1);
			}
			f=From[ i ];
            solve( c1, target, f);
			solve( target+1, c2, i-f);
			return ;
		}
	}
}

int main(){
	read();
	solve( 1, 200, g );
	return 0;
}
