#include <cstdio>
#include <iostream>
using namespace std;

    #define INF 0x3f3f3f3f
    #define ln 50

    int n,i,j;
    long long minim=(long long)INF*INF,a,b, Pow[ln+5];

    struct ceva {
        long long el[ln+5];
    } act,inf,last;

    long long min ( long long a , long long b ){
        if ( a<b )
            return a;
        return b;
    }

int main(){
    /*

        freopen ("hacker3.in","r",stdin);
        freopen ("hacker3.out","w",stdout);

    */
    for ( i=0; i<=ln; i++ )
        inf.el[i]=(long long)INF*INF;
    Pow[0]=1;
    for ( i=1; i<=ln; i++ )
        Pow[i]=(long long) Pow[i-1]*2;
    scanf ("%d", &n);
    for ( i=1; i<=n; i++ ){
        cin>>a>>b;
        act=inf;
        for ( j=0; j<=ln; j++ ){
            if ( b <= (long long) ( (100000*2000000000) - last.el[j] ) / Pow[j] )
            act.el[j]=min( act.el[j], Pow[j]*b  +last.el[j] );
            if ( j>0 )
                if ( a <= ( (long long) ( (100000*2000000000) - last.el[j-1] ) / Pow[j-1]  ) )
                    act.el[j]=min( act.el[j], Pow[j-1]*a  + last.el[j-1] );
            cout<<act.el[j]<<"\n";
        }
        last=act;
    }
    minim=(long long)INF*INF;
    for ( i=0; i<=ln; i++ ){
        if ( minim > act.el[i] )
            minim=act.el[i];
    }
    cout<<minim<<"\n";
    return 0;
}

