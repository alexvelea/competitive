#include <cstdio>
#include <vector>
using namespace std;

    #define pb push_back
    #define max_m 100005
    #define max_n 300
    #define eps 0.000001

    typedef struct { int a,b,c; } Muchie;
    typedef struct { double exp[max_n]; } Linie;
    Muchie Mu[max_m];
    vector<int> T[max_n];
    Linie Gaus[max_n];

    int a,b,c,i,j,n,m;

/*
    Esc[i] = ( Esc[ T[1].nod ] + T[1].c )/.size + ( )/.size + ... 
    Esc[i] - Esc[ T[1].nod ]/.size - Esc[ T[2].nod ]/.size ... = ( T[1].c + T[2].c + ... ) /.size
*/

int main()
{
    freopen ("tunel.in","r",stdin);
    freopen ("tunel.out","w",stdout);

    scanf ("%d %d", &n, &m );
    for ( i=1; i<=m; i++ )
    {
        scanf ("%d %d %d", &Mu[i].a, &Mu[i].b, &Mu[i].c );
        
        T[ Mu[i].a ].pb ( i );
        T[ Mu[i].b ].pb ( i );
    }
    // facem ecuatiile
    for ( i=1; i<n; i++ ){
        Gaus[i].exp[i]=1;
        for ( j=0; j<T[i].size(); j++ ){
            Gaus[i].exp[ Mu[ T[i][j] ].a + Mu[ T[i][j] ].b - i ]    -=  1.0/T[i].size();
            Gaus[i].exp[ n+1 ]                                      +=  1.0*Mu[ T[i][j] ].c/T[i].size();
        }
    }
    // Pentru i=n
    Gaus[n].exp[n]=1;
    
    // rezolvam gausul
    int l=1,c=1;
    for ( ; l<=n; ){
        int k;
        double p;
        for ( k=l; k<=n && ( Gaus[k].exp[c] < eps && Gaus[k].exp[c] > -eps ); k++ )    
            ;
        if ( k==n+1 ){
            c++;
            continue;
        }
        if ( l!=k ){
            swap ( Gaus[l], Gaus[k] );
        }
        p=Gaus[l].exp[c];
        for ( k=c; k<=n+1; k++ ){
            Gaus[l].exp[k]/=p;
        }
        for ( k=1; k<=n; k++ ){
            if ( k!=l ){
                p = Gaus[k].exp[c];
                for ( j=1; j<=n+1; j++ ){
                    Gaus[k].exp[j] -= p* Gaus[l].exp[j];
                }
            }
        }
        l++;
        c++;
    }   
    printf("%.9lf\n",Gaus[1].exp[n+1]);
    return 0;
}
