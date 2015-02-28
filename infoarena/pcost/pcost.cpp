#include <cstdio>
#include <vector>
using namespace std;
 
#define max_n 1000005
#define pb push_back
 
int Nr[ max_n ];
bool V[ 2005 ];
 
int i,j,d,c,x,n;
long long rez;
vector<int> Div;
 
void update( int val ){
    rez+=1LL*Nr[val]*val*val;
    Nr[val]++;
}
 
int main(){
    freopen("pcost.in","r",stdin);
    freopen("pcost.out","w",stdout);
    for( i=2; i<=1000; ++i ){
        if( !V[i] ){
            Div.pb(i);
            for( j=i*i; j<=1000; j+=i ){
                V[j]=1;
            }
        }
    }
    scanf("%d", &n );
    for( i=1; i<=n; ++i ){
        scanf("%d", &x );
        c = x;
        d=0;
        while ( d<Div.size() && c!=1 && Div[d]*Div[d] <= x ){
            if( c%Div[d] == 0 ){
                update( Div[d] );
                while( c%Div[d]== 0 )
                    c/=Div[d];
            }
            d++;
        }
        if( c != 1 )
            update( c );
    }
    printf("%lld\n",rez);
    return 0;
}
