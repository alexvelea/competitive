#include <cstdio>
using namespace std;

    #define max(a,b) ((a>b)?(a):(b))
    int le,last,last2,n,i,a,maxim;

int main(){
        freopen ("suma2.in","r",stdin);
        freopen ("suma2.out","w",stdout);
    scanf ("%d", &n);
    for ( i=1; i<=n; i++ ){
        scanf ("%d", &a );
        if ( a+le > maxim ){
            maxim=a+le;
        }
        last2=le+a;
        le=max(le,last);
        last=last2;
    }
    printf("%d", maxim);
    return 0;
}

