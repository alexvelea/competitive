#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define max_n 1005

void get_max( int &a, int b ){
	if( b>a )
		a=b;
}

struct element{
	int x1,y1,x2,y2;
	element(){
		x1=x2=y1=y2=0;
	}
	element( int _x1, int _y1, int _x2, int _y2 ){
		x1=_x1;
		y1=_y1;
		x2=_x2;
		y2=_y2;
		if( x1>x2 )
			swap(x1,x2);
		if( y1>y2 )
			swap(y1,y2);
	}
	int get_time( element other ){
		int rez=0;
		int x,y;
		if( x1==x2 )
			{x=x1;y=other.y1;}
		else
			{x=other.x1;y=y1;}
		if( x1<=x && x<=x2 && y1<=y & y<=y2 )
			;
		else
			get_max( rez, max(min( abs(x-x1),abs(x-x2) ), min( abs(y-y1), abs(y-y2))) );
		if( other.x1<=x && x<=other.x2 && other.y1<=y && y<=other.y2 )
			;
		else
			get_max( rez, max(min( abs(x-other.x1), abs(x-other.x2) ), min( abs(y-other.y1), abs(y-other.y2) ) ) );
		return rez;

	}
} ;
vector< element > E[2];

struct event{
	int cost, l, c;
	event(){
		cost=l=c=0;
	}
	event( int _cost, int _l, int _c ){
		cost=_cost;
		l=_l;
		c=_c;
	}
	bool operator <( const event b ) const {
		return cost<b.cost;
	}
} ;
vector< event > Event;

int i,j,ind;
int x1,y1,x2,y2;
int n;

vector<int> Col[max_n];
bool Viz[max_n][max_n];

int main(){
	freopen("segmente.in","r",stdin);
	freopen("segmente.out","w",stdout);
	scanf("%d", &n );
	for( i=1; i<=n; ++i ){
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2 );
		if( x1==x2 ){
			ind=0;
		}else{
			ind=1;
		}
		E[ind].push_back(element( x1, y1, x2, y2 ) );
	}
	if( E[1].size()<E[0].size() )
		swap( E[1],E[0] );
	// facem eventurile
	i=0;
	FORIT( itL, E[0] ){
		j=0;
		FORIT( itC, E[1] ){
			Event.push_back(event( itL->get_time( *itC ),i,j));
	   		++j;				
		}
		++i;
	}
	sort( Event.begin(), Event.end() );
	FORIT( it, Event ){
		FORIT( itC, Col[ it->c ] ){
			if( Viz[it->l][*itC] || Viz[*itC][it->l] ){
				printf("%d\n",it->cost);
				return 0;
			}
			Viz[it->l][*itC]=Viz[*itC][it->l]=1;
		}
		Col[it->c].push_back(it->l);
	}
	return 0;
}
