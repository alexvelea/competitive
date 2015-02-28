#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

    #define INF 0x3f3f3f3f
    #define fi first
    #define se second
    #define pb push_back
    #define max_val 10000000
    #define zs 10000000

    vector<int> Div[max_val];
    bool V[max_val];

    vector<int> RezA,RezB;
    vector<int> :: iterator it;
    int Count[max_val];

    long long  i,j,l;
    int n,m,aux,last_a,last_b;

int main()
{

    for ( i=2; i<max_val; i++ )
    {

        if ( !V[i] )
        {
            V[i]=1;
            for ( j=i*i; j<max_val; j+=i )
                V[j]=1;
            // introducel divizorii

            for ( l=i; l<max_val; l*=i )
            {

                for ( j=l; j<max_val; j+=l )
                {
                    Div[j].pb(i);
                }
            }
        }
    }
    printf("GATAPENIS!");
    scanf ("%d %d", &n, &m);
    for ( i=1; i<=n; i++ )
    {
        scanf ("%d", &aux);
        for ( it=Div[aux].begin(); it!=Div[aux].end(); it++ )
            Count[*it]++;
    }
    for ( i=1; i<=m; i++ )
    {
        scanf ("%d", &aux);
        for ( it=Div[aux].begin(); it!=Div[aux].end(); it++ )
            Count[*it]--;
    }

    last_a=1;
    last_b=1;

    for ( i=1; i<max_val; i++ )
    {
        if ( Count[i] > 0 )
        {
            while ( Count[i]>0 )
            {
                if ( ( last_a*i ) <= zs )
                {
                    last_a*=i;
                }
                else{
                    RezA.pb(last_a);
                    last_a=i;
                }
                Count[i]--;
            }
        }
        if ( Count[i] < 0 )
        {
            while ( Count[i]<0 )
            {
                if ( ( last_b*i ) <= zs )
                {
                    last_b*=i;
                }
                else{
                    RezB.pb(last_b);
                    last_b=i;
                }
                Count[i]++;
            }
        }
    }
    RezB.pb(last_b);
    RezA.pb(last_a);

    printf("%d %d\n", RezA.size(),RezB.size() );
    for ( i=0; i<RezA.size(); i++ )
        printf("%d ",RezA[i]);
    printf("\n");
    for ( i=0; i<RezB.size(); i++ )
        printf("%d ",RezB[i]);
    printf("\n");
    return 0;
}

