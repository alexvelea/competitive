/*
    Velea Alexandru, clasa a 10-a, ICHB
    100 de puncte la judeteana.
    Calificat in lot in clasa a 9-a
*/
 
#include<cassert>
#include<algorithm>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
 
ifstream in("showroom.in");
ofstream out("showroom.out");
 
#define FORIT( it,v ) for( auto it=(v).begin(); it!=(v).end(); ++it )
const int max_n=505, sigma=41, MOD1=49941491, MOD2=(1<<24), ModRez=9001;
 
int n,a,r,k;
int i,j,l;
 
string Linie;
int Nr[max_n]; // cate masini are dealerul i
int Father[max_n];
 
int Fact[50005], InvFact[50005];
 
struct trio{
    int h1,h2,ind;
    trio(){
        h1=h2=ind=0;
    }
    trio( int _h1, int _h2, int _ind ){
        h1=_h1;
        h2=_h2;
        ind=_ind;
    }
    bool operator < ( const trio b ) const {
        if( h1 == b.h1 )
            return h2<b.h2;
        return h1<b.h1;
    }
};
vector <trio> Sir;
 
int encode( char c ){
    if( c>='a' && c<='z' )
        return c-'a'+1;
    return c-'0'+27;
}
 
int get_father( int nod ){
    if( nod != Father[nod] )
        Father[nod] = get_father( Father[nod] );
    return Father[nod];
}
 
void set_father( int nod, int target ){
    if( nod == Father[nod] )
        ;
    else
        set_father( Father[nod], target );
    Father[nod]=target;
}
 
int calc( int a ){
    return a/ModRez;
}
 
int comb( int n, int k ){
    if( calc(n) - calc(k) - calc( n-k ) )
        return 0;
    return (1LL*((1LL*Fact[n]*InvFact[n-k])%ModRez)*InvFact[k])%ModRez;
}
 
int pow( int a, int p ){
    int rez=1;
    while( p ){
        if( p&1 )
            rez=(rez*a)%ModRez;
        a=(a*a)%ModRez;
        p/=2;
    }
    return rez;
}
 
int main(){
 
    // facem combinarile 
    Fact[0]=Fact[1]=1;
    for( i=2; i<50005; ++i ){
        if( i%ModRez!=0 )
            Fact[i]=(1LL*i*Fact[i-1])%ModRez;
        else
            Fact[i]=(1LL*i*Fact[i-1]/9001)%ModRez;
    }
    InvFact[50004]=pow(Fact[50004],ModRez-2);
    for( i=50003; i; --i ){
        if( (i+1)%ModRez )
            InvFact[i]=(1LL*InvFact[i+1]*(i+1))%ModRez;
        else
            InvFact[i]=(1LL*InvFact[i+1]*(i+1)/ModRez)%ModRez;
    }
    InvFact[1]=InvFact[0]=1;
    // terminal preprocesarea la combinari -> O(n)
 
    in>>n>>a>>r>>k;
    getline( in, Linie ); // scapam de linia goala
    for( i=1; i<=n; ++i ){
        getline( in, Linie );
        int h1,h2;
        for( j=0; j<int(Linie.size()); ++j ){
            if( Linie[j]!=' ' ){
                h1=0;
                h2=0;
                while( j<int(Linie.size()) && Linie[j]!=' ' ){
                    h1*=sigma;
                    h1+=encode(Linie[j]);
                    h1%=MOD1;
 
                    h2*=sigma;
                    h2+=encode( Linie[j] );
                    h2%=MOD2;
                    j++;
                }
                Sir.push_back( trio( h1, h2, i ) );
            }
        }
    }
    for( i=1; i<=n; ++i )
        Father[i]=i;
    sort( Sir.begin(), Sir.end() );
 
    // punem dealari impreuna
    for( i=0; i<int(Sir.size()); ){
        j=i;
        while( j<int(Sir.size()) && Sir[i].h1 == Sir[j].h1 && Sir[i].h2 == Sir[j].h2 )
            ++j;
        int mn=n+1;
        for( l=i; l<j; ++l ){
            mn=min( mn, get_father( Sir[l].ind ) );
        }
        for( ; i<j; ++i ){
            set_father( Sir[i].ind, mn );
        }
    }
    for( i=1; i<=n; ++i )
        get_father(i);
    // adaugam masinile la dealari
    for( i=0; i<int(Sir.size());  ){
        j=i;
        Nr[ get_father( Sir[i].ind ) ]++;
        while( j<int(Sir.size()) && Sir[i].h1 == Sir[j].h1 && Sir[i].h2 == Sir[j].h2 )
            ++j;
        i=j; 
    }
    // debug
/*  cerr<<"Nr Elemente ->\n";
    for( i=1; i<=n; ++i )
        cerr<<i<<"#\t"<<Nr[i]<<"\n";
    cerr<<"\n\nFather->\n";
    for( i=1; i<=n; ++i )
        cerr<<i<<"#\t"<<Father[i]<<"\n";*/
    //
    a%=k;
    r%=k;
    int rez=0;
    for( i=1; i<=n; ++i )
        if( Nr[i]>0 )
            rez++;
    out<<rez<<"\n";
    rez=1;
    for( i=1; i<=n; ++i ){
        if( Nr[i] ){                
            if( Nr[i]>=a ){
                rez*=comb(Nr[i],a);
                rez%=ModRez;
            }
            a+=r;
            a-=k;
            if( a<0 )
                a+=k;
        }
    }
    out<<rez<<"\n";
    return 0;
}
