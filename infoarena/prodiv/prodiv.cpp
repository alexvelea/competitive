#include <cstdio>
#include <iostream>
using namespace std;

    long long d,n,cn,nr,P[50],D[50],i,a,rez;

int main(){

        freopen ("prodiv.in","r",stdin);
        freopen ("prodiv.out","w",stdout);

    cin>>n;
    cn=n;
    long long d2=4;
    for ( d=2; d2<=n && cn>1; d2+=d<<1,d2++,d++ ){
        if ( cn%d == 0 ){
            D[++nr]=d;
            while ( cn%d==0 ){
                cn/=d;
                P[nr]++;
            }
        }
    }
    if ( cn > 1 ){
        D[++nr]=cn;
        P[nr]=1;
    }
    a=1;
    for ( i=1; i<=nr; i++ ){
        if ( P[i]&1 )
            rez++;
        for ( d=1; d<=P[i]/2; d++ )
            a*=D[i];
    }
    cout<<a<<" "<<n/a<<"\n"<<(1<<rez);
//    printf("%d %d\n%d",a,(n/a),(1<<rez));
    return 0;
}
