#include <fstream>
using namespace std;

	#define max_n 500005

	ifstream in("reguli.in");
	ofstream out("reguli.out");

long long Number[ max_n ];
int n,i,Rez,Prefix[ max_n ];

void prefix (){
	Prefix[ 0 ] = Prefix[ 1 ] = 0;
	int k=0,i=0;
	for ( i=2; i<=n; ++i ){
		while ( k && Number[ k+1 ] != Number[ i ] ){
			k = Prefix[ k ];
		}
		if ( Number[ i ] == Number[ k+1 ] ){
			++k;
		}
		Prefix[ i ] = k;
	}
	Rez = n - Prefix[ n ];
}


int main(){
    in>>n;
	n--;
	for ( i=0; i<=n; ++i ){
		in>>Number[i];
	}
	for ( i=n; i>=1; --i ){
		Number[i] -= Number[ i-1 ];
	}
	prefix();
	out<<Rez<<"\n";
	for ( i=1; i<=Rez; ++i ){
		out<<Number[i]<<"\n";
	}
	return 0;
}
