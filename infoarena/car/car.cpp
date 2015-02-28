#include <cstdio>
#include <algorithm>
#include <deque>
#include <iostream>
using namespace std;

#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define fi first
#define se second
#define mp make_pair
#define pb push_back

#define max_n 505

int Dx[8]={ 1, 1, 0, -1, -1, -1, 0, 1 };
int Dy[8]={ 0, 1, 1, 1, 0, -1, -1, -1 };

int next( int d ){
	d++;
	if( d == 8 )
		return 0;
	return d;
}
int last( int d ){
	d--;
	if( d == -1 )
		return 7;
	return d;
}

struct coord{
	int x,y;
	coord(){
		x=y=0;
	}
	coord( int _x, int _y ){
		x=_x;
		y=_y;
	}
	coord move( int d ){
		return coord( x+Dx[d], y+Dy[d] );
	}
} St,Fi;

int Best[max_n][max_n][8], El[max_n][max_n];
bool Viz[max_n][max_n][8];
deque< pair<coord,int> > Deq;

int i,j,n,m;

int main(){
	freopen("car.in","r",stdin);
	freopen("car.out","w",stdout);
	scanf("%d %d", &n, &m);
	scanf("%d %d %d %d", &St.x, &St.y, &Fi.x, &Fi.y );
	for( i=1; i<=n; ++i ){
		for( j=1; j<=m; ++j ){
 			scanf("%d", &El[i][j]);
		}
	}
	for( i=0; i<=max(n,m)+1; ++i ){
		El[0][i]=El[i][0]=El[n+1][i]=El[i][m+1]=1;
	}
	// inseram TOATE DIRECTIILE!
	for( i=0; i<8; ++i ){
		Deq.push_front( make_pair( St, i ) );
		Best[St.x][St.y][i]=1;
	}
	coord act;
	int dir,cost,otherD;
	while( Deq.size() ){
		act = Deq.front().fi;
		dir = Deq.front().se;
		Deq.pop_front();
		cost = Best[act.x][act.y][dir];
		if( El[act.x][act.y] )
			continue;
		if( Viz[act.x][act.y][dir] )
			continue;
		Viz[act.x][act.y][dir]=1;
		otherD=next(dir);
		if( !Best[act.x][act.y][otherD] ){
 			Best[act.x][act.y][otherD] = cost+1;
			Deq.push_back( make_pair( act, otherD ) );
		}
		otherD=last(dir);
		if( !Best[act.x][act.y][otherD] ){
			Best[act.x][act.y][otherD] = cost+1;
			Deq.push_back( make_pair( act, otherD ) );
		}
		act=act.move(dir);
		if( !Viz[act.x][act.y][dir] && ( Best[act.x][act.y][dir]>cost || Best[act.x][act.y][dir] == 0 ) ){
			Best[act.x][act.y][dir]=cost;
			Deq.push_front( make_pair( act,dir ) );
		}
	}
    int mn = 0x3f3f3f3f;
	for( i=0; i<8; ++i ){
		if( Best[Fi.x][Fi.y][i] && Best[Fi.x][Fi.y][i]<mn )
			mn=Best[Fi.x][Fi.y][i];
	}
	if( mn == 0x3f3f3f3f )
		printf("-1\n");
	else
		printf("%d\n",mn-1);
	return 0;
}
