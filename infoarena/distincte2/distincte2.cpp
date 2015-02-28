#include <cstdio>
using namespace std;

    #define max_n 1000005

    bool viz[max_n];
    int Sp[max_n];

    int n,i,q,a,b;

int main(){

        freopen ("distincte2.in","r",stdin);
        freopen ("distincte2.out","w",stdout);

    scanf ("%d %d", &n, &q );
    for ( i=1; i<=n; i++ ){
        scanf ("%d", &a );
        viz[a]=1;
    }
    for ( i=1; i<max_n; i++ ){
        Sp[i]=Sp[i-1]+viz[i];
    }
    for ( ; q; q-- ){
        scanf ("%d %d", &a, &b );
        printf("%d\n", Sp[b]-Sp[a-1]);
    }
    return 0;
}
