#include <cstdio>
#include <algorithm>
#include <fstream>
#include <set>
#include <vector>
using namespace std;


ifstream in("nuke.in");
ofstream out("nuke.out");

#define MaxChar 1000000
#define verf ( (++CharB==MaxChar) ? ( in.read(Buffer,MaxChar),CharB=0 ) : (1) )

long CharB=MaxChar-1;
char Buffer [ MaxChar ];

void cit ( int &a )
{
    bool ok=0;
    for ( ; !( (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9') || ( Buffer[ CharB ] == '-' ) ); verf )
        ;
    if ( Buffer[ CharB ] == '-' ){
        verf;
		ok=1;
    }
    for ( a=0; (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9'); a*=10,a+=( Buffer[ CharB ]-'0'), verf )
        ;
    if ( ok ){
        a=-a;
    }
}

#define max_n 200005
#define INF 0x3f3f3f3f
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

struct query{
	int tip,x,y,ind;
	query( ){
		tip=x=y=ind=0;
	}
	query( int _tip, int _x, int _y, int _ind ){
		tip=_tip;
		x  =_x;
		y  =_y;
		ind=_ind;
	}
	bool operator < ( const query other ) const {
		if( y == other.y )
			return tip>other.tip;
		return y<other.y;
	}
} Qact;
vector<query> Query;

struct point{
	int x,y,r;
	point(){
		x=r=y=0;
	}
	point( int _x, int _y, int _r ){
		x=_x;
		y=_y;
		r=_r;
	}
} Point[2*max_n];
 
struct intSet{
	int ind,x;
	intSet(){
		ind=0;
	}
	intSet( int _x, int _ind ){
		ind=_ind;
		x=_x;
	}
	bool operator < ( const intSet& rhs ) const{
		return x<rhs.x;
	}
	bool operator == ( const intSet& rhs ) const{
		return x == rhs.x;
	}
};
set<intSet> Set;


int Rez[max_n], PointLast;
int n,m,i,j;

bool inside( int x1, int y1, int r, int x2, int y2 ){
	int x=x1-x2;
	int y=y1-y2;
	if( 1LL*r*r >= 1LL*x*x + 1LL*y*y )
		return 1;
	return 0;
}

int main(){
	verf;
	int x,y,r;
	cit(n);cit(m);
	for( i=1; i<=n; ++i ){
		cit(x);cit(y);
		Query.push_back( query( 0, x, y, i ) );
	}
	for( i=1; i<=m; ++i ){
		cit(x);cit(y);cit(r);
		Point[i]=point( x,y,r );
		Query.push_back( query( +1, x, y-r, i ) );
		Query.push_back( query( -1, x, y+r, i ) );
	}
	Point[0]=point( INF, INF, 0 );
	sort( Query.begin(), Query.end() );
	Set.insert( intSet( INF,0) );
	Set.insert( intSet(-INF,0) );
	FORIT( it, Query ){
		Qact=*it;
		if( Qact.tip == +1 ){
			// insert
			Set.insert( intSet(Qact.x, Qact.ind) );
		}
		if( Qact.tip == -1 ){
			Set.erase( intSet(Qact.x, Qact.ind) );
		}                       
		if( Qact.tip == 0 ){
			set<intSet> :: iterator it;

			it = Set.find( intSet( Qact.x, -1 ) );
			if( it != Set.end() ){
    			Rez[ it->ind ]++;
				continue;
			}
			it = Set.lower_bound( intSet(Qact.x,-1) );

			if( inside( Point[it->ind].x, Point[it->ind].y, Point[it->ind].r, Qact.x, Qact.y ) ){
				Rez[ it->ind ]++;
			}
			it--;
			if( it!= Set.end() ){
				if( inside( Point[it->ind].x, Point[it->ind].y, Point[it->ind].r, Qact.x, Qact.y ) )
	  				Rez[ it->ind ]++;
			}
		}
	}
	for( i=1; i<=m; ++i )
		out<<Rez[i]<<"\n";
	return 0;
}
