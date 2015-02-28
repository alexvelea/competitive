#include <cstdio>

#include <algorithm>
#include <queue>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

	#define pb push_back
	#define fi first
	#define se second
	#define max_n 100005


long long Best[ max_n ];
bool Viz[ 1005 ];
int i,j,n,x,res;

vector <int> P, Ciur;

struct edge {
    int a,b,c;
} ;

int main(){
	
	for ( i=2; i<=1000; ++i ){
		if ( !Viz[ i ] ){
			Ciur.push_back ( i );
			for ( j=i*i; j<=1000; j+=i ){
				Viz[ j ] = 1;
			}
		}
	}
	
	cin>>n;
	for ( ; n; --n ){
		cin>>x;
		P.clear();
		for ( i=0; i<Ciur.size(); ++i ){
			if ( x % Ciur[i] == 0 ){
				P.push_back ( i );
				while ( x % Ciur[ i ] == 0 ){
					x /= Ciur[ i];
				}
			}
		}
		if ( x != 1 ){
			P.push_back ( x );
		}
		int mx = 0;
		for ( i=0; i<P.size(); ++i ){
        	if ( Best[ P[ i ] ] > mx ){
				mx = Best[ P[ i ] ];
			}
		}
		mx ++;
		for ( i=0; i<P.size(); ++i ){
			if ( mx > Best[ P[ i ] ] ){
				Best[ P[ i ] ] = mx;
			}
		}
		if ( res < mx ){
			res = mx;
		}
	}
	cout<<res<<"\n";
	return 0;
}
