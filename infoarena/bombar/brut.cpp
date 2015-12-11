#include <cstdio>
#include <cassert>
#include <algorithm>
#include <iostream>
using namespace std;

#define sigma 100000000
#define max_cif 2000

struct nrmare{
    int El[max_cif],nrcif;
    nrmare(){
        for( int i=0; i<max_cif; ++i ){
            El[i]=0;
        }
        nrcif=0;
    }
    nrmare( int _el){
        El[0]=_el;
        nrcif=1;
        for( int i=1; i<max_cif; ++i ){
            El[i]=0;
        }
    }
    void afisare(){
        int i,j,x,Cif[10];
        for( i=nrcif-1; i>=0; --i ){
            if( i==nrcif-1 ){
                printf("%d",El[i]);
            }else{
                assert(El[i]<sigma);
                x=El[i];
                for( j=0; j<8; ++j )
                    Cif[j]=0;
                j=0;
                while( x ){
                    Cif[j++]=x%10;
                    x/=10;
                }
                for( j=7; j>=0; --j )
                    printf("%d",Cif[j]);
            }
        }
        printf("\n");
    }
} N[2];

void add( int ind, int exp ){
    int t=0,i;
    for(   i=0; i<max(N[ind].nrcif,N[ind^1].nrcif); ++i ){
        if( exp == 1 )
            N[ind].El[i]=N[ind].El[i]+N[ind^1].El[i]+t;
        else
            N[ind].El[i]=N[ind].El[i]+(N[ind^1].El[i]<<1)+t;
        t=0;
        while( N[ind].El[i]>=sigma ){
            N[ind].El[i]-=sigma;
            t++;
        }
    }
    N[ind].nrcif=max(N[ind].nrcif,N[ind^1].nrcif);
    if( t ){
        N[ind].El[ N[ind].nrcif ]=t;
        N[ind].nrcif++;
    }
}

int main(){
    
    freopen("bombar.in","r",stdin);
    freopen("bombar.out","w",stdout);
    
    int T;
    scanf("%d", &T );
    N[0]=N[1]=nrmare(1);
    T--;
    while( T ){
        add( 1, 2 );
        add( 0, 1 );
        T--;
    }
    N[0].afisare();
    return 0;
}
