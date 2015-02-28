#include <cstdio>
#include <cstring>

#include <fstream>
#include <iostream>

using namespace std;

	ifstream in("prefix.in");
	ofstream out("prefix.out");

	#define max_n 1000005

string Pattern;
int Prefix[ max_n ];
int Number;
int n;

void solve (){
	Prefix[ 0 ] = Prefix[ 1 ] = 0 ;
	int k=0;
	for ( int i=2; i<=n; ++i ){
    	while ( ( k ) && ( Pattern[ k+1 ] != Pattern[ i ] ) )
			k = Prefix[k];
		if ( Pattern[ k+1 ] == Pattern[ i ] )
			k++;
		Prefix[ i ] = k;
	}

	for ( int i=n; i>0; --i ){
		if ( ( Prefix[ i ] ) && !( i % ( i-Prefix[ i ] ) ) ){
			out<<i<<"\n";
			return ;
		}
	}               
	out<<"0\n";
	return ;
}

void read (){
	in>>Number;
	while ( Number ) {
        in>>Pattern;
		n = Pattern.length();
		Pattern = " " + Pattern;
		solve();

		Number--;
	}
}


int main(){

	read ();

	return 0;
}
