#include <cstdio>
using namespace std;

    #define max_n 505
    #define mod 123457
    int Rez[max_n][max_n];
    
    int n,k,i,j;

int main(){
/*
    freopen ("mugur.in","r",stdin);
    freopen ("mugur.out","w",stdout);
*/
    scanf ("%d %d", &n, &k );
    Rez[0][0]=1;
    for ( i=0; i<=n; i++ ){
        if ( i>0 ){
            Rez[i][i]=Rez[i-1][i];
        }
        for ( j=i+1; j<=n; j++ ){
            if ( i > 0 ){
                Rez[i][j]+=Rez[i-1][j];
            }
            Rez[i][j]+=Rez[i][j-1];
            Rez[i][j]%=mod;
        }
    }
    for ( i=0; i<=n; i++,printf("\n") ){
        for ( j=0; j<=n; j++ ){
            printf("%d ",Rez[i][j]); 
        }
    }
    Fin[0][0]=0;
    for ( i=1; i<=k; i++ ){
        for ( s=
    }
    return 0;
}
