#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

    #define max_n 2000005
    #define pb push_back

    int n,m,Pre[max_n],rez;
    int i;
    char A[max_n],B[max_n];

    vector<int> Rez;

    int min ( int a, int b ){
        if ( a < b )
            return a;
        return b; 
    }

    void prefix ( ){
        Pre[0]=Pre[1]=0;
        int k=0;
        for ( int i=2; i<=m; i++ ){
            while ( (k!=0) && (B[k+1]!=B[i]) )
                k = Pre[k];

            if ( B[k+1] == B[i] )
                k++;
            Pre[i]=k;            
        }
        return ;
    }

int main(){

        freopen ("strmatch.in","r",stdin);
        freopen ("strmatch.out","w",stdout);

    scanf ("%s\n%s",&B, &A);
    m=strlen(B);
    n=strlen(A);
    for ( i=n; i>0; i-- )
        A[i]=A[i-1];
    for ( i=m; i>0; i-- )
        B[i]=B[i-1];
    A[0]=B[0]=' ';

    prefix();
    int k=0;
    for ( i=1; i<=n; i++ ){
        while ( k && B[k+1]!=A[i] )
            k = Pre[k];
        if ( B[k+1]==A[i] )
            k++;
        if ( k == m ){
            k=Pre[m];
            Rez.pb( i-m );
        }
    }
    printf("%d\n", Rez.size() );
    for ( i = 0; i <= 999 && i < Rez.size(); i++ )
        printf("%d ",Rez[i]);
    return 0;
}
