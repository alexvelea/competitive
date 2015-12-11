#include <cstdio>

#include <algorithm>
#include <queue>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

#define pb push_back
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define mp make_pair
#define fi first
#define se second
#define INF 0x3f3f3f3f

struct edge {
    int a,b,c;
} ;

long long i,j,a,rez,n;
long long k;
vector<long long> Number;
bool Viz[ 100005 ];

int main(){
	cin>>n>>k;
	for ( i=1; i<=n; ++i ){
		cin>>a;
		Number.push_back(a);
	}
	sort( Number.begin(), Number.end() );
	i=0;
	j=0;
	FORIT( it, Number ){
		if ( !Viz[ j ] ){
			rez++;
			while( i<n && 1LL*Number[ i ] < 1LL*k*(*it) ){
				++i;
			}
			if ( i<n && 1LL*Number[ i ] == 1LL*k*(*it) ){
				Viz[ i ] = 1;
			}
		}
		++j;
	}
	cout<<rez<<"\n";
	return 0;
}
