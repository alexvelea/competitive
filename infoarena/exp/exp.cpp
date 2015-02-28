#include <cassert>
#include <cstdio>
#include <fstream>
#include <vector>
using namespace std;

#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define pb push_back
#define max_val 30005

ifstream in("exp.in");
ofstream out("exp.out");

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

vector<int> Div;
int Nr[max_val],Desc[max_val];

int i,j,n,m,ok,x;

void desc( int val ){
	int c=val;
	while( c!=1 && c%Desc[val] == 0 ){
		Nr[ Desc[val] ]++;
		c/=Desc[val];
	}
	if( c == 1 )
		return ;
	FORIT( it,Div ){
		if( (*it)*(*it) > c )
			break;
		if( c == 1 )
			return ;
		while( c%(*it) == 0 ){
			Nr[*it]++;
			c/=*it;
		}
	}
	if( c!=1 )
		Nr[c]++;
}

int main(){
	verf;
	// facem euler
	int i,j;
	for( i=2; i<max_val; ++i ){
		if( Desc[i]==0 ){
			Div.pb(i);
			for( j=i; j<max_val; j+=i ){
				Desc[j]=i;
			}
		}
	}
	Desc[1]=1;
	cit(m);
	cit(n);
	for( i=1; i<=n; ++i ){
		cit(x);
		desc(x); 		
	}
	ok=1;
	FORIT( it, Div ){
		if( Nr[*it]%m ){
			ok=0;
		}
	}
	out<<ok<<"\n";
	if( ok ){
		FORIT( it,Div ){
			if( Nr[*it] ){
				out<<*it<<" "<<Nr[*it]/m<<"\n";
			}
		}
	}
	return 0;
}
