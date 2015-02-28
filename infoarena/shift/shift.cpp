#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

    #define max_n 100005

    int i,n;
    struct cif {
        int nr,poz[2],c[2];
    } El[26];

    char text[max_n],a[26],b[26];

    struct rez {
        int poz,cost;
    } R[2],N[2];


int main(){

        freopen ("shift.in","r",stdin);
        freopen ("shift.out","w",stdout);
    cin>>text;
    n=strlen(text);
    for ( i=0; i<26; i++ ){
        cin>>a[i]>>b[i];
        El[a[i]-'a'].poz[ El[a[i]-'a'].nr++ ]=i+1;        
        El[b[i]-'a'].poz[ El[b[i]-'a'].nr++ ]=i+1;
    }
    for ( i=0; i<26; i++ )
        El[i].nr=0;
    for ( i=0; i<26; i++ ){
        scanf ("%d", &El[ a[i]-'a'].c[ El[a[i]-'a'].nr++ ] );
        scanf ("%d", &El[ b[i]-'a'].c[ El[b[i]-'a'].nr++ ] );
    }
    // rezolvammmm
    R[1].poz=R[0].poz=1;
    for ( i=0; i<n; i++ ){
        N[0].cost = min ( abs( R[0].poz-El[ text[i]-'a' ].poz[0] ) + R[0].cost , abs( R[1].poz-El[ text[i]-'a' ].poz[0] ) + R[1].cost ) + El[ text[i]-'a' ].c[0] ;
        N[1].cost = min ( abs( R[0].poz-El[ text[i]-'a' ].poz[1] ) + R[0].cost , abs( R[1].poz-El[ text[i]-'a' ].poz[1] ) + R[1].cost ) + El[ text[i]-'a' ].c[1] ; 
        N[0].poz = El[ text[i]-'a' ].poz[0];
        N[1].poz = El[ text[i]-'a' ].poz[1];
        R[0]=N[0];
        R[1]=N[1];
    }
    printf("%d", min ( R[0].cost, R[1].cost ) );
    return 0;
}
