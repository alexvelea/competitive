#include <cstdio>
#include <iostream>
using namespace std;

const int max_n=1000005, INF=0x3f3f3f3f;

int n, i, nr_el, act;
int El[max_n];
int Mars[max_n], m;
int Ind[3], target;

long long Rez[max_n], RezDef, RezFin, see;

struct nod {
	int next, last, ind, ap;
 	nod(){
		next = last =  ind = ap = 0;
	}
	nod( int ind ) ;
	void erase() ;
} Qu[ max_n ];

nod::nod( int _ind ){
	next = nr_el+2;
	last = nr_el;
	nr_el++;
	ind = _ind;
 	ap = 0;
}
void nod::erase(){
	Qu[ next ].last = last;
	Qu[ last ].next = next;
}

void debug(){
	int i;
	for( i=0; i<=n+1; ++i ){
		cerr<<Qu[i].last<<"\t"<<Qu[i].next<<"\t"<<Qu[i].ind<<"\t"<<Qu[i].ap<<"\n";
	}
	cerr<<"\n\n";
}
int main(){
	freopen("turnuri.in","r",stdin);
	freopen("turnuri.out","w",stdout);
	scanf("%d", &n);
	for( i=1; i<=n; ++i )
		scanf("%d", &El[i] );
	El[0]=2*INF;
	for( i=1; i<=2; ++i )
		Qu[nr_el+1] = nod(0);
	for( i=1; i<=n; ++i ){
//		debug();
		act = nr_el;
		target = 2;
 		while( target ){
			if( El[ Qu[act].ind ] > El[i] ){
				Ind[target] = Qu[act].ind;
				target--;
			}
			else{
				Qu[act].ap++;
				if( Qu[act].ap == 2 )
					Qu[act].erase();
			}
			act = Qu[act].last;
		}
		see = i-Ind[2];
		if( Ind[2] == 0 )
			see--;
		RezFin -= 2*see; // 1 de la cand il scoatem pe asta, si unu de la cand ii scoatem pe fiecare ceilalti
		RezDef += see;
 		Rez[Ind[2]] += Ind[2]-max( 1, Ind[1] );		
		Qu[nr_el+1] = nod(i);
	}
	for( i=1; i<=n; ++i ){
		RezFin += RezDef + Rez[i];
	}
	printf("%lld", RezFin );
    return 0;
}
