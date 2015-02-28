#include <cstdio>
#include <iostream>
using namespace std;

    long long T[105][105],i,j,n,rez;

int main(){
    /*
    freopen ("sistem.in","r",stdin);
    freopen ("sistem.out","w",stdout);
    */
    cin>>n;
    T[2][1]=1;
    for ( i=3; i<=n; i++ ){
        for ( j=1; j<=n; j++ ){
            if ( T[i-1][j] )
                T[i][j]+=T[i-1][j]*j;
            if ( i>3 )
                T[i][j]+=T[i-3][j-1]*(i-1)*(i-2)*(i-3)/6;
        }
    }
    for ( i=1; i<=n; i++,cout<<"\n" )
        for ( j=1; j<=n; j++ )
            cout<<T[i][j]<<" ";
    for ( j=1; j<=n; j++ )
        rez+=T[n][j];
    cout<<rez;
    return 0;
}
