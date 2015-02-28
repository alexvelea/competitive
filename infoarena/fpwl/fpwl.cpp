#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

    #define max_val 1000005
    #define max_n   500005
    #define fi first
    #define se second


    int n,k;
    int i;
    int Nr[max_n], Sign[max_n];
    int maxim=-1,poz;

    pair<int,int> Best[max_val];
    pair<int,int> P[3][max_n];
    pair<int,int> Arb[2][max_val];
    /*
        0 <
        1 >
        2 = 
    */

void update ( int nr, int rez, int poz, int arb ){
    for ( ; nr<max_val; nr+=nr&(-nr) )
        if ( Arb[arb][nr].fi <= rez ){
            Arb[arb][nr]=make_pair(rez,poz);
        }
    return ;
}

void upd ( int nr, int poz, int ind ){
    if ( Sign[ind] == 0 ){
        update ( nr, ind, poz, 0);
        return ;
    }
    if ( Sign[ind] == 1 ){
        update ( max_val-nr, ind, poz, 1 );
        return ;
    }
    if ( Best[nr].fi < ind ){
        Best[nr]=make_pair(ind,poz);
    }
    return ;
}

pair <int,int> query ( int nr, int arb ){
    pair <int,int> R;
    R.fi=R.se=0;
    for ( ; nr; nr-=nr&(-nr) )
        if ( Arb[arb][nr].fi > R.fi )
            R=Arb[arb][nr];
    return R;
}
int main(){

        freopen ("fpwl.in","r",stdin);
        freopen ("fpwl.out","w",stdout);

    scanf ("%d %d", &n, &k );
    for ( i=1; i<=n; i++ ){
        scanf ("%d", &Nr[i] );
    }
    for ( i=1; i<=k; i++ ){
        char c;
        cin>>c;
        if ( c == '=' )
            Sign[i]=2;
        if ( c == '<' )
            Sign[i]=0;
        if ( c == '>' )
            Sign[i]=1;
    }
    int j;
    for ( i=k+1, j=1; i<=n; ++i,++j ){
        if ( j == k+1 )
            j=1;
        Sign[i]=Sign[j];
    }
    for ( i=1; i<=n; i++ ){
        // rezolvam pentru elementul 0
        // avem < in fata lui Nr[i] 
        pair <int,int> Rez1=make_pair(0,0), Rez2=make_pair(0,0), Rez3=make_pair(0,0);
        // query ( st, dr, lim_inf, lim_sup, nod );
        if ( Nr[i] > 1 ){
            Rez1 = query ( Nr[i]-1, 0 );
            P[0][i] = Rez1;
   
            if ( Rez1.fi > maxim ){
                maxim=Rez1.fi;
                poz=i;
            }
        }
        // cazul 1 -> '>' in fata lui Nr[i]
        Rez2 = query ( max_val-Nr[i]-1, 1 );
        P[1][i] = Rez2;
    
        if ( Rez2.fi > maxim ){
            maxim=Rez2.fi;
            poz=i;
        }
        // cazul 2 -> '='
        Rez3 = Best[ Nr[i] ];
        P[2][i] = Rez3;

        if ( Rez3.fi > maxim ){
            maxim=Rez3.fi;
            poz=i;
        }
        upd ( Nr[i], i, Rez1.fi+1 );
        upd ( Nr[i], i, Rez2.fi+1 );
        upd ( Nr[i], i, Rez3.fi+1 );

    }
    printf("%d\n",maxim+1);
    vector<int> Rez;
    maxim++;

    while ( poz!=0 ){
        maxim--;
        Rez.push_back(poz);
        for ( i=0; i<3; i++ ){
            if ( P[i][poz].fi == maxim ){
                poz = P[i][poz].se;
                break;
            }
        }
    }
    for ( i=Rez.size()-1; i>=0; i-- )
        printf("%d ",Nr[Rez[i]]);
    return 0;
}
