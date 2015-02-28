#include <cstdio>
using namespace std;

    #define INF 0x3f3f3f3f
    int i,n,j,m,minim,minim2,aux;
    int T[300];
    struct linie {
        int el[300];
    } last,next;

int main(){
    freopen ("lacusta.in","r",stdin);
    freopen ("lacusta.out","w",stdout);
    scanf ("%d %d", &n, &m );
    for ( j=2; j<=m; j++ ){
        last.el[j]=INF;
    }
    last.el[1]=0;
    for ( i=1; i<n; i++ ){
        minim=minim2=INF;
        for ( j=1; j<=m; j++ ){
            scanf ("%d", &T[j]);
            last.el[j]+=T[j];
            if ( last.el[j] < minim ){
                minim2=minim;
                minim=last.el[j];
            }
            else
                if ( last.el[j] < minim2 )
                    minim2=last.el[j];
        }
        for ( j=1; j<=m; j++ ){
            if ( last.el[j] == minim )
                next.el[j]=T[j]+minim2;
            else
                next.el[j]=T[j]+minim;
        }
        last=next;
    }
    minim=INF;
    for ( j=1; j<m; j++ ){
        scanf ("%d", &T[j] );
        if ( T[j]+last.el[j] < minim )
            minim=T[j]+last.el[j];
    }
    scanf ("%d", &aux);
    printf("%d",minim+aux);
    return 0;
}
