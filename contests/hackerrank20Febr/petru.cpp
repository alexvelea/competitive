#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define LL long long
#define MOD 1000000007
#define DN 100005
using namespace std;

long long n,m,a[DN],b[DN];

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t;
    for(cin>>t;t--;) {
        cin>>n>>m;
        for(int i=1; i<n; ++i) cin>>a[i];
        for(int i=1; i<m; ++i) cin>>b[i];
        sort(a+1,a+n);
        sort(b+1,b+m);
        reverse(a+1,a+n);
        reverse(b+1,b+m);
        long long rez=0;
        for(LL i=1,j=1;i<n || j<m;) {
            if(i==n || (a[i]<b[j] && j<m)) {
                rez+=b[j]*i;
                ++j;
            }else {
                rez+=a[i]*j;
                ++i;
            }
            rez%=MOD;
        }
        cout<<rez<<'\n';
    }
    return 0;
}
