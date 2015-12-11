#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

	#define pb push_back
	#define fi first
	#define se second
	#define MOD 666013
	#define max_n 1005
	#define max_m 100005
	
	vector <int> T[5005];
	int n,a,i,j;

int main(){

    freopen ("input.txt","r",stdin);
	freopen ("output.txt","w",stdout);

	cin>>n;
	for ( i=1; i<=2*n; i++ ){
		cin>>a;
		T[a].push_back(i);
	}
	int ok=1;
	for ( i=1; i<=5002; i++ ){
		if ( (T[i].size() & 1) )
			ok=0;
	}
	if ( ok ){
		for ( i=1; i<=5002; i++ ){

			for ( j=0; j< T[i].size(); j+=2 ){
				cout<<T[i][j]<<" "<<T[i][j+1]<<"\n";
			}
		}
	}
	else{
		cout<<"-1\n";
	}
	return 0;
}

