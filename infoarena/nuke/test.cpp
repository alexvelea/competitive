#include <cstdio>
#include <set>
#include <iostream>
using namespace std;

#define FORIT( it,v ) for(typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

struct querySet {
	int x,y;
	querySet(){
		x=y=0;
	}
	querySet( int _x, int _y ){
		x=_x;
		y=_y;
	}
	bool operator < ( const querySet rhs ) const{
		if( x == rhs.x )
			return y<rhs.y;
		return x<rhs.x;
	}
};
set<querySet> Set;
set<int> SS;
int main(){
	int x,y,t;
	for( ;; ){
		scanf("%d %d %d", &t, &x, &y );
 		if( t == 1 )
			Set.insert( querySet(x,y) );
		if( t == 0 ){
			set<querySet> :: iterator it;
			it=Set.lower_bound( querySet(x,y) );
			if( it == Set.end() )
				printf("YOK!\n");
			else
				printf("%d %d---\n",it->x, it->y );
		}
		if( t == -1 ){
			FORIT( it, Set )
			printf("%d@%d\n", it->x, it->y );
		}
	}
	return 0;
}
