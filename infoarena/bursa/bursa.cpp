#include <cstdio>
using namespace std;

    int n,p,i;
    long long s;

    struct money{
        long long m,a;
    } Rez[2],Next[2];

int main(){
    
    freopen ("bursa.in","r",stdin);
    freopen ("bursa.out","w",stdout);

    scanf ("%d %lld", &n, &s );
    Rez[0].m=s;
    for ( i=1; i<=n; i++ ){

        scanf ("%d", &p);

        Next[0]=Rez[0];
        Next[1]=Rez[1];
        if ( Next[0].m < Rez[1].m + p*Rez[1].a ){
            Next[0].m = Rez[1].m + p*Rez[1].a;
        }
        if ( Next[1].a <= Rez[0].m/p ){
            if ( ( Next[1].m < Rez[0].m%p ) || ( Next[1].a < Rez[0].m/p ) ){
                Next[1].a=Rez[0].m/p;
                Next[1].m=Rez[0].m%p;
            }
        }
        Rez[0]=Next[0];
        Rez[1]=Next[1];
    }
    printf("%lld", ( Rez[0].m - s) );
    return 0;
}
