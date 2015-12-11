#include <cstdio>
#include <iostream>
using namespace std;

    #define max_n 100005
    int n,i,j,a,T[max_n],Poz[max_n];
    int Viz[max_n],start,size;
    int s;

int main()
 {
   freopen ("intersort.in","r",stdin);
   freopen ("intersort.out","w",stdout);

    scanf ("%d", &n );
    for ( i=1; i<=n; i++ )
    {
        scanf ("%d", &a );
        Poz[a]=i;
        T[i]=a;
        if ( a!=i )
            s++;
    }
    if ( Poz[1]!=1 )
        s-=2;
    // cautam componentele conexe 
    for ( i=1; i<=n; i++ )
    {
        if ( !Viz[i] && i!=T[i] )
        {
            j=i;
            start=j;
            size=0;
            do{
                Viz[j]=1;
                j=T[j];
                size++;
            }while ( start!=j );
            if ( i==2 && size==2 )
                s--;
            s++;
/*            for ( j=1; j<=n; j++ )
                printf("%d ",Viz[j]);
            printf("\n");*/
        }

    }
    printf("%d",s);

    
    return 0;
}
