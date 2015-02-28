#include <cstdio>
#include <utility>
#include <iostream>
using namespace std;

    #define max_n 310
    #define eps 0.00001

    struct lin{
        double val[max_n];
    } Li[max_n];

    double Rez[max_n],p;
    int n,m,i,j,l,c,k;

int main(){
    freopen ("gauss.in","r",stdin);
    freopen ("gauss.out","w",stdout);

    scanf ("%d %d", &n, &m );
    for ( i=1; i<=n; i++ ){
        for ( j=1; j<=m+1; j++ ){
            scanf ("%lf", &Li[i].val[j] );
        }
    }
	int xx = Li[1].val[1];
    int l=1,c=1;
    for ( ; l<=n; ){
        for ( k=l; k<=n && ( ( Li[k].val[c] < eps ) && ( Li[k].val[c] > -eps ) ); k++ )
            ;
        if ( k==n+1 ){
            ++c;
            continue;
        }
        if ( l!=k ){
            swap ( Li[l], Li[k] );
        }
        p=Li[l].val[c];
        for ( k=c; k<=m+1; ++k ){
            Li[l].val[k]/=p;
        }
        for ( k=1; k<=n; ++k ){
            p=Li[k].val[c];
            if ( k!=l ){
                for ( j=c; j<=m+1; ++j ){
                    Li[k].val[j] -= p*Li[l].val[j];
                }
            }
        }
        ++l;
        ++c;
    }
    for ( i=n; i>0; --i ){
        for ( j=1; j<=m+1; ++j ){
            if ( !( ( Li[i].val[j] < eps ) && ( Li[i].val[j] > -eps ) ) ){
                if (j==m+1 ){
                    printf("Imposibil\n");
                    return 0;
                }

                Rez[j] = Li[i].val[m+1];
             /*   for ( k=m; k>j; k-- ){
                    Rez[j]-=Li[i].val[k]*Rez[k];
                }*/
                break;
            }
        }
    }
	double sum=0;
	for ( i=1; i<=m; ++i ){
		sum += Rez[i];
	}
	printf("%.10lf\t%.10lf\n",sum,1.0*(xx+1)*Rez[1]/sum);
    for ( i=1; i<=m; ++i ){
        printf("%.10lf ",Rez[i]);
    }
    return 0;
}

