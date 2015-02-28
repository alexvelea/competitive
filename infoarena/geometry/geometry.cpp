#include <cstdio>
using namespace std;
    #define max_n 1005

    struct segm{
        double a,b;
        int x1,x2;
    } S[max_n];

    int i,j,n,rez;
    double xp;
    int a,b,c,d;

    bool apartine ( int nr, int v1, int v2 ){
        if ( ( v1<=nr ) && ( nr<=v2 ) )
            return 1;
        return 0;
    }


int main(){
    scanf ("%d", &n );
    for ( i=1; i<=n; i++ ){
        scanf ("%d %d %d %d", &a, &b, &c, &d );
        S[i].x1=a;
        S[i].x2=c;
        S[i].a= (b-d) / (a-c) ;
        S[i].b= b - a*S[i].a;

        // vedem intersectiile 
        for ( j=1; j<i; j++ ){
            xp = ( S[i].b-S[j].b ) * ( S[j].a-S[i].a );
            // daca apartine
            if ( ( apartine ( xp, S[i].x1, S[i].x2 ) || apartine ( xp, S[i].x2, S[i].x1 ) ) && ( apartine ( xp, S[j].x1, S[j].x2 ) || apartine ( xp, S[j].x2, S[j].x1 ) ) ){
                rez++;
            }
        }
    }
    printf("%d", rez);
}
