#include <fstream>
#include <iostream>
#include <cstdio>
using namespace std;

	#define max_n 100010

	ifstream in("citylog.in");
	ofstream out("citylog.out");

#define MaxChar 100000
#define verf ( (++CharB==MaxChar) ? ( in.read(Buffer,MaxChar),CharB=0 ) : (1) )

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


int Ancestor[ max_n ][ 5 ];
int i,j,n,m;
int Pow32[ 10 ],tip,x,y,current;

void push ( int x, int y ){
	// nodul x e fiul lui y
	Ancestor[ x ][ 0 ] = y;
	int i;
	int act = y;
	for ( i=0; i<4 && act; ++i ){
		for ( j=1; j<16 && act; ++j ){
			act = Ancestor[ act ][ i ];
		}
		if ( act ){
        	Ancestor[ x ][ i+1 ] = act;
		}   
		else{
			break;
		}
	}
	return ;
}

int search ( int x, int y ){
	// cetatean x al y-lea stramos :)
	int act = x;
	int i,j;
	for ( i=0; i<5; ++i ){
 		for ( j=1; j<= (y&15);  ++j ){
			act = Ancestor[ act ][ i ];
		}
		y>>=4;
	}
	return act;
}

int main(){

	verf;

    Pow32 [ 0 ] = 1;
	for ( i=1; i<=4; ++i ){
 		Pow32 [ i ] = Pow32[ i-1 ] * 16;
	}

	cit(n);
	cit(m);
	for ( i=1; i<=m; ++i ){
		cit(tip);
		cit(x);
		cit(y);
        x ^= current;
		y ^= current;
		
		if ( !tip ){
			push ( x,y );
		}
		else{
			current = search ( x,y );
			out<<current<<"\n";
		}
	}
//	debug();

	return 0;
}
