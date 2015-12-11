#include <cstdio>
#include <iostream>

using namespace std;

    #define MOD 1000000007
    typedef struct{ long long E[55][55]; } Mat;

    int codif ( char a )
    {
        if ( a>='a' && a<='z' )
            return a-'a'+1;
        if ( a>='A' && a<='Z' )
            return 26+a-'A'+1;
        return -1;
    }

    Mat Act[70];

    long long m,k,i,j;
    long long M[55][55];
    long long A,B;
    char a,b;
    long long n;

    Mat MaI,F,Mat_empty;


Mat inm ( Mat a, Mat b )
{
    int i,j,k,l;
    Mat F;
    for ( i=1; i<=m; i++ )
    {
        for ( j=1; j<=m; j++ )
        {
            F.E[i][j]=0;
            for ( l=1; l<=m; l++ )
            {
                F.E[i][j]+= (long long) a.E[i][l]*b.E[l][j];
                F.E[i][j]%= MOD;
            }
        }
    }
    return F;
}

void show ( Mat a )
{
    int i,j;
    for ( i=1; i<=m; i++,printf("\n") )
        for ( j=1; j<=m; j++ )
            printf("%d ",a.E[i][j]);
    printf("\n\n");
}

Mat rid ( long long pow, int k )
{
/*    cout<<pow<<"\n";
    show ( Act );
    cout<<"\n\n\n\n\n\n\n";*/
    if ( pow == 1 )
        return Act[k];

    Act[k+1]=inm(Act[k],Act[k]);
    if ( pow&1 )
    {
        return inm ( Act[k], rid( pow/2, k+1 ) );
    }
    else
        return rid ( pow/2, k+1 );
}

int main()
{
    cin>>n>>m>>k;
    for ( i=1; i<=k; i++ )
    {
        A=-1;
        while( A==-1 )
        {
            scanf ("%c", &a);
            A=codif(a);
        }
        B=-1;
        while( B==-1 )
        {
            scanf ("%c", &b);
            B=codif(b);
        }
        M[B][A]=1;
    }
    n--;
    for ( i=1; i<=m; i++ )
        Mat_empty.E[i][i]=1;
    for ( i=1; i<=m; i++ )
    {
        for ( j=1; j<=m; j++ )
            MaI.E[i][j]=1^M[i][j];
    }

    Act[1]=MaI;
    if ( n )
        F=rid(n,1);
    else{
        printf("%d\n",m);
        return 0;
    }
    long long rez=0;
    for ( i=1; i<=m; i++ )
        for ( j=1; j<=m; j++ )
        {
            rez+=F.E[i][j];
            rez%=MOD;
        }
    cout<<rez;
    return 0;
}
