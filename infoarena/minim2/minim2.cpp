#include <cstdio>
using namespace std;

    #define max_n 100005
    #define eps 0.00000001

    int n,i,j,Nr[max_n];
    double a,b,target;
    double pow[15];
double putere ( int p ){
    int ind=0;
    double rez=1;
    while ( p ){
        if ( p&1 )
            rez*=pow[ind];
        ind++;
        p>>=1;
    }
    return rez;
}
int fin=0;
int solve ( double mid ){
    int i;
    fin=0;
    double rez=0;
    for ( i=1; i<=n; i++ ){
        double act=Nr[i];
        if ( act - mid > eps )
            act*=a,fin++;
        // cautam binar
        int p=0;
        for ( int ind=(1<<12); ind; ind>>=1 ){
            double aux=putere(ind+p);
            if ( act*aux > mid ){
                p+=ind;
                act*=aux;
            }
        }
        fin+=p;
        rez+=act;
    }
    if ( rez > target )
        return 1;
    return 0;
}

int main(){
    /*

        freopen ("minim2.in","r",stdin);
        freopen ("minim2.out","w",stdout);

    */
    scanf ("%d", &n );
    for ( i=1; i<=n; i++ ){
        scanf ("%d", &Nr[i] );
    }
    scanf ("%lf %lf %lf", &a, &b, &target );
    // facem cautarea binana pentru lungimea segmentelor.
        // calculam puterile lui b ^^
        pow[0]=b;
        for ( i=1; i<=12; i++ ){
            pow[i]=pow[i-1]*pow[i-1];
        }
    double rez=0;
    for ( double ind=(1<<20); ind>eps; ind/=2.0 ){
        printf("%.7lf       %.5lf\n",rez+ind,rez);
        if ( !solve( rez+ind ) ){
            rez+=ind;
        }
    }
    printf("%.5lf\n",rez);
    solve(rez);
    printf("%d", fin );

    return 0;
}

