#include <fstream>
using namespace std;

int a,b,c;

int gcd ( int a, int b ){
	if ( !b ){
		return a;
	}
	return gcd ( b, a%b );
}

int search ( int val ){
	if ( val == 1 ){
		return 0;
	}
	int i,rez=0,c=val;
    for ( i=2; i*i<=c; ++i ){
		if ( val%i == 0 ){
        	rez++;
			while ( val%i == 0 )
				val/=i;
		}
	}
	if ( val != 1 ){
		rez++;
	}
	return rez;
}

int main(){

	ifstream in("divmul.in");
	ofstream out("divmul.out");
int t;
in>>t;
for ( ; t; --t ){
    in>>a>>b;
	int c = gcd ( a,b );
	a/=c;
	b/=c;
	int nr=0;
	nr+=search ( a );
	nr+=search ( b );
	out<<(1<<nr)<<"\n";
}
	return 0;
}
