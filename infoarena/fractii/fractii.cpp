#include <cstdio>
#include <iostream>
using namespace std;
#define maxn 1001000
 
    long long V[maxn],Rez[maxn];
    long long n,i,j,l;
 
 
int main()
{
    freopen ("fractii.in","r",stdin);
    freopen ("fractii.out","w",stdout);
    scanf ("%d", &n);
 
    for ( i=1; i<=n; i++ )
        Rez[i]=1;
	long long rez=0;
    for ( i=2; i<=n; i++ )
    {
        if ( !V[i] )
        {
            for ( j=1LL*i*i; 1LL*j<=1LL*n; j+=i ){
//				assert( j<maxn );
                V[j]=1;
			}
            for ( j=i; 1LL*j<=1LL*n; j+=i ){
//				assert( j< maxn );
                Rez[j]*=(i-1);
			}
            for ( l=1LL*i*i; 1LL*l<=1LL*n; l*=i )
                for ( j=l; 1LL*j<=1LL*n; j+=l ){
//					assert( j<maxn );
                    Rez[j]*=i;
				}
        }
    }
    if ( !n )
    {
        printf("0");
        return 0;
    }
    for ( i=2; i<=n; i++ )
        rez+=(long long)Rez[i];
	rez<<=1;
    rez++;
    cout<<rez<<"\n";
    return 0;
}
