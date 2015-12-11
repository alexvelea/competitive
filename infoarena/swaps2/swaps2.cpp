#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
    
    vector<int> Rez;
    int a,b,n;
    char Text[1005];

int main(){

        freopen ("swaps2.in","r",stdin);
        freopen ("swaps2.out","w",stdout);

    cin>>n;
    cin>>Text;
    for ( a=0,b=n-1; a<b; ){
        while ( ( Text[a] == '0' ) && ( a<n ) ){
            a++;
        }
        while ( ( Text[b] == '1' ) && ( b>0 ) ){
            b--;
        }
        if ( a < b ){
            Rez.push_back(a+1);
            Rez.push_back(b+1);
        }
        a++;
        b--;
    }
    printf("%d\n", Rez.size()/2);
    for ( int i=1,j=0; i<=Rez.size()/2; i++ ){
        printf("%d %d\n", Rez[j++], Rez[j++] );
    }
    return 0;
}
