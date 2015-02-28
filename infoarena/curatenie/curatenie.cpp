#include <cstdio>
#include <iostream>
using namespace std;

	#define fi first
	#define se second
    #define max_n 500005

	int A[max_n],B[max_n];
	int PozA[max_n];
	pair<int,int> C[max_n];

	int i,n;

void solve ( int sta, int dra, int stb, int drb ){
	if ( sta == dra )    
		return ;
	// nodul curent este 
	int nod=B[stb];
	// are ambii fii 
	if ( PozA[nod]!=sta && PozA[nod]!=dra ){
		// Ieee
		C[nod].fi = B[stb+1];
		C[nod].se = B[stb+(PozA[nod]-sta)+1];
		solve ( sta, PozA[nod]-1, stb+1, stb+(PozA[nod]-sta));
		solve ( PozA[nod]+1, dra, stb+(PozA[nod]-sta)+1, drb );
		return ;
	}
	// are doar fiu dreapta
	if ( PozA[nod] == sta ){
		C[nod].se = B[stb+1];
		solve ( sta+1, dra, stb+1, drb );
		return ;
	}
	// are doar fiu stanga ^^ 
	C[nod].fi = B[stb+1];
	solve ( sta, dra-1, stb+1, drb );
}

#define MaxChar 1000000
#define verf ( (++CharB==MaxChar) ? ( cin.read(Buffer,MaxChar),CharB=0 ) : (1) )

long CharB=MaxChar-1;
char Buffer [ MaxChar ];

void cit ( int &a )
{
    for ( ; !(Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9'); verf )
        ;
    for ( a=0; (Buffer[ CharB ]>='0' && Buffer[ CharB ]<='9'); a*=10,a+=( Buffer[ CharB ]-'0'), verf )
        ;
}

int main(){
	freopen ("curatenie.in","r",stdin);
	freopen ("curatenie.out","w",stdout);
	verf;
	cit(n);
	for ( i=1; i<=n; i++ ){
		cit(A[i]);
		PozA[A[i]]=i;
	}
	for ( i=1; i<=n; i++ ){
		cit(B[i]);
	}
	solve ( 1,n, 1,n );
	for ( i=1; i<=n; i++ ){
		cout<<C[i].fi<<" "<<C[i].se<<"\n";
	}
	return 0;
}

