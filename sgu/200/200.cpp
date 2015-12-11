#include <cstdio>
#include <utility>
#include <iostream>
using namespace std;

    int i,j,V[1000],n,t,nr_p,Prime[300],a,nr,rez,k,Cif[100],nrcif;
    struct gauss{
        bool el[105];
    } Gauss[105];

int main(){
    scanf ("%d %d", &t, &n );
    for ( i=2; i<=30; i++ ){
        if ( !V[i] ){
            for ( j=i*i; j<=900; j+=i ){
                V[j]=1;
            }
        }
    }
    for ( i=2; i<=900; i++ ){
        if ( !V[i] ){
            Prime [++nr_p] = i;
        }
    }
    for ( i=1; i<=n; i++ ){
        scanf ("%d", &a);
        for ( j=1; j<=100 && a>1 ; j++ ){
            while ( a% Prime[j] == 0 ){
                a/=Prime[j];
                Gauss[j].el[i]^=1;
            }
        }
    }
    // facem GAUSS 
    int l,c;
    rez=n;
    for ( l=1; l<=t; l++ ){
        // cautam coloana libera :()()()()()()
        for ( c=1; c<=n && !Gauss[l].el[c]; c++ ) ;
        if ( c>n )
            continue;
        for ( i=l+1; i<=t; i++ ){
            if ( Gauss[i].el[c] )
                for ( k=1; k<=n; k++ )
                    Gauss[i].el[k]^=Gauss[l].el[k];
        }
        rez--;        
    }
    
    nrcif=1;
    Cif[1]=1;
    for ( i=1; i<=rez; i++ ){
        int t=0;
        j=0;
        for ( j=1; j<=nrcif || t; j++ ){
            Cif[j]*=2;
            Cif[j]+=t;
            t=Cif[j]/10;
            Cif[j]%=10;
        }
        nrcif=j-1;
    }
    Cif[1]--;
    i=1;
    while ( Cif[i] < 0 ){
        Cif[i]+=10;
        Cif[i+1]--;
        i++;
    }
    for ( j=nrcif; j>=1; j-- )
        printf("%d", Cif[j]);
    return 0;
}
