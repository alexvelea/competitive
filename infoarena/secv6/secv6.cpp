#include <cstdio>
using namespace std;

    #define INF (0xffffffff)
    #define max_n 16000010

    unsigned int n,i,last,act,rez,in,in2,ll;
    unsigned int Deq[max_n],Last[8200];

int min( int a, int b ){
    if ( a<b )
        return a;
    return b;
}

int main(){

    freopen ("secv6.in","r",stdin);
    freopen ("secv6.out","w",stdout);

    scanf ("%d", &n);
    for ( i=0; i<min(n,8192); i++ ){
        scanf ("%d", &Last[i]);
    }
    last=1;
    Deq[last]=INF;
    for ( i=0, in2=0; i<n; i++,in2++ ){
        if ( in2==8192 ){
            in++;
            in2=0;
        }
            ll=act;
            act=i+(Last[in] ^ Last[in2] );

        rez++;
        
        while ( ( act > Deq[last] ) ){
            rez++;
            last--;
        }
        if ( last == 1 ){
            rez--;
        }
        if ( act != Deq[last] ){
            Deq[++last]=act;
        }
    }
    printf("%d",rez);
    return 0;
}

