#include <cassert>
#include <cstdio>

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in("rps.in");
ofstream out("rps.out");

const int max_n = 1000005, max_k=max_n, INF=0x3f3f3f3f;

struct nod_trie{
	int Father, Rez, Inside, It[3];
 	nod_trie(){
		Father = -1;
		Rez = 0;
		Inside = 0;
		It[0]=It[1]=It[2]=-1;
	}
} nod_trie_gol;

vector<nod_trie> Trie;

int n, k, W, D;
int El[max_k];
int i;
char c, Simbol[3]={'R', 'P', 'S'};

void Afiseaza(){
	int nod=0, i, j, mx, ind, Rez[3], Cnt[3];
	for( i=1; i<=k; ++i ){
		// luam cele 3 elemente
		for( j=0; j<3; ++j ){
			if( Trie[nod].It[j] != -1 ){
				Rez[j]=Trie[ Trie[nod].It[j] ].Rez;
				Cnt[j]=Trie[ Trie[nod].It[j] ].Inside;
			}else{
				Rez[j]=Cnt[j]=0;
			}
		}
		mx = -INF;
		ind = -1;
 		// alegem P - 1       punem intai P-ul ca sa se ia in ordine lexicografica :)
		if( Rez[1] + W*Cnt[0] > mx ){
			mx = Rez[1] + W*Cnt[0];
			ind = 1;
		}
    	// alegem R - 0
		if( Rez[0] + W*Cnt[2] > mx ){
			mx = Rez[0] + W*Cnt[2];
			ind = 0;
		}
   		// alegem S - 2 
		if( Rez[2] + W*Cnt[1] > mx ){
			mx = Rez[2] + W*Cnt[1];
			ind = 2;
		}
		assert( ind != -1 );
		if( Trie[nod].It[ind] != -1 ){
			out<<Simbol[ind];
			nod = Trie[nod].It[ind];
		}else{
			out<<Simbol[ind];
			for( ++i; i<=k; ++i )
				out<<Simbol[1];
			out<<"\n";
			return ;
		}
	}
	out<<"\n";
	return ;
}

void update_dp( int nod ){
	int mx, ind, i, Rez[3], Cnt[3];
	Trie[nod].Rez = Trie[nod].Inside * D;
	nod = Trie[nod].Father;
	while( nod != -1 ){
		// luam cele 3 elemente
		for( i=0; i<3; ++i ){
			if( Trie[nod].It[i] != -1 ){
				Rez[i]=Trie[ Trie[nod].It[i] ].Rez;
				Cnt[i]=Trie[ Trie[nod].It[i] ].Inside;
			}else{
				Rez[i]=Cnt[i]=0;
			}
		}
		mx = -INF;
		ind = -1;
		// alegem R - 0
		if( Rez[0] + W*Cnt[2] > mx ){
			mx = Rez[0] + W*Cnt[2];
			ind = 0;
		}
		// alegem P - 1 
		if( Rez[1] + W*Cnt[0] > mx ){
			mx = Rez[1] + W*Cnt[0];
			ind = 1;
		}
		// alegem S - 2 
		if( Rez[2] + W*Cnt[1] > mx ){
			mx = Rez[2] + W*Cnt[1];
			ind = 2;
		}
		assert( ind != -1 );
		Trie[nod].Rez= mx;
		nod = Trie[nod].Father;
	}
}

void Insert(){
	int nod = 0, next, i;
 	for( i=1; i<=k; ++i ){
		if( Trie[nod].It[ El[i] ] == -1 ){
			Trie[nod].It[ El[i] ] = Trie.size();
			next = Trie.size();
			Trie.push_back( nod_trie_gol );
			Trie[next].Father=nod;
		}
		nod = Trie[nod].It[ El[i] ];
		Trie[nod].Inside++;
	}
	update_dp( nod );
	return ;
}

int main(){
	Trie.push_back( nod_trie_gol );
	in>> n >> k >> W >> D;
	while( n-- ){
		for( i=1; i<=k; ++i ){
			in>> c ;
			if( c == 'R' )
				El[i]=0;
			if( c == 'P' )
				El[i]=1;
			if( c == 'S' )
				El[i]=2;
		}
		Insert();
		Afiseaza();
	}
}
