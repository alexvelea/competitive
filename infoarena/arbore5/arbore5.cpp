#include <cstdio>
#include <vector>
using namespace std;

    #define max_n 100005
    #define pb push_back

    int n,m,a,b,i,rez;

    bool R[max_n],V[max_n];
    vector<int> T[max_n];

    void df ( int nod ){
        V[nod]=1;
        for ( int i=0; i<T[nod].size(); i++ ){
            if ( !V[ T[nod][i] ] ){
                df ( T[nod][i] );
                if ( !R[ T[nod][i] ] )
                    rez++;
                R[nod]^=R[ T[nod][i] ];
            }
        }
        return ;
    }

int main(){

        freopen ("arbore5.in","r",stdin);
        freopen ("arbore5.out","w",stdout);

    scanf ("%d %d", &n, &m );
    for ( i=1; i<n; i++ ){
        scanf ("%d %d", &a, &b );
        T[a].pb(b);
        T[b].pb(a);
    }
    for ( i=1; i<=m; i++ ){
        scanf("%d %d", &a, &b );
        R[a]^=1;
        R[b]^=1;
    }
    df(1);
    printf("%d",rez);
    return 0;
}

