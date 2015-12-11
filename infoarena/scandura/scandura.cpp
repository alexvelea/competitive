#include <cstdio>
using namespace std;

    #define max_n 1000005
    long long rez,act;
    int a,nr,n,m,div,i,s1,s2,l1,l2;

    long long D1[max_n],D2[2*max_n];

int main(){
    freopen ("scandura.in","r",stdin);
    freopen ("scandura.out","w",stdout);
    scanf ("%d %d", &n, &m );
    for ( i=1; i<=n; i++ ){
        scanf ("%lld", &D1[i] );
    }
    s1=1;
    l1=n;
    s2=1;
    l2=0;
    if ( (n-1)%(m-1) ){
        for ( i=1; i<=(n-1)%(m-1)+1; i++ )
            act+=D1[i];
        D2[++l2]=act;
        s1=i;
        n-=(n-1)%(m-1);
        rez+=act;
    }
    for ( ; n>1; ){
        act=0;
        for ( i=1; i<=m && n; i++ ){
            if ( s1<=l1 && s2<=l2 ){
                // luam minimul
                if ( D1[s1] < D2[s2] ){
                    act+=D1[s1];
                    s1++;
                }
                else{
                    act+=D2[s2];
                    s2++;
                }
            }
            else{
                if ( s1<=l1 ){
                    act+=D1[s1];
                    s1++;
                }
                else{
                    act+=D2[s2];
                    s2++;
                }
            }
            n--;
        }
        rez+=act;
        n++;
        D2[++l2]=act;
    }    
    printf("%lld",rez);
    return 0;
}

