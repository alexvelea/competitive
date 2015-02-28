#include <cstdio>
#include <cstring>
#include <fstream>
using namespace std;

ifstream in("kbiti.in");
ofstream out("kbiti.out");

unsigned int Pre[40],rez;
int i,j,B[40],t,n,nr;
char Text[ 40 ];
 
int main(){
    for ( i=0; i<=32; ++i ){
        Pre[i] = (1LL<<i);
    }
 	in>>t;
    for ( ; t; --t ){
		in>>Text;
        n=strlen( Text );
        rez=0;
		nr=0;
        for ( i=0; i<n; ++i ){
            if ( Text[ i ] == '1' ){
                rez |= Pre[ n-i-1 ];
				nr++;
			}
        }
		rez++;
		if( nr == 32 )
			out<<4294967296<<"\n";
        else
			out<<rez<<"\n";
    }
 
    return 0;
}
