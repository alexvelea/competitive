#include <cstdio>
#include <algorithm>
using namespace std;

    #define max_n 1005
    int Mod [3] = { 100000007, 100000037, 100000039 };

    struct segment {
        int a,b,c;
    } Se[max_n];

    struct modul{
        int val[3];
    } Nu[max_n];

    int n,m,i,j,l,rez,x,y;

    bool mysort ( modul a, modul b ){
        for ( int i=0; i<3; i++ ){
            if ( a.val[i] == b.val[i] ){
                ;
            }
            else{
                return a.val[i]<b.val[i];
            }
        }
        return 1;
    }

    bool egal ( int a, int b ){
        for ( int i=0; i<3; i++ ){
            if ( Nu[a].val[i] != Nu[b].val[i] )
                return 0;
        }
        return 1;           
    }


int main(){

        freopen ("regiuni.in","r",stdin);
        freopen ("regiuni.out","w",stdout);

    scanf ("%d %d", &n, &m );
    for ( i=1; i<=n; i++ ){
        scanf ("%d %d %d", &Se[i].a, &Se[i].b, &Se[i].c );
    }
    for ( i=1; i<=m; i++ ){
        scanf ("%d %d", &x, &y );
        for ( j=1; j<=n; j++ ){
            for ( l=0; l<3; l++ ){
                Nu[i].val[l]*=2;
                Nu[i].val[l]+= ( x*Se[j].a + y*Se[j].b + Se[j].c ) > 0; 
                Nu[i].val[l]%=Mod[l];
            }
        }
    }
    sort ( Nu+1, Nu+m+1, mysort );
    for ( i=1; i<=m; ){
        j=i;
        while ( ( i<=m ) && ( egal (i,j ) ) )
            i++;
        rez++;
    }
    printf("%d",rez);

}

