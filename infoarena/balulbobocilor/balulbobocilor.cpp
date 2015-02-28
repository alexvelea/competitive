#include <cstdio>
using namespace std;
    
    int d,v1,v2,v3,a,b;

int main(){
	freopen ("balulbobocilor.in","r",stdin);
	freopen ("balulbobocilor.out","w",stdout);
    scanf ("%d", &d);
    scanf ("%d %d %d", &v1, &a, &b );
    scanf ("%d %d %d", &v2, &a, &b );
    scanf ("%d", &v3 );
    printf("%.9lf",double(1.0*d/(v1+v2)*v3));
}
