#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

    #define max_m 100005
    #define max_n 15005

    #define fi first
    #define se second
    #define pb push_back
    #define mp make_pair


    typedef struct { int a,b,c,ma,mb; } Muchie;
    Muchie Mu[max_m];

    vector <int> T[max_n];
    vector <int> rez;


    int a,b,c,i,j,n,m,t;

        int It[max_n];
        bool Viz_m[max_m];

    bool mysort ( int a , int b )
    {
        return Mu[ a ].c < Mu[ b ].c ;
    }

    void  perechi ( int nod )
    {
        int dest,c=0 ,i,j,maxim=0;

        sort ( T[nod].begin(), T[nod].end() , mysort );

        for ( i=0; i< int ( T[nod].size() ); )
        {
            j=i;
            while ( ( i<T[nod].size() ) && ( Mu[ T[nod][i] ].c == Mu[ T[nod][j] ].c ) )
            {
                i++;
            }

            if ( i-j > maxim )
            {
                maxim=i-j;
                c=Mu[ T[nod][j] ].c ;
            }
        }
//        printf ("   - %d %d\n",poz,maxim);
        dest= T[nod].size() - 2 * maxim;
        dest/=2;

        if ( dest < 0 )
        {
            // no solution
        }
        i=0;

        int st,dr;
        st=0;
        dr=T[nod].size()-1;

        while ( dest )
        {
            while ( Mu[ T[nod][st] ].c  == c )
                st++;
            while ( Mu[ T[nod][dr] ] .c  == c )
                dr--;
                      
            if ( Mu[ T[nod][st] ].a == nod )
                Mu[ T[nod][st] ].ma = T[nod][dr];
            else
                Mu[ T[nod][st] ].mb = T[nod][dr];

            if ( Mu[ T[nod][dr] ].a == nod )
                Mu[ T[nod][dr] ].ma = T[nod][st];
            else
                Mu[ T[nod][dr] ].mb = T[nod][st];
  //          printf("   ---   %d %d\n", T[nod][st], T[nod][dr] );
            dest--;
            st++;
            dr--;
        }
        j=0;
        while ( Mu[ T[nod][j] ].c != c )
            j++;

        for ( i=st; i<=dr; i++ )
        {
            if ( Mu[ T[nod][i] ].c != c )
            {
    //            printf ("  BUG -  %d %d\n", Mu[ T[nod][i] ].c, Mu[ T[nod][j] ].c );
//                printf("  %d %d             %d %d\n", i,j,T[nod][i], T[nod][j] );
                if ( Mu[ T[nod][i] ].a == nod )
                    Mu[ T[nod][i] ].ma = T[nod][j];
                else
                    Mu[ T[nod][i] ].mb = T[nod][j];

                if ( Mu[ T[nod][j] ].a == nod )
                    Mu[ T[nod][j] ].ma = T[nod][i];
                else
                    Mu[ T[nod][j] ].mb = T[nod][i]; 
                j++;
            }
        }
//        printf("\n\n");
    }

    void solve_nod ( int, int, int );

    void euler ( int muchie, int nod, int stop )
    {
        Viz_m[ muchie ]=1;   
        int muchie_next,nod_next;

        if ( muchie == stop )
        {
            rez.pb( nod );
            return ;
        }

        if ( nod == Mu[ muchie ].a )
            muchie_next = Mu[ muchie ].ma;
        else
            muchie_next = Mu[ muchie ].mb;

        nod_next = Mu[ muchie_next ].a + Mu[ muchie_next ].b - nod;
        euler ( muchie_next, nod_next, stop );
        solve_nod ( Mu[ muchie_next ].c , Mu[ muchie ].c , nod );
        rez.pb(nod);
    }

    void solve_nod ( int start, int finish , int nod )
    {
//        printf("\n-%d %d\n", start, finish );
        for ( ; It[nod] < int ( T[nod].size() ); )
        {
            #define it It[nod]
            int aux_it=it;
            it++;
            if ( !Viz_m[ T[nod][aux_it] ] )
            {
                if ( nod == Mu[ T[nod][aux_it] ].a )
                {
                    if ( finish != Mu[ T[nod][aux_it] ].c && start != Mu [ Mu[ T[nod][aux_it] ].ma ].c)
                    {
                        euler ( T[nod][aux_it] , Mu[ T[nod][aux_it] ].b , Mu[ T[nod][aux_it] ].ma ); 
                        start = Mu[ Mu [ T[nod][aux_it] ].ma ].c;
                    }
                    else
                    {
                        euler ( Mu[ T[nod][aux_it] ].ma , ( Mu[ Mu[ T[nod][aux_it] ].ma ].a + Mu[ Mu[ T[nod][aux_it] ].ma ].b - nod ) , T[nod][aux_it] );                    
                        start = Mu[ T[nod][aux_it] ].c;
                    }
                }
                else
                {
                    if ( finish != Mu [ T[nod][aux_it] ].c && start != Mu [ Mu[ T[nod][aux_it] ].mb ].c )
                    {
                        euler ( T[nod][aux_it] , Mu[ T[nod][aux_it] ].a , Mu[ T[nod][aux_it] ].mb );
                        start = Mu[ Mu[ T[nod][aux_it] ].mb ].c;
                    }
                    else
                    {
                        euler ( Mu [ T[nod][aux_it] ].mb , ( Mu [ Mu[ T[nod][aux_it] ].mb ].a + Mu[ Mu[ T[nod][aux_it] ].mb ].b - nod ) , T[nod][aux_it] );
                        start = Mu[ T[nod][aux_it] ].c;
                    }
                }

            }
        }
    }

    void solve ( )
    {
        // facem perechiile
        for ( int i=1; i<=n; i++ )
            perechi ( i );
/*        for ( i=1; i<=m; i++ )
            printf ("i-%d       %d     %d \n", i,Mu[i].ma, Mu[i].mb );*/
        // facem intrarea.
        if ( Mu[ T[1][0] ].a == 1 )
        {
            euler ( T[1][0], Mu[ T[1][0] ].b, Mu[ T[1][0] ].ma );
            solve_nod ( Mu[T[1][0]].c ,  Mu [ Mu [ T[1][0] ].b ].c , 1 );
        }
        else{
            euler ( T[1][0], Mu[ T[1][0] ].a, Mu[ T[1][0] ].mb );
            solve_nod ( Mu [ T[1][0] ].c, Mu [ Mu[ T[1][0] ].a ].c, 1 );
        }
    }

int main()
{
    freopen ("ulei.in","r",stdin);
    freopen ("ulei.out","w",stdout);

    scanf ("%d", &t );
    for ( ; t; t-- )
    {
        scanf ("%d %d", &n, &m );
        for ( i=1; i<=m; i++ )
        {
            scanf ("%d %d %d", &a, &b, &c );
            Mu[i].c=c;
            Mu[i].a=a;
            Mu[i].b=b;

            T[a].pb( i );
            T[b].pb( i );
        }

        solve ( );

/*        for ( i=1; i<=m; i++ )
            printf(" i )%d      %d %d c - %d        %d  %d\n", i, Mu[i].a, Mu[i].b, Mu[i].c, Mu[i].ma, Mu[i].mb );*/
/*        for ( i=0; i<rez.size(); i++ )
            printf("%d - ", rez[i]);*/
        for ( i=0; i<rez.size(); i++ )
            printf("%d ",rez[i]);
        printf("1");
        printf("\n");
        rez.erase ( rez.begin(), rez.end() );
        for ( i=1; i<=m; i++ )
            Viz_m[i]=0;
        for ( i=1; i<=n; i++ )
        {
            T[i].erase ( T[i].begin(), T[i].end() );
            It[i]=0;
        }
    }
    return 0;
}
