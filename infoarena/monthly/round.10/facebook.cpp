#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

    #define INF 0x3f3f3f3f
    #define max_n 1000000

    int n,k,a,i,j,minim=INF;
    vector<pair<int,int> > T;

int main(){
    freopen ("facebook.in","r",stdin);
    freopen ("facebook.out","w",stdout);
    cin>>n>>k;
    for ( i=1; i<=n; i++ ){
        cin>>a;
        T.push_back(make_pair(a,i));
    }
    sort ( T.begin() , T.end() );
    for ( i=0; i<n; ){
        j=i;
        while ( ( T[i].first == T[j].first ) && ( i-j < k )  && (i<n) ) 
            i++;
        if ( (i-j==k) && ( T[i-1].first == T[j].first ) && ( T[i-1].second < minim ) )
            minim=T[i-1].second;
        while ( ( T[i].first == T[j].first ) && ( i<n ) )
            i++;
    }
    if ( minim == INF )
        cout<<"-1";
    else
        cout<<minim-k;
    return 0;
}
