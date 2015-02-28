#include <cstdio>
#include <vector>
using namespace std;

    #define pb push_back
    #define max_n 100005

    int V[max_n],In[max_n],a,b,i,n,m;
    vector<int> T[max_n],Rez;

void df ( int nod ){
    V[nod]=1;
    Rez.pb(nod);
    for ( int i=0; i<T[nod].size(); i++ ){
        In[T[nod][i]]--;
        if ( !In[T[nod][i]] )
            df( T[nod][i] );
    }
}

int main(){

        freopen ("sortaret.in","r",stdin);
        freopen ("sortaret.out","w",stdout);

    scanf ("%d %d", &n, &m );
    for ( i=1; i<=m; i++ ){
        scanf ("%d %d", &a, &b );
        T[a].pb(b);
        In[b]++;
    }
    for ( i=1; i<=n; i++ )
        if ( ( In[i]==0 ) && ( V[i]==0 ) )
            df(i);

    for ( i=0; i<Rez.size(); i++ )
        printf("%d ",Rez[i]);

    return 0;
}
