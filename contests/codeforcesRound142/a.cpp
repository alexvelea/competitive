#include <cstdio>
using namespace std;
#define INF 0x3f3f3f3f
#define maxn 105
#define maxm 10005
#define min(a,b) ((a<b)?(a):(b))

    char c;
    bool In[maxn][maxm];
    int n,m,i,j,minim,St[maxm],Dr[maxm],Rez[maxm],ok=1;

int main()
{
    scanf ("%d %d", &n, &m );
    for ( i=0,j=0; i<n; )
    {
        scanf ("%c", &c );
        if ( (c=='0') || (c=='1'))
        {
            In[i][j]=c-'0';
            j++;
            if ( j==m )
            {
                j=0;
                i++;
            }
        }
    }
    for ( i=0; i<n; i++ )
    {
        for ( j=0; j<m; j++ )
            St[j]=Dr[j]=INF;
        minim=INF;
        for ( int l=0,j=0; l<=2*m; l++ )
        {
            minim++;
            if ( In[i][j]==1 )
                minim=0;
            St[j]=min( St[j], minim) ;
            j--;
            if ( j == -1 )
                j=m-1;
        }
        minim=INF;
        for ( int l=0,j=0; l<=2*m; l++ )
        {
            minim++;
            if ( In[i][j]==1 )
                minim=0;
            Dr[j]= min ( Dr[j], minim) ;
            j++;
            if ( j == m )
                j=0;
        }
        if ( minim >= INF )
            ok=0;
        for ( j=0; j<m; j++ )
            Rez[j]+=min( St[j], Dr[j] );
    }
    minim=INF;
    for ( j=0; j<m; j++ )
        if ( minim > Rez[j] )
            minim=Rez[j];
    if ( ok )
        printf("%d\n",minim);
    else
        printf("-1");
    return 0;
}
