#include <cstdio>
#include <algorithm>
using namespace std;

    #define max_n 30005    
    #define MOD 32173

    struct numar {
        int el,val;
    } T[2*max_n];
    
    bool mysort ( numar a, numar b ){
        return a.el < b.el;
    }

    int n,m,i,val,k,rez,a,b;

int main(){
    freopen ("ben.in","r",stdin);
    freopen ("ben.out","w",stdout);
    scanf ("%d", &n);
    for ( i=1; i<=n; i++ ){
        scanf ("%d %d", &a, &b );
        T[++m].el=a;
        T[  m].val=1;
        T[++m].el=b;
        T[  m].val=-1;
    }
    sort ( T+1, T+m+1, mysort );
    for ( i=1; i<=m; i++ ){
        val+=T[i].val;
        if ( val > k )
            k=val;
    }
    val=0;
    rez=1;
    for ( i=1; i<=m; i++ ){
        val+=T[i].val;
        if ( T[i].val == 1 ){
            rez*=(k-val+1);
            rez%=MOD;
        }
    }
    printf("%d %d", k, rez);
    return 0;
}
