#include <cstdio>
#include <algorithm>
using namespace std;

    #define max_k 105
    #define max_n 16005
    #define INF 0x3f3f3f3f

    struct muncitor {
        int l,p,s;
    } M[max_k];
    
    struct linie {
        int Best[max_n];
    } last,next;

    struct deq {
        int poz,el;
    } Deq[max_n];

    bool mysort ( muncitor a, muncitor b ){
        return a.s < b.s;
    }

    int i,j,k,n;

int main(){

        freopen ("gard.in","r",stdin);
        freopen ("gard.out","w",stdout);

    scanf ("%d %d", &n, &k );
    for ( i=1; i<=k; i++ ){
        scanf ("%d %d %d", &M[i].l, &M[i].p, &M[i].s );
    }
    sort ( M+1, M+k+1, mysort );
    for ( i=1; i<=k; i++ ){
        // pregatim stiva
        int suma=0,st=0,dr=0;
        Deq[0].poz=0;
        Deq[0].el=-INF;
        suma = M[i].p * ( M[i].s - max ( 0, M[i].s-M[i].l ) -1 );
        for ( j=max ( 1, M[i].s-M[i].l+1 ); j<=M[i].s; j++ ){
            while ( ( dr >= st ) && ( last.Best[j-1]+suma > Deq[dr].el ) )
                dr--;
            Deq[++dr].el = last.Best[j-1]+suma;
            Deq[  dr].poz = j;            
            suma -= M[i].p;
        }
        suma=0;
        for ( j=M[i].s; j<=n && j<M[i].s+M[i].l; j++ ){
            suma += M[i].p;
            if ( Deq[st].poz == j-M[i].l )
                st++;

            next.Best[j]=max(next.Best[j], suma + Deq[st].el);
        }
        for ( j=1; j<=n; j++ )
            next.Best[i]=max(next.Best[i], last.Best[i]);
        last=next;
    }
    int maxim = 0;
    for ( i=1; i<=n; i++ )
        if ( last.Best[i] > maxim )
            maxim = last.Best[i];
    printf("%d\n",maxim);
    return 0;
}
