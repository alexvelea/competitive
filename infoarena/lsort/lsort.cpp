#include <cstdio>
#include <vector>
using namespace std;

    #define max_n 1004
    #define pb push_back

    int C[max_n][max_n];
    int T[max_n],Poz[max_n];
    int i,j,n;
    int poz,rez1,rez2,l;

    struct stare {
        int val,from;
    } Best[max_n][max_n];

    vector<int> rez;
    int st,dr;

int main(){
        
        freopen ("lsort.in","r",stdin);
        freopen ("lsort.out","w",stdout);

    scanf ("%d", &n );
    for ( i=1; i<=n; i++ ){
        scanf ("%d", &T[i] );
        Poz[ T[i] ]=i;
    }
    for ( i=2; i<=n; i++ ){
        for ( j=1; j< Poz[ i-1 ]; j++ )
            C[i][j]=C[i-1][j];
        for ( j=Poz[ i-1 ]; j<=n; j++ )
            C[i][j]=1+C[i-1][j];
    }
    for ( i=1; i<=n; i++ )
        C[n+1][i]=i;
    for ( i=1; i<=n; i++ )
        Best[i][i].val=Poz[i];
    for ( l=1; l<n; l++ ){
        for ( i=1; i+l<=n; i++ ){
            // avem intervalul [i,i+l]
            // vedem din ce poate sa provina.
            rez1=0;
            // costul ca sa punem acum elementul i in interval.
            rez1+=Best[i+1][i+l].val;
            poz=Poz[i];
            rez1+=(l+1)*( poz - C[i+l+1][poz-1]+C[i][poz-1]);

            rez2=0;
            rez2+=Best[i][i+l-1].val;
            poz=Poz[i+l];
            rez2+=(l+1)*( poz - C[i+l+1][poz-1]+C[i][poz-1]);

            if ( rez1 < rez2 ){
                Best[i][i+l].val=rez1;
                Best[i][i+l].from=1;
            }
            else{
                Best[i][i+l].val=rez2;
                Best[i][i+l].from=2;
            }
        }
    }
    printf("%d\n", Best[1][n].val );
    st=1;
    dr=n;
    for ( l=1; l<=n; l++ ){
        if ( Best[st][dr].from == 1 ){
            rez.pb(st);
            st++;
        }
        else{
            rez.pb(dr);
            dr--;
        }
    }
    for ( i=rez.size()-1; i>=0; i-- )
        printf("%d ",rez[i]);
    return 0;
}
