#include <cstdio>
#include <iostream>
using namespace std;
	long long n,a,suma,i;
int main(){
	cin>>n;
	for ( i=1; i<=n; i++ ){
		cin>>a;
		suma+=a;
	}
	if ( suma%n == 0 )
		cout<<n;
	else
		cout<<n-1;
	return 0;
}
