#include <cstdio>
#include <cstring>
 
#include <algorithm>
#include <iostream>
#include <vector>
 
using namespace std;
 
#define Sigma 31
#define max_l 500005
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
 
const int Mod[2]={ 666013, (1<<23) };
vector< int > Hash[ 666013 ];
 
bool viz[ 50 ];
int re=0;
char T[2][ 2*max_l ];
int PowSigma[ 2*max_l ][ 2 ], InvPowSigma[ 2*max_l ][ 2 ], Rez[ 2*max_l ], PartialProd[ 2*max_l ][2];
 
int pow( int val, int p, int mod ){
    int rez=1;
    while( p ){
        if( p&1 )
            rez = ( 1LL*rez*val ) % mod;
        val = ( 1LL*val*val ) % mod;
        p>>=1;
    }
    return rez;
}
 
void init( int val ){
    int l,i;
    for( l=0; l<2; ++l ){
        PowSigma[ 0 ][ l ] = 1;
        for( i=1; i<=val; ++i ){
            PowSigma[ i ][ l ] = (PowSigma[ i-1 ][ l ]*Sigma)%Mod[l];
        }
        InvPowSigma[ val ][ l ] = pow( PowSigma[ val ][ l ], Mod[l]-2, Mod[l] );
        for( i=val-1; i>=1; --i ){
            InvPowSigma[ i ][ l ] = ( 1LL*Sigma*InvPowSigma[ i+1 ][ l ] ) % Mod[ l ] ;
        }
    }
}
 
bool FindHash( int ind, int v ){
    FORIT( it, Hash[ ind ] ){
        if( *it == v )
            return 1;
    }
    return 0;
}
void EraseHash( int val, int v ){
    int i=0;
    FORIT( it,Hash[ val ] ){
        if( *it == v ){
            Hash[ val ][ i ] = Hash[ val ][ Hash[ val ].size()-1 ];
            Hash[ val ].pop_back();
            return ;
        }
        i++;
    }
}
void InsertHash( int val, int v ){
    Hash[ val ].push_back( v );
}
 
void solve( int ind ){
    int last=0,i,l,st,dr,n,P[4];
    n=strlen(T[ind]);
    for( i=0; i<n; ++i ){
        if( ind == 0 ){
            viz[ T[ind][i]-'a' ]=1;
        }else{
            if( viz[ T[ind][i]-'a' ] ){
                re++;
                viz[ T[ind][i]-'a' ]=0;
            }
        }
    }
    for( i=2*n; i>=0; --i ){
        if( i&1 ){
            T[ ind ][ i ] = T[ ind ][ i>>1 ];
        }
        else{
            T[ ind ][ i ] = '|';
        }
    }
    n<<=1;
    for( l=0; l<2; ++l ){
        PartialProd[ 0 ][ l ] = T[ ind ][ 0 ] - 'a' + 1;
        for( i=1; i<=n; ++i ){
            PartialProd[ i ][ l ] = ( ( 1LL*( T[ ind ][ i ] - 'a' + 1 ) * PowSigma[ i ][ l ] ) % Mod[l] + PartialProd[ i-1 ][ l ] ) % Mod[ l ];
        }
    }
    for( i=0; i<=n; ++i )
        Rez[ i ] = 0;
    for( i=0; i<=n; ++i ){
        if( last+Rez[last] >= i ){
            Rez[ i ] = min( Rez[ 2*last-i ], last+Rez[last]-i );
        }
        while( ( i+Rez[i]+1 <= n )
            && ( i-Rez[i]-1 >= 0 )
            && ( T[ ind ][ i+Rez[i]+1 ] == T[ ind ][ i-Rez[i]-1 ] ) ){
            Rez[i]++;
            if( T[ ind ][ i+Rez[i] ] != '|' ){
                st=i-Rez[i]-1;
                dr=i+Rez[i];
                for( l=0; l<2; ++l ){
                    P[l]=PartialProd[ dr ][ l ];
                    if( st >= 0 ){
                        P[l]-=PartialProd[ st ][ l ];
                    }
                    if( P[l] < 0 ){
                        P[l]+=Mod[l];
                    }
                    P[l]=(1LL*P[l]*InvPowSigma[ st+1 ][ l ])%Mod[ l ];
                }
                if( FindHash( P[0], P[1]) ){
                    if( ind == 0 )
                        ;
                    else{
                        EraseHash( P[0], P[1] );
                        re++;
                    }
                }
                else{
                    if( ind == 0 ){
                        InsertHash( P[0], P[1] );
                    }
                }
            }
        }
	if( Rez[i]+i > last+Rez[last] )
		last=i;
    }
}
 
int main(){
    freopen("unicat.in","r",stdin);
    freopen("unicat.out","w",stdout);
    scanf("%s",&T[0]);
    scanf("%s",&T[1]);
    init( 2*max( strlen(T[0]), strlen(T[1])) );
    solve(0);
    solve(1);
    printf("%d\n",re);
    return 0;
}
