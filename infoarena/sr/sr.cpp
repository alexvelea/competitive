#include <cstdio>
#include <cstring>
using namespace std;

    #define max_n 200000
    char a[max_n],b[max_n];
    int i,j;

int main(){

    freopen ("sr.in","r",stdin);
    freopen ("sr.out","w",stdout);

    scanf ("%s", &a);
    scanf ("%s", &b);

    int n=strlen(a),m=strlen(b);

    for ( i=0; i<m; i++ ){
        while ( ( a[j]!=b[i] ) && ( j<n ) ){
            j++;
        }
        printf("%d ",j+1);
        j++;
    }
    return 0;
}

