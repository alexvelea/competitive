#include <iostream>
using namespace std;

	#define max_n 100005

int T[max_n],i,n,rez,minim;
int min ( int a, int b ){
	if ( a < b )
		return a;
	return b;
}

int main(){
	cin>>n;
	for ( i=1; i<=n; ++i ){
		cin>>T[i];
	}
	minim=n+1;
	bool ok=false;
	for ( i=n; i; --i ){
		if ( ok ){
			rez++;
			continue;
		}
		if (T[ i ] > minim ){
			rez++;
			ok=1;
		}
		minim=min(T[i],minim);
	}
	cout<<rez<<"\n";
}
