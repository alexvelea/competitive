#include <cstdio>
using namespace std;

    #define MOD 10007
    #define max_n 20005
    int n,k,x,i,j,A[max_n];

int main(){
    freopen ("desc2.in","r",stdin);
    freopen ("desc2.out","w",stdout);
    scanf ("%d %d %d", &n, &k, &x );
    n-=k*(k-1)*x/2;
    n-=k;
    A[0]=1;
    for ( i=1; i<=k; i++ )
        for ( j=0; j<=n; j++ ){
            A[i+j]+=A[j];
            A[i+j]%=MOD;
        }
    printf("%d", A[n]);    
    return 0;
}
