#include <cstdio>
#include <iostream>
using namespace std;

 	int dx[4]={0,0,1,-1};
	int dy[4]={1,-1,0,0};

	int s,nr,i,j,n,m;
	bool T[130][130];
	char c;
	int maxim;

	struct rez{ 
	int c,s,viz;
	} C[130][130];
	struct point{
		int x,y;
	} Deq[130*130];

bool valid ( int x, int y ){
	if ( ( x>n ) || ( x == 0 ) || ( y>m ) || ( y == 0 ) )
		return 0;
	return 1;
}

void bf ( int x, int y ){
	int i,prim,ultim;
	nr++;
	prim=0;
	ultim=0;
	Deq[0].x=x;
	Deq[0].y=y;
	C[x][y].viz=1;
	C[x][y].c=nr;
	int sm=1;
	while ( prim <= ultim ){
        for ( i=0; i<4; i++ ){
			int xn,yn;
			xn=Deq[prim].x+dx[i];
			yn=Deq[prim].y+dy[i];
			if ( valid(xn,yn) && (!C[xn][yn].viz) && (!T[xn][yn]) ){
				C[xn][yn].viz=1;
				C[xn][yn].c=nr;
				++ultim;
				Deq[ultim].x=xn;
				Deq[ultim].y=yn;
				sm++;
			}
		}
		prim++;
	}
	for ( i=0; i<=ultim; i++ ){
		C[ Deq[i].x ][ Deq[i].y ].s = sm;
	}
	if ( sm > maxim )
		maxim=sm;
	return ;
}

int main(){
	freopen ("vila.in","r",stdin);
	freopen ("vila.out","w",stdout);
	cin>>n>>m;
	for ( i=1; i<=n; i++ ){
		for ( j=1; j<=m; j++ ){
			cin>>c;
			if ( c=='1' )
				T[i][j]=1;
		}
	}
	for ( i=1; i<=n; i++ ){
		for ( j=1; j<=m; j++ ){
			if ( !C[i][j].viz && !T[i][j] )
				bf( i,j );
		}
	}
    cout<<nr<<"\n"<<maxim<<"\n";
	int x=0,y=0;
	for ( i=1; i<=n; i++ ){
		for ( j=1; j<=m; j++ ){
			if ( T[i][j] ){
				s=1;
                for ( int p=0; p<4; p++ ){
					s+= C[ i+dx[p] ][ j+dy[p] ].s;
					for ( int o=0; o<p; o++ ){
						if ( C[ i+dx[p] ][ j+dy[p] ].c == C[ i+dx[o] ][ j+dy[o] ].c ){
							s -= C[ i+dx[p] ][ j+dy[p] ].s;
							break;
						}
					}
				}
				if ( s > maxim ){
					maxim=s;
					x=i;
					y=j;
				}

			}			
		}
	}
	cout<<x<<" "<<y<<" "<<maxim<<"\n";
	return 0;
}
