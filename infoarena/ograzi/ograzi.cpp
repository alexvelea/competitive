#include <cstdio>
 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
 
#define MaxChar 1000000
#define verf ( (++CharB==MaxChar) ? ( in.read(Buffer,MaxChar),CharB=0 ) : (1) )
 
ifstream in("ograzi.in");
ofstream out("ograzi.out");
 
long CharB=MaxChar-1;
char Buffer [ MaxChar ];
 
void cit ( int &a )
{
    bool ok=0;
    for ( ; !( (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9') || ( Buffer[ CharB ] == '-' ) ); verf )
        ;
    if ( Buffer[ CharB ] == '-' ){
        CharB++;
        ok=1;
    }
    for ( a=0; (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9'); a*=10,a+=( Buffer[ CharB ]-'0'), verf )
        ;
    if ( ok ){
        a=-a;
    }
}
 
 
#define MOD 1048575
#define max_n 50005
 
struct point {
    int x,y;
} sheep, rectangle;
 
vector<point> Hash[ MOD ];
 
int n,m,w,h;
int i,d;
 
int dx[4] = { 0, -1, -1,  0 };
int dy[4] = { 0,  0, -1, -1 };

int get_value ( int x, int y ){
	if ( x < 0 || y < 0 )
		return -1;
    return ( (x&MOD)*(100001&MOD) + y ) & MOD;
}
 
int main(){
    verf;
    cit ( n );    cit ( m );    cit ( w );    cit ( h );
    for ( i=1; i<=n; ++i ){
        cit ( rectangle.x );	cit ( rectangle.y );
        int nr;
        nr = get_value ( rectangle.x/w , rectangle.y/h );
		Hash[ nr ].push_back ( rectangle );
    }
    int rez=0;
    for ( ; m; --m ){
        cit ( sheep.x );
        cit ( sheep.y );
        bool ok=0;
		for ( d=0; d<4; ++d ){
			int nr = get_value ( sheep.x/w + dx[ d ] , sheep.y/h + dy[ d ] );
			if ( nr != -1 ){
		        for ( i=0; i< int ( Hash[ nr ].size() ) && !ok; ++i ){
		            if ( sheep.x >= Hash[ nr ][ i ].x &&
		                sheep.x <= Hash[ nr ][ i ].x + w &&
		                sheep.y >= Hash[ nr ][ i ].y &&
		                sheep.y <= Hash[ nr ][ i ].y + h )
		                ok=1;
		        }
			}
		}
        rez+=ok;
    }
    out<<rez;
    return 0;
}
