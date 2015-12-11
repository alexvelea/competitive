#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

    #define max_n 1000006
    int Lung[400],s,w,n,i;
    int A[50];
    char Text[max_n];

int main(){

    freopen ("texttrim.in","r",stdin);
    freopen ("texttrim.out","w",stdout);

    for ( i=0; i<=26; i++ ){
        scanf ("%d", &A[i] );
    }
    Lung[' ']=A[0];
    for ( i=1; i<=26; i++ ){
        Lung['a'+i-1]=A[i];
    }
    
    fgets ( Text, max_n, stdin );  
    fgets ( Text, max_n, stdin );

    n=strlen ( Text );
    scanf ("%d", &w );

    for ( i=0; ( i<n && s<=w ) ; i++ ){
        s+=Lung[ Text[i] ];  
    }
    if ( s<=w ){
        // afisam tot textul
        for ( i=0; i<=n; i++ ){
            printf("%c", Text[i] );
        }
    }
    else{
        s=0;
        for ( i=0; ( i<n && s<=w-3 ); i++ ){
            s+=Lung[ Text[i] ];
            if ( s<=w-3 ){
                printf("%c", Text[i]);
            }
        }
        printf("...");
    }
    return 0;
}
