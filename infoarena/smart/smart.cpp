#include <cstdio>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

const int max_n=55, max_t=500;

#define fi first
#define se second

ifstream in("smart.in");
ofstream out("smart.out");

int Dx[4]={ 0,-1, 0, 1 };
int Dy[4]={-1, 0,+1, 0 };

struct stare{
	int x, y, t;
	stare(){
		x=y=t=0;
	}
	stare( int _x, int _y, int _t ){
		x=_x;
		y=_y;
		t=_t;
	}
	bool operator != ( const stare other ) const {
		if( x == other.x && y == other.y && t==other.t )
			return 0;
		return 1;
	}
	bool viz(){
		if( x!=0 || y!=0 || t!=0 )
			return 1;
		return 0;
	}
} From[max_n][max_n][max_t], empty;

bool C[max_n][max_n][4][max_t];
int Up[max_n][max_n][max_t];
int n, k, i, j, El[max_n][max_n], T, MaxFlow;
char c;

int get_dir( stare a, stare b ){
 	int x=b.x-a.x;
	int y=b.y-a.y;
	if( x == 0 && y == -1 )
		return 0;
	if( x == -1 && y == 0 )
		return 1;
	if( x == 0 && y == 1 )
		return 2;
	return 3;
}

pair<int,int> St,Finish;
queue<stare> Deq;

void make_empty(){
	int i,j,t;
	for( i=0; i<=n; ++i )
		for( j=0; j<=n; ++j )
			for( t=0; t<=T; ++t ){
				From[i][j][t]=empty;
			}
	while( !Deq.empty())
		Deq.pop();
}

bool valid( int a ){
	if( 1<=a && a<=n )
		return 1;
	return 0;
}

bool FindFlow(){
	bool end=false, ok;
	int x, y, timp, d;
	stare Sink, Source=stare( St.fi, St.se, 0 ), nod;
	make_empty();
	Deq.push(Source);
	From[St.fi][St.se][0] = Source;
	while( (!Deq.empty()) && (!end) ){
		nod = Deq.front();
		Deq.pop();
		for( d=0; d<4; ++d ){
			x=nod.x+Dx[d];
			y=nod.y+Dy[d];
 			if( valid(x) && valid(y) )
				;
			else
				continue;
			if( El[x][y] )
				continue;
 			// mergem inainte
			ok=0;
			if( nod.t < T ){
				if( !C[nod.x][nod.y][d][nod.t] && !From[x][y][nod.t+1].viz() ){
 					From[x][y][nod.t+1]=nod;
					Deq.push( stare(x,y,nod.t+1) );
					ok=1;
					timp = nod.t+1;
				}
			}
			// mergem inapoi :)
			if( nod.t ){
				if( C[x][y][d^2][nod.t-1] && !From[x][y][nod.t-1].viz() ){
					From[x][y][nod.t-1]=nod;
					Deq.push( stare(x,y,nod.t-1) );
					ok=1;
					timp = nod.t-1;
				}
			}
			if( (ok==1) && (x == Finish.fi) && (y == Finish.se) ){
				Sink = stare( Finish.fi, Finish.se, timp );
				end = true;
				break;
			}
		}
		if( !From[nod.x][nod.y][nod.t+1].viz() && nod.t < T ){
			From[nod.x][nod.y][nod.t+1]=nod;
			Deq.push( stare( nod.x, nod.y, nod.t+1 ) );
		}
		if( nod.t )
			if( !From[nod.x][nod.y][nod.t-1].viz() && Up[nod.x][nod.y][nod.t-1] ){
				From[nod.x][nod.y][nod.t-1]=nod;
				Deq.push( stare( nod.x, nod.y, nod.t-1 ) );
			}
	}
 	if( !end )
		return false;
	stare F;
	for( ; Sink != Source;  ){
		F = From[ Sink.x ][ Sink.y ][ Sink.t ];
		if( F.x == Sink.x && F.y == Sink.y ){
			if( F.t > Sink.t ){
				Up[Sink.x][Sink.y][Sink.t] --;
			}else{
				Up[F.x][F.y][F.t]++;
			}
			swap( Sink, F );
			continue;
		}
 		if( F.t < Sink.t )
 			C[F.x][F.y][get_dir( F,Sink )][ F.t ] = true;
		else
			C[Sink.x][Sink.y][get_dir( Sink,F ) ][ Sink.t ] = false;
		swap( Sink, F );
	}
	MaxFlow++;
	return 1;
}

int main(){
	in>>n>>k;
	for( i=1; i<=n; ++i )
		for( j=1; j<=n; ++j ){
			in>>c;
			if( c == 'X' ){
				St.fi=i;
				St.se=j;
			}
			if( c == 'Y' ){
				Finish.fi=i;
				Finish.se=j;
			}
			if( c == '1' )
				El[i][j]=1;
		}
	for( T=1; ; T++ ){
		while( FindFlow() )
			;
		if( MaxFlow >= k ){
			out<<T<<"\n";
			return 0;
		}
	}   
	return 0;
}
