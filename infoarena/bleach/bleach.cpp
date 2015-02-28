#include <cstdio>
#include <queue>
using namespace std;

    priority_queue<int> pq;
    int n,k,i,s,t,a;
    long long act;

int main(){
        freopen ("bleach.in","r",stdin);
        freopen ("bleach.out","w",stdout);
    
    scanf ("%d %d", &n, &k );
    for ( i=1; i<=n && i<=2*k; i++ ){
        scanf ("%d", &a );
        pq.push(-a);
    }
    s=0;
    act=0;
    for ( i=2*k+1; i<=n; i++ ){
        // actualizam
        t=pq.top();
        pq.pop();
        t*=-1;
        if ( act < t ){
            s+=(t-act);
            act=t;
        }
        act+=t;
        scanf ("%d", &a);
        pq.push(-a);
    }
    // scoatem tot ce a ramas ...
    while ( !pq.empty() ){
        t=pq.top();
        pq.pop();
        t=-t;
        if ( act < t ){
            s+=(t-act);
            act=t;
        }
        act+=t;
    }
    printf("%d", s);
    return 0;
}
