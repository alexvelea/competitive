#include <cstdio>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;
    
    #define max_n 1005
    #define fi first
    #define se second
    #define MOD 30103

    int A[max_n];
    pair<int,int> Pa[max_n*max_n];

    int i,j;
    int n,m;
    long long rez,s;

    long long Aib[max_n][max_n];

    bool my_sort ( pair<int,int> a, pair<int,int> b ){
        if (  A[a.fi]+A[a.se] ==  A[b.fi]+A[b.se] ){
            if( a.se == b.se ){
                return a.fi < b.fi;
            }
            else{
                return a.se > b.se;
            }
        }
        else{ 
            return A[a.fi]+A[a.se] < A[b.fi]+A[b.se];
        }
    }

    long long query ( int x, int y ){
        int i,j;
        long long rez=0;
        for ( i=x; i; i-=i&(-i) )
            for ( j=y; j; j-=j&(-j) )
                rez+=Aib[i][j];
        return rez;
    }

    void add ( int x, int y, long long val ){
        int i,j;
        for ( i=x; i<=n; i+=i&(-i) )
            for ( j=y; j<=n; j+=j&(-j) ){
                Aib[i][j]+=val;
                if ( Aib[i][j] >= MOD ){
                    Aib[i][j]-=MOD;
                }
            }
    }
 
int main(){

    freopen ("evantai.in","r",stdin);
    freopen ("evantai.out","w",stdout);

    scanf ("%d", &n );
    for ( i=1; i<=n; ++i ){
        scanf ("%d", &A[i] );
    }
    for ( i=1; i<n; ++i ){
        for ( j=i+1; j<=n; ++j ){
            Pa[++m]=make_pair(i,j);
        }
    }
     sort ( Pa+1, Pa+m+1, my_sort );
    for ( i=1; i<=m; i++ ){
        s = query ( Pa[i].se-1 , n-Pa[i].fi );
        s ++;
        s%=MOD;
        rez+=s;
        rez%=MOD;
        add ( Pa[i].se , n-Pa[i].fi+1 , s );
    }
    cout<<rez;
    return 0;
}
