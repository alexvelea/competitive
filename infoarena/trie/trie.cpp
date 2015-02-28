#include <cstdio>
#include <fstream>

#include <string>
#include <vector>
using namespace std;

#define max_l 25
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

string text;
int t;

ifstream in("trie.in");
ofstream out("trie.out");

struct trie{
	int val,under;
	int Next[ 26 ];
	trie(){
		for( int i=0; i<26; ++i ){
			Next[ i ] = -1;
		}
		val=0;
	}
} trie_free;
vector<trie> T;

int add( int v ){
	int act=0;
	FORIT( it, text ){
		if( T[ act ].Next[ *it-'a' ] == -1 ){
			T.push_back( trie_free );
			T[ act ].Next[ *it-'a' ] = T.size()-1;
		}
		act = T[ act ].Next[ *it-'a' ];
		T[ act ].under+=v;
	}
	T[ act ].val+=v;
	return T[ act ].val;
}

int prefix(){
	int act=0,rez=0;
	FORIT( it, text ){
		act = T[ act ].Next[ *it-'a' ];
		if( act == -1 )
			return rez;
		else if ( T[ act ].under == 0 )
			return rez;
		rez++;
	}
	return rez;
}

void solve(){
	int k=0;
	while( in>>t ){
		in>>text;
		k+=t>1;

		switch( t ){
			case 0:
				add( 1 );
			break;
			case 1:
				add( -1 );
			break;
			case 2:
				out<<add( 0 )<<"\n";
			break;
			case 3:
				out<<prefix()<<"\n";
			break;
		}
	}
}

int main(){
	T.push_back( trie() );
	solve();
	return 0;
}

