#include <cstdio>
using namespace std;
    
    int x,y,S,n,a,b,rez;
    int abs ( int a ){
        if ( a < 0 )
            return -a;
        return a;
    }

int main(){
    
        freopen ("cal.in","r",stdin);
        freopen ("cal.out","w",stdout);

    scanf ("%d %d %d %d", &x, &y, &S, &n );
    for ( ; n; n-- ){
        scanf ("%d %d", &a, &b );
        if ( ( abs(a-x)+abs(b-y) ) == S )
            rez++;
    }
    printf("%d",rez);
    return 0;
}
