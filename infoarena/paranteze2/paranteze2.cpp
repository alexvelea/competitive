#include<cstdio>
#include<cstring>
using namespace std;

    #define max_n 1000005

    int n,i,lev;
    int P[max_n],Nr[max_n];
    char T[max_n];
    long long rez;
    
int main(){

        freopen ("paranteze2.in","r",stdin);
        freopen ("paranteze2.out","w",stdout);

    scanf ("%s", &T );
    n=strlen(T);
    for ( i=0; i<=n; i++ ){
        if ( T[i]=='(' ){
            P[i]=1;
        }
        else{
            P[i]=0;
        }
    }
    lev=0;
    for ( i=0; i<n; i++ ){
        if ( P[i] == 1 ){
            Nr[lev]++;
            lev++;
        }
        else{
            if ( lev > 0 )
                rez+=Nr[lev-1];
            Nr[lev]=0;
            lev--;
            if ( lev < 0 ){
                lev=0;
            }
        }
    }
    printf("%lld",rez);
    return 0;
}

