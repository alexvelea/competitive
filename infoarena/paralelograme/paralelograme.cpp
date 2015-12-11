#include <cstdio>
#include <iostream>
using namespace std;

    int n,m,i,j;
    long long rez;

int main(){
    scanf ("%d %d", &n, &m);
    for ( i=0; i<=n; i++ ){
        for ( j=i; j<=m; j++ ){
            if ( ( i!=0 ) || ( j!=0 ) ){
                cout<<i<<" "<<j<<"\n ---    ";
                rez+=(long long)(n-i+1)*(n+2)*(m-j+1)*(m+2)/4;
                cout<<rez<<"\n";
            }
        }
    }
    rez-=n*m;
    cout<<rez<<"\n";
    return 0;
}
