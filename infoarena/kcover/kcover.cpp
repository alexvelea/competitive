#include <cstdio>

#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;


ifstream in("kcover.in");
ofstream out("kcover.out");

#define MaxChar 10000000
#define verf ( (++CharB==MaxChar) ? ( in.read(Buffer,MaxChar),CharB=0 ) : (1) )

long CharB=MaxChar-1;
char Buffer [ MaxChar ];

void cit ( int &a )
{
    bool ok=0;
    for ( ; !( (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9') || ( Buffer[ CharB ] == '-' ) ); verf )
        ;
    if ( Buffer[ CharB ] == '-' ){
        CharB++;
        ok=1;
    }
    for ( a=0; (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9'); a*=10,a+=( Buffer[ CharB ]-'0'), verf )
        ;
    if ( ok ){
        a=-a;
    }
}


vector<int> Nr;
vector<unsigned int> Dif;
int t,n,k,i,a;

int main(){

	verf;

	cit(t);
	for ( ; t; --t ){
		cit(n);
		cit(k);
		k--;
		for ( i=1; i<=n; ++i ){
			cit ( a );
			Nr.push_back ( a );
		}
		sort ( Nr.begin(), Nr.end() );
		for ( i=0; i<int ( Nr.size()-1 ); ++i ){
			Dif.push_back ( (unsigned int)  Nr[i+1]-Nr[i] );
		}
		sort ( Dif.begin(), Dif.end() );
       	unsigned int s=0;
		for ( i=0; i+k< Dif.size(); ++i ){
			s+=Dif[i];
		}
		out<<s<<"\n";
		Dif.clear();
		Nr.clear();
	}
	return 0;
}
