#include <cstdio>
//#include <iostream>
#include <fstream>
using namespace std;
ifstream cin("convex.in");
ofstream cout("convex.out");

#define max_n 705

int n,m,nr;
int i,j,x,y;

bool El[max_n][max_n], Viz[max_n][max_n];
int Up[max_n][max_n], Left[max_n][max_n], Down[max_n][max_n], Right[max_n][max_n], SP[max_n][max_n];

long long rez;
char c;

int dfs( int x, int y ){
 	if( Viz[x][y] || !El[x][y] )
		return 0;
	Viz[x][y]=1;
	int rez=0;
	rez += dfs( x+1, y );
	rez += dfs( x-1, y );
	rez += dfs( x, y+1 );
	rez += dfs( x, y-1 );
	return rez+1;
}

int main(){
	cin>>n>>m;
	for( i=1; i<=n; ++i )
		for( j=1; j<=m; ++j ){
			cin>>c;
			if( c == 'N' ){
				El[i][j]=true;
				nr++;
				x=i,y=j;
			}
		}
	n=max(n,m); // avem un patrat :)
	// verificam sa fie 'convex' 
	if( nr == 0 ){
		cout<<1<<"\n";
		return 0;
	}
	bool ok, convex=true;
 	for( i=1; i<=n; ++i ){
		ok=false;
 		for( j=1; j<=n; ++j ){
			if( !El[i][j] && El[i][j-1] )
				ok=true;
			if( El[i][j] && ok )
 				convex=false;
		}
	}
	for( j=1; j<=n; ++j ){
		ok=false;
		for( i=1; i<=n; ++i ){
			if( !El[i][j] && El[i-1][j] )
				ok=true;
			if( El[i][j] && ok )
				convex=false;
		}
	}
	if( convex == false ){
		cout<<"0\n";
		return 0;
	}
	if( dfs( x,y ) != nr ){
		cout<<"0";
		return 0;
	}

 	for( i=1; i<=n; ++i )
		for( j=1; j<=n; ++j )
			if( El[i][j] ){
				Up[i][j] = Up[i-1][j] + 1;
				Left[i][j] = Left[i][j-1] + 1;

				rez += Up[i-1][j]; // elemente de pe aceeasi linie
				rez += Left[i][j-1]; // elemente de pe aceeasi coloana
			}
	for( i=n; i; --i )
		for( j=n; j; --j ){
			if( El[i][j] ){
				Down[i][j] = Down[i+1][j] + 1;
				Right[i][j] = Right[i][j+1] + 1;
			}
			SP[i][j] = SP[i][j+1] + SP[i+1][j] - SP[i+1][j+1] + El[i][j];
		}
	for( i=1; i<=n; ++i )
		for( j=1; j<=n; ++j )
			if( El[i][j] ){
				// cate elemente au coltul curent aici :)
				rez +=( Down[i][j]-1 ) * ( Right[i][j]-1 );
				rez +=( Up[i][j]-1 ) * ( Left[i][j]-1 );
				// le scadem pe alea numarate de 2 ori
	            x=i-Up[i][j]+1;
				y=j-Left[i][j]+1;
				rez -= SP[x][y] + SP[i][j] - SP[x][j] - SP[i][y];
			}
	
	for( i=1; i<=n; ++i )
		for( j=1; j<=n; ++j )
			SP[i][j]=0;
	for( i=n; i; --i )
		for( j=1; j<=n; ++j )
			SP[i][j]=SP[i][j-1]+SP[i+1][j]-SP[i+1][j-1]+El[i][j];	
	
	for( i=1; i<=n; ++i )
		for( j=1; j<=n; ++j )
			if( El[i][j] ){
				// idem 
				rez += (Up[i][j]-1)*(Right[i][j]-1);
				rez += (Down[i][j]-1)*(Left[i][j]-1);
 				x=i-Up[i][j]+1;
				y=j+Right[i][j]-1;
				rez -= SP[x][y]+SP[i][j]-SP[x][j]-SP[i][y];
			}

	if( rez*2 == 1LL*nr*(nr-1) || ( rez == 0 && nr == 1 ) )
		cout<<1<<"\n";
	else
		cout<<0<<"\n";

	return 0;
}
