#include <cstdio>
using namespace std;

    #define max_nr_cif 25000

    typedef struct { int Cif[max_nr_cif],nrcif; } NumaruMare;
    NumaruMare ab,ba;
    int a,b;

    NumaruMare to_mare ( int a )
    {
        NumaruMare c;
        c.nrcif=0;
        while ( a )
        {
            c.Cif [ ++c.nrcif ]=a%10;
            a/=10;
        }
        return c;
    }

    NumaruMare scadere ( NumaruMare a, NumaruMare b )
    {
        for ( int i=1; i<=a.nrcif || i<=b.nrcif; i++ )
        {
            a.Cif[i]-=b.Cif[i];
            if ( a.Cif[i] < 0 )
            {
                a.Cif[i]+=10;
                a.Cif[i+1]--;
            }
        }
        return a;
    }

    NumaruMare inmultire ( NumaruMare a, NumaruMare b )
    {
        NumaruMare c;
        int i,j,t;

        for ( i=1; i<= 2* ( a.nrcif + b.nrcif ) && i<max_nr_cif; i++ )
            c.Cif[i]=0;
        for ( i=1; i<=a.nrcif; i++ )
            for ( j=1; j<=b.nrcif; j++ )
                c.Cif[i+j-1]+=a.Cif[i]*b.Cif[j];
        for ( i=1,t=0; ( i< ( a.nrcif+b.nrcif ) ) || t; i++ )
        {
            c.nrcif++;
            c.Cif[i]+=t;
            t=c.Cif[i]/10;
            c.Cif[i]%=10;
        }
        return c;
    }

        void afisare ( NumaruMare a )
    {
        for ( int i=a.nrcif; i>0; i-- )
            printf("%d", a.Cif[i] );
        printf("\n");
    }

    NumaruMare pow ( NumaruMare a, int p )
    {
        printf("%d - ",p);
        afisare ( a );
        if ( p==1 )
            return a;

        if ( p&1 )
            return inmultire ( a , pow ( inmultire ( a,a ) , p/2 ) );
        else
            return pow ( inmultire ( a,a ) , p/2 );
    }

int main()
{
    scanf ("%d %d", &a, &b );
    ab = to_mare ( a );
    ba = to_mare ( b );

    ab=pow ( ab, b );
    ba=pow ( ba, a );



    ab=scadere ( ab,ba );

    return 0;
}
