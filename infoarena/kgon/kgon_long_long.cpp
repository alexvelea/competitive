#include<cstdio>
#include<cmath>
 
#include<algorithm>
#include<iostream>
#include<fstream>
 
using namespace std;
 
ifstream in("kgon.in");
ofstream out("kgon.out");
 
#define max_n 100005
#define pi 3.14159265358979
#define EPS 0.000001
#define MULTI 10000000
#define MULTI_mic  100
 
double x,r;
int n,k,i,j,ok,It[ max_n ], Final[ max_n ],rez;
long long Start[ max_n ], El[ max_n ], start;
 
 
int main(){
    in>>n>>k>>r;
    for( i=1; i<=k+1; ++i ){
        Start[ i ] = 1LL*2.0*pi*r/k*(i-1)*MULTI;
    }
    for( i=1; i<=n; ++i ){
        in>>x;
        El[i]=x*MULTI;
    }
    sort( El+1, El+n+1 );
    j=1;
    for( i=1; i<=k; ++i ){
        It[ i ] = j;
        while( j<=n && Start[i+1]-El[j] >= MULTI_mic ){
            El[ j ] -= Start[ i ];
            ++j;
        }
        Final[ i ] = j;
    }                                                      
    for( i=1; i< Final[ 1 ]; ++i ){
        start = El[ i ];
        ok=1;
        for( j=1; j<=k; ++j ){
            while( It[ j ] < Final[ j ] && start - El[ It[ j ] ] >= MULTI_mic ){
                ++It[ j ];
            }
            if( abs(start - El[ It[ j ] ]) < MULTI_mic )
                ;
            else
                ok=0;
        }
        rez+=ok;
    }
    out<<rez;
    return 0;
}
