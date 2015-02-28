#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <queue>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

#define pb push_back
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define mp make_pair
#define fi first
#define se second
#define th third
#define INF 0x3f3f3f3f
#define mx 305
struct trio {
    int first,second,third;
	trio(){
		fi=se=th=0;
	}
	trio( int a, int b, int c ){
		fi=a;
		se=b;
		th=c;
	}
 	int other( int nod ){
		return fi+se-nod;
	}
} ;
bool M[mx][mx][mx], R[mx][mx][mx][4];

int min( int a, int b ){
	if( a < b )
		return a;
	return b;
}

void solve( int a, int b, int c ){
	int mn=1;
	if( (a>0) ){
		if( (M[a-1][b][c] == -1) );
			solve(a-1,b,c);
		
	}
	if( (b>0)  )
		if(  (M[a][b-1][c] ==-1) )
		solve(a,b-1,c);
	if( (c>0) ) if (  (M[a][b][c-1] == -1) )
		solve( a,b,c-1 );
	if( (a>0) && (b>0) && (c>0) ) if( (M[a-1][b-1][c-1] == -1) )
		solve( a-1,b-1,c-1 );
	if( a > 0 ) 
		mn=min(R[a-1][b][c][0],mn);
	if( b > 0 ) 
		mn=min(R[a][b-1][c][1],mn);
	if( c > 0 )
		mn=min(R[a][b][c-1][2],mn);
	if( (a>0) && (b>0) && (c>0) )
		mn=min(R[a-1][b-1][c-1][3],mn);
	mn^=1;
	M[a][b][c]=mn;
	for( int i=0; i<4; ++i )
		R[a][b][c][i]=mn;
	if( a>0 )	
		R[a][b][c][0]=min(R[a-1][b][c][0],mn);
	if( b>0 )
		R[a][b][c][1]=min(R[a][b-1][c][1],mn);
	if( c>0 )
		R[a][b][c][2]=min(R[a][b][c-1][2],mn);
	if( (a) && (b>0) && (c>0) )
		R[a][b][c][3]=min(R[a-1][b-1][c-1][3],mn);
}

int i,j,l;

int main(){
	for( i=0; i<mx; ++i )
		for( j=0; j<mx; ++j )
			for( l=0; l<mx; ++l )
				M[i][j][l]=-1;
	int rez=0;
	freopen("d2.cpp","w",stdout);
	for( i=0; i<mx; ++i )
		for( j=0; j<mx; ++j )
			for( l=0; l<mx; ++l ){
				solve(i,j,l);
				if( M[i][j][l]==0 )
    				if( i<=j && j<=l ){
						printf("%d,",i*mx*mx+j*mx+l);
						if(rez%1000==0)
							printf("\n");
						rez++;
					}
			}
	printf("}\n\n");
	return 0;
}
