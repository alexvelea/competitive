#include <cstdio>
#include <fstream>
#include <iostream>
using namespace std;

ifstream in("teams.in");
ofstream out("teams.out");

const int max_val=33000;

int Ap[max_val], Sum[max_val];
int n, a, b, i, ap, bp, x, sum;
long long rez;
bool ok;

int main(){
	in>>n>>a>>b;
	for( i=1; i<=n; ++i ){
		in>>x;
		Ap[x]++;
	}
	for( i=1; i<max_val; ++i )
		Sum[i] = Sum[i-1] + Ap[i];
	for( i=1; i<max_val; ++i ){
		ap = a-i;
		bp = b-i;
		

		bp = max( bp,0 );
		bp = min( bp, i-1 );
		ap = min( ap, bp+1 ); // scadem 1 de acolo .. deci daca il pune m = b o sa fie 0 overall
 		ap = max( ap,1 );  

		sum = Sum[bp] - Sum[ap-1];
		rez = 1LL*Ap[i]*sum + rez;
		
		if( a <= 2*i && 2*i <= b )
			rez = rez + 1LL*(Ap[i]*(Ap[i]-1)/2);
	}
	out<<rez<<"\n";
	return 0;
}
