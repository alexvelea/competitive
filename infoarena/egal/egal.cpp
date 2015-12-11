#include <cstdio>
#include <cassert>

#include <iostream>
#include <vector>

#include <tr1/unordered_map>
using namespace std;
using namespace std::tr1;

#define max_n 100005
#define pb push_back
#define se second
#define fi first
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

int i,n,a,b;
int Color[ max_n ], Size[ max_n ];
bool Viz[ max_n ];

pair<int,int> Rez[ max_n ];

vector<int> Edge[ max_n ];
tr1::unordered_map< int, int > Map[ max_n ];

struct functie {
	int maxim,ind,i;
	pair<int,int> act,max_act;
	tr1::unordered_map< int,int > :: iterator it;
	functie (){
    	maxim = 0;
		ind = -1;
		i = 0;
		act.fi=act.se=max_act.fi=max_act.se=0;
		it = Map[0].begin();
	}
} S[max_n];

void solve ( int nod ){

	#define i S[nod].i
	#define ind S[nod].ind
	#define maxim S[nod].maxim
	#define act S[nod].act
	#define max_act S[nod].max_act
    #define it S[nod].it
	Viz[ nod ] = 1;
	
/*	tr1::unordered_map<int,int>::iterator it;
	int maxim=0,ind=-1,i;
	pair<int,int> max_act, act;*/
	
	for ( i=0; i< Edge[ nod ].size(); ++i ){
		if ( Viz[ Edge[ nod ][ i ] ] ){
			Edge[ nod ][ i ] = Edge[ nod ][ Edge[ nod ].size()-1 ];
			Edge[ nod ].pop_back();
			i--;
		}
		else{
			solve ( Edge[ nod ][ i ] );
			if ( Size[ Edge[ nod ][ i ] ] > maxim ){
				maxim = Size[ Edge[ nod ][ i ] ];
				ind = i;
			}
			Size[ nod ] += Size[ Edge[ nod ][ i ] ];
		}
	}
	Size[ nod ] ++;
	maxim=0;

	if ( ind != -1 ){
		max_act = Rez[ Edge[ nod ][ ind ]];
		swap ( Map[ nod ], Map[ Edge[ nod ][ ind ] ] );
	}
	else{
		max_act.fi = Color[ nod ];
		max_act.se = 0;
	}
	if ( max_act.fi == Color[ nod ] ){
		max_act.se++;
	}

	it = Map[ nod ].find ( Color[ nod ] );
 	if ( it == Map[ nod ].end() ){
		act.fi = Color[ nod ];
		act.se = 0;
	}
	else{
		act = *it;	
		Map[ nod ].erase ( it );
	}
	act.se++;
	if ( act.se > max_act.se || ( act.se == max_act.se && act.fi < max_act.fi ) ) {
		max_act=act;
	}
	Map[ nod ]. insert( act );
	for ( i=0; i< Edge[ nod ].size(); ++i ){
		if ( i != ind ){
			FORIT ( itMap, Map[ Edge[ nod ][ i ] ] ){
				it = Map[ nod ].find ( itMap->fi );
				if ( it != Map[ nod ].end() ){
     				act = *it;
					Map[ nod ].erase ( it );
				}
				else{
					act.se=0;
				}
				act.fi = itMap->fi;
				act.se += itMap->se;
				if ( act.se > max_act.se || ( act.se == max_act.se && act.fi < max_act.fi ) ) {
					max_act=act;
				}
				Map[ nod ].insert ( act );
			}
		}
		Map[ Edge[ nod ][ i ] ].clear();
	}
	Rez[nod]=max_act;
}

int main(){

	freopen ("egal.in","r",stdin);
	freopen ("egal.out","w",stdout);
    int nod=0;	
	scanf ("%d", &n );
    for ( i=1; i<n; ++i ){
		scanf ("%d %d", &a, &b );
		Edge[ a ].pb( b );
		Edge[ b ].pb( a );
	}
	for ( i=1; i<=n; ++i ){
		scanf ("%d", &a );
		Color[ i ] = a;
	}

	solve ( 1 );

	for ( i=1; i<=n; ++i ){
		printf("%d %d\n",Rez[i].fi, Rez[i].se);
	}

	return 0;
}
