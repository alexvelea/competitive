#include <cstdio>
using namespace std;

    int t,i,s1,s2,a;

int main(){
    
    freopen ("switch.in","r",stdin);
    freopen ("switch.out","w",stdout);
    
    scanf ("%d", &t );
    for ( ; t; t-- ){
        s1=s2=0;
        for ( i=0; i<4; i++ ){
            scanf ("%d", &a );
            s1+=a;
        }
        for ( i=0; i<4; i++ ){
            scanf ("%d", &a);
            s2+=a;
        }
        if ( (s1&1) == (s2&1) ){
            printf("DA\n");
        }
        else{
            printf("NU\n");
        }
    }
}

