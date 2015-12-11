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
#define max_n 100005

struct edge {
    int a,b,c;
} ;

int i,n,a,b;
vector<int> Vertex[ max_n ];
pair< long long, long long > Rez[ max_n ];
int Val[ max_n ];
bool Viz[ max_n ];

void df ( int nod ){
	Viz[ nod ] = 1;

	FORIT( it, Vertex[ nod ] ){
		if ( !Viz[ *it ] ){
			df( *it );
			Rez[ nod ].fi = max( Rez[ nod ].fi, Rez[ *it ].fi );
			Rez[ nod ].se = max( Rez[ nod ].se, Rez[ *it ].se );
		}
	}
	if ( Val[ nod ] + Rez[ nod ].fi - Rez[ nod ].se > 0 )
		Rez[ nod ].se += Val[ nod ] + Rez[ nod ].fi - Rez[ nod ].se;
	else
		Rez[ nod ].fi -= Val[ nod ] + Rez[ nod ].fi - Rez[ nod ].se;
}

int main(){
	cin>>n;
	for ( i=1; i<n; ++i ){
		cin>>a>>b;
		Vertex[ a ].pb ( b );
		Vertex[ b ].pb ( a );
	}
	for ( i=1; i<=n; ++i ){
		cin>>Val[i];
	}
	df(1);
	cout<<Rez[ 1 ].fi + Rez[ 1 ].se;
	return 0;
}
