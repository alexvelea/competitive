#include <cstdio>
#include <deque>
#include <iostream>
using namespace std;

    #define prec 1000
    #define max_n 30005
    struct ab{
        int a,b;
    } T[max_n];

    int n,u,l,i;

bool solve ( int r ){

    long long S[max_n];
    int i;
    S[0]=0;
    for ( i=1; i<=n; i++ ){
        S[i]=S[i-1]+T[i].a-r*T[i].b;
    }
    deque <int> Deq;
    Deq.push_front(0);
    for ( i=l; i<=n; i++ ){
        if ( ( S[i]-S[ Deq.front() ] ) >=0 ){
            return 1;
        }
        // adaugam
        while ( ( !Deq.empty() ) && ( S[i-l+1 ] < S[ Deq.back() ] ) ){
            Deq.pop_back();
        }
        Deq.push_back(i-l+1);

        // scoatem primul element.
        if ( Deq.front() == ( i-u+1 ) ){
            Deq.pop_front();
        }
    }
    return 0;
}


int BS ( )
{
    long long rez=0;
    for ( long long act = ( 1<<20 ); act; act>>=1 ){
        if ( solve ( act+rez ) ){
            rez+=act;
        }
    }
    return rez;
}

int main(){
    
        freopen ("secv3.in","r",stdin);
        freopen ("secv3.out","w",stdout);
    
    scanf ("%d %d %d", &n, &l, &u );
    for ( i=1; i<=n; i++ ){
        scanf ("%d", &T[i].a );
        T[i].a*=prec;
    }
    for ( i=1; i<=n; i++ ){
        scanf ("%d", &T[i].b );
    }
    printf ("%.2f", float( 1.0 * BS ()/prec ));
    
    return 0;
}
