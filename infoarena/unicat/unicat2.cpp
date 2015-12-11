#include <fstream>
#include <cstring>
#include <algorithm>
#include <vector>
 
using namespace std;
 
ifstream in("unicat.in");
ofstream out("unicat.out");
#define max_n 500005
 
int Mod[3]={ 666019, 666023, 666031 };
int Mod10[ 2*max_n ][ 3 ], InvMod10[ 2*max_n ][ 3 ], Prod[ 2*max_n ][ 3 ], Rez[ 2*max_n ], It, P[3];
 
struct pal{
    int Val[ 3 ];
    bool operator<( const pal b ) const{
        if( b.Val[0] != Val[0] )
            return b.Val[0]<Val[0];
        if( b.Val[1] != Val[1] )
            return b.Val[1]<Val[1];
        return b.Val[2]<Val[2];
    }
    pal( int a, int b, int c ){
        Val[0]=a;
        Val[1]=b;
        Val[2]=c;
    }
    pal(){
        Val[0]=Val[1]=Val[2]=0;
    }
} ;
vector<pal> R[2];
char T[2][ 2*max_n ];
 
int pow( int a, int p, int MOD ){
    int rez=1;
    while( p ){
        if( p&1 ){
            rez= (1ll*a*rez)%MOD;
        }
        a=(1LL*a*a)%MOD;
        p>>=1;
    }
    return rez;
}
 
 
void solve( int ind ){
    int n;
    n=strlen(T[ind]);
    int last=0,i,j,l;
    for( i=2*n; i>=0; --i ){
        if( i&1 ){
            T[ind][i]=T[ind][ i>>1 ];
        }
        else{
            T[ind][i]='{';
        }
    }
    n<<=1;
 
    for( l=0; l<3; ++l ){
        Mod10[0][l]=1;
        for( i=1; i<=n; ++i ){
            Mod10[i][l]=(1LL*Mod10[i-1][l]*10)%Mod[l];
        }
    }
    // calculam inversele modulare
    for( l=0; l<3; ++l ){
        InvMod10[0][l]=1;
        for( i=1; i<=n; ++i ){
            InvMod10[i][l]=pow(Mod10[i][l],Mod[l]-2,Mod[l]);
        }
    }
 
    // calculam produsul de la 1 la n
    for( l=0; l<3; ++l ){
        for( i=1; i<=n; ++i ){
            Prod[ i ][l] = ( 1LL*Prod[ i-1 ][l] + 1LL*(T[ind][i]-'a'+1)*Mod10[i][l] )%Mod[l]; 
        }
    }
 
    for( i=0; i<=n; ++i ){
        if( Rez[ last ]+last >= i ){
            Rez[ i ] = min( Rez[ 2*last-i ], last+Rez[ last ]-i );
            It = Rez[ i ];
        }
		else{
			Rez[ i ] = 0;
			It = 0;
		}
        while( ( i-Rez[i]-1 >=0 )
            && ( i+Rez[i]+1<=n)
            && ( T[ind][ i+Rez[i]+1 ] == T[ind][ i-Rez[i]-1 ] ) )
            Rez[i]++;
        if( last+Rez[ last ] < i+Rez[i] ){
            last=i;
        }
        for( j=It; j<=Rez[i]; ++j ){
            if( T[ind][ i+j ] != '{' ){
                P[0]=P[1]=P[2]=0;
                for( l=0; l<3; ++l ){
                    if( i-j-1 >= 0 )
                        P[l]= Prod[ i+j ][l] - Prod[ i-j-1 ][l];
                    else
                        P[l]= Prod[ i+j ][l];
 
                    if( P[l] < 0 )
                        P[l]+=Mod[l];
                    if( i-j-1>=0 )
                        P[l]=(1LL*P[l]*InvMod10[i-j-1][l])%Mod[l];
                }
                R[ind].push_back( pal( P[0],P[1],P[2] ) );
            }
        }
    }
    return ;
}
 
int main(){
 
    in>>T[0];
    in>>T[1];
    solve(0);                            
    solve(1);
    sort( R[0].begin(), R[0].end() );
    sort( R[1].begin(), R[1].end() );
    int i=0,j=0,ok,k,rez=0;
    pal act;
    for( ; i<int(R[0].size()) && j<int(R[1].size()); ){
        if( R[0][i]<R[1][j] )
            act=R[0][i];
        else
            act=R[1][j];
        ok=1;
        k=0;
        while( i<int(R[0].size())
            && R[0][i].Val[0] == act.Val[0] 
            && R[0][i].Val[1] == act.Val[1]
            && R[0][i].Val[2] == act.Val[2] ){
                ++i;
                k=1;
            }
        if(!k) ok=0;
        k=0;
        while( j<int(R[1].size())
            && R[1][j].Val[0] == act.Val[0] 
            && R[1][j].Val[1] == act.Val[1] 
            && R[1][j].Val[2] == act.Val[2] ){
            ++j;
            k=1;
            }
        if( !k ) ok=0;
        if( ok )
            rez++;
    }
    out<<rez<<"\n";
    return 0;
}
