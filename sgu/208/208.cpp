#include <cstdio>
using namespace std;
    
    #define max_cif 500

    int n,m,i,j,l,d,Rez[500],maxnr;
    int V[100][100];

    struct nrmare{
        int nrcif,cif[max_cif];
    } rez,p2;
    struct matrice {
        int x[30][30],y[30][30],n,m;
    } mat;

    void rotire(){
        matrice m2;
        for ( i=0; i<30; i++ )
            for ( j=0; j<30; j++ )
                m2.x[i][j]=0,m2.y[i][j]=0;
        for ( i=1; i<=mat.n; i++ )
            for ( j=1; j<=mat.m; j++ ){
                m2.x [j][mat.n-i+1]=mat.x[i][j];
                m2.y [j][mat.n-i+1]=mat.y[i][j];
            }
        m2.m=mat.n;
        m2.n=mat.m;
        mat=m2;
    }

    void rotirex(){
        int i,j;
        for ( j=1; j<=mat.m; j++ ){
            mat.x[mat.n+1][j]=mat.x[1][j];
            mat.y[mat.n+1][j]=mat.y[1][j];
        }
        for ( i=1; i<=mat.n; i++ ){
            for ( j=1; j<=mat.m; j++ ){
                mat.x[i][j]=mat.x[i+1][j];
                mat.y[i][j]=mat.y[i+1][j];
            }
        }
    }

    void rotirey(){
        int i,j;
        for ( i=1; i<=mat.n; i++ ){
            mat.x[i][mat.m+1]=mat.x[i][1];
            mat.y[i][mat.m+1]=mat.y[i][1];
        }
        for ( j=1; j<=mat.m; j++ ){
            for ( i=1; i<=mat.n; i++ ){
                mat.x[i][j]=mat.x[i][j+1];
                mat.y[i][j]=mat.y[i][j+1];
            }
        }
    }

    int x2,y2;

    int i1,j1,x1,y1,nr;

    int abs ( int a ){
        if ( a<0 )
            return -a;
        return a;
    }

    int gcd ( int a, int b ){
        if ( b==0 )
            return a;
        if ( a==0 )
            return b;
        return gcd(b,a%b);
    }

    nrmare adunare ( nrmare a, nrmare b ){
        nrmare c;
        int t=0,i;
        for ( i=0; i<max_cif; i++ )
            c.cif[i]=0;
        for ( i=1; i<=a.nrcif || i<=b.nrcif || t; i++ ){
            c.cif[i]=a.cif[i]+b.cif[i]+t;
            t=c.cif[i]/10;
            c.cif[i]%=10;
        }
        c.nrcif=i-1;
        return c;
    }
    nrmare multi ( nrmare a, int pro ){
        int t=0,i;
        for ( i=1; i<=a.nrcif || t; i++ ){
            a.cif[i]*=pro;
            a.cif[i]+=t;
            t=a.cif[i]/10;
            a.cif[i]%=10;
        }
        a.nrcif=i-1;
        return a;
    }
    nrmare divide ( nrmare a, int div ){
        int t=0,i;
        nrmare r;
        for ( i=0; i<max_cif; i++ )
            r.cif[i]=0;
        r.nrcif=0;
        for ( i=a.nrcif; i>0; i-- ){
            t+=a.cif[i];
            r.cif[i]=t/div;
            t=t%div;
            t*=10;
        }
        for ( i=a.nrcif; r.cif[i]==0; i-- )
            ;
        r.nrcif=i;
        if ( i==0 )
            r.nrcif=1;
        return r;
    }
    void afisare ( nrmare a ){
        for ( int i=a.nrcif; i>0; i-- )
            printf("%d",a.cif[i]);
        printf("\n");
        return ;
    }
void solve(){
    for ( l=0; l<2 ; l++ ){
        for ( i=0; i<mat.n; i++ ){
            rotirex();
            for ( j=0; j<mat.m; j++ ){
                rotirey();
                // incepem sa vedem numarul de ciclii
                nr=0;
                for ( i1=0; i1<=mat.n; i1++ ){
                    for ( j1=0; j1<=mat.m; j1++ ){
                        V[i1][j1]=0;
                    }
                }
                for ( i1=1; i1<=mat.n; i1++ ){
                    for ( j1=1; j1<=mat.m; j1++ ){
                        if ( !V[i1][j1] ){
                            nr++;    
                            x1=mat.x[i1][j1];
                            y1=mat.y[i1][j1];
                            V[x1][y1]=1;
                            while ( ( x1!=i1 ) || ( y1!=j1 ) ){
                                x2=x1;
                                y2=y1;

                                x1=mat.x[x2][y2];
                                y1=mat.y[x2][y2];
                                V[x1][y1]=1;
                            }
                        }                           
                    }
                }
                Rez[nr]++;
                if ( nr > maxnr )
                    maxnr=nr;
            }
        }
        rotire();
        rotire();
    }
 
}
int main(){
    scanf ("%d %d", &n, &m);
    for ( i=1; i<=n; i++ ){
        for ( j=1; j<=m; j++ ){
            mat.x[i][j]=i;
            mat.y[i][j]=j;
        }
    }
    mat.n=n;
    mat.m=m;
    d=n*m*2;
    solve();
    if ( n==m ){
        rotire();
        solve();
        d*=2;
    }
    // facem in numar mare ^^
    for ( i=1; i<=maxnr || Rez[i]; i++ ){
        Rez[i+1]+=Rez[i]>>1;
        Rez[i]&=1;
    }
    maxnr=i-1;
    p2.nrcif=1;
    p2.cif[1]=2;
    for ( i=1; i<=maxnr; i++ ){
        if ( Rez[i] )
            rez=adunare(rez,p2);
        p2=multi(p2,2);
    }
    rez=divide(rez,d);
    afisare(rez);
    return 0;
}
