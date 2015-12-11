#include <iostream>
#include <fstream>
#include <algorithm>
#include <deque>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <cmath>
#include <map>
#include <set>
#include <string>


#define per pair<int,int>
#define mp make_pair
#define pb push_back
#define DN 100005
#define DM 1000
using namespace std;

ifstream f("date.in");
ofstream out("date.out");

int n,m,radn,aa,bb;
bool val[DN],buk[DM],full[DM];

int get_bucket(int x){

    return (x/radn) + 1;
}

int left(int x){

    int p = (x-1)*radn;
    return max(p,1);
}
int right(int x){

    return x*radn - 1;
}

void check(int bucket){

    bool x = val[ left(bucket) ];
    full[ bucket ] = true;

    for(int i = left(bucket); i<=right(bucket) && i<=n; ++i)
        if( val[i] != x )
            full[ bucket ] = false;
}

void update(int st,int dr){


    for(int i = get_bucket(st) ; i<= get_bucket(dr); ++i){

        int bucket = i;

        if( left(bucket) < st && st <= right(bucket) ){

            for(int i= st ; i<= min( dr , right(bucket)) && i<=n ;++i)
                val[i] = !val[i];
            check(bucket);
        }
        else
            if(left(bucket) <= dr && dr < right(bucket)){

                for(int i = max( left(bucket) , st ) ; i<=dr && i<=n; ++i)
                    val[i] = !val[i];

                check(bucket);
            }
            else
                buk[i] = !buk[i];
    }
}

int val_buc(int bucket){

    int rez = val[ left(bucket) ];
    if( buk[ bucket ])
        rez = !rez;
    return rez;
}

int val_poz(int poz){

    int rez = val[poz];
    if( buk[ get_bucket(poz) ] )
        rez = !rez;
    return rez;
}

int query(int poz){

    int x = val_poz(poz);

    aa = get_bucket(poz) , bb = get_bucket(poz) ;

    for( ; full[ bb ] && val_buc(bb) == x && right(bb)<=n ; ++bb);
    for( ; full[ aa ] && val_buc(aa) == x && left(aa)>=1 ; --aa);


    if( get_bucket(poz) == aa )
        aa = poz;
        else
            aa = left( aa + 1);

    if( get_bucket(poz) == bb)
        bb = poz;
        else
            bb = right( bb - 1);

    for( ; val_poz(bb) == x && bb<=n ; ++bb); --bb;
    for( ; val_poz(aa) == x && aa>=1 ; --aa); ++aa;

    return x;
}


void read(){

    f>>n>>m;
    radn = sqrt(n);

    for(;m--;){

        int op;
        f>>op;
        if(op == 1){

            int a,b;
            f>>a>>b;
            update(a,b);
        }
        else{

            int p;
            f>>p;
            out<<query(p);
            out<<" "<<aa<<" "<<bb<<"\n";
        }
    }
    out.close();
    f.close();
}


int main()
{
    read();

    return 0;
}
