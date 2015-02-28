#include <fstream>

using namespace std;
int main(){
	ifstream in("cartonase.in");
	ofstream out("cartonase.out");
	int t,i,ind,n;
	char c;
	in>>t;
	while( t-- ){
		ind=0;
		in>>n;
		for( i=1; i<=n; ++i ){
			in>>c;
			if( c == 'R' )
				ind ^= i;
		}
		if( ind )
			out<<"DA\n";
		else
			out<<"NU\n";
	}
	return 0;
}
