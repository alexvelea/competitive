#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>

using namespace std;

ifstream in("9-cntgcd.in");
ofstream out("cntgcd.out");

int d,n,i,j;
int Exp[15728640];

int main(){
	in>>n>>d;
	n/=d;
	for( i=1; i<=n; ++i )
		Exp[i]=i;
	for( i=2; i<=n; ++i ){
		if( Exp[i] == i ){
			for( j=i; j<=n; j+=i ){
				Exp[j]/=(i);
				Exp[j]*=(i-1);
			}
		}
	}
	long long sum=0;
	for( i=1; i<=n; ++i )
		sum += Exp[i];
	out<<sum<<"\n";
	return 0;
}
