#include <cstdio>
using namespace std;

    int a,b,aa,bb;

    double min ( double a, double b ){
        if ( a < b )
            return a;
        return b;
    }
    double max ( double a, double b ){
        if ( a > b )
            return a;
        return b;
    }

int main(){

        freopen ("scalecrop.in","r",stdin);
        freopen ("scalecrop.out","w",stdout);

    scanf ("%d %d %d %d", &a, &b, &aa, &bb );
    double r=min( (double) aa/a, (double) bb/b);
    printf("%.5lf %.5lf\n",(double) aa/r, (double) bb/r );
    return 0;
}
