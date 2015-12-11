#include <iostream>
using namespace std;
int main(){
	int t,x;
	cin>>t;
	for ( ; t; --t ){
		cin>>x;
		x=180-x;
		if ( 360%x==0 )
			cout<<"YES\n";
		else
			cout<<"NO\n";
	}
	return 0;
}
