#include <fstream>
#include <vector>
using namespace std;
struct trie{
	int ind,Next[2];
	trie(){
		ind=Next[1]=Next[0]=-1;
	}
} free_trie;
vector<trie> T;

int Max=-1,st,dr,i,l,B[35],n,c,act,sum,x,a;

int main(){
	ifstream in("xormax.in");
	ofstream out("xormax.out");
	in>>n;
	T.push_back( free_trie );
	act=0;
	for( i=0; i<31; ++i ){
		T.push_back( free_trie );
		T[ act ].Next[0]=T.size()-1;
		act=T.size()-1;
		T[ act ].ind = 0;
	}

	for( i=1; i<=n; ++i ){
		in>>x;
		a ^= x;
		// scriem pe act ca siruri de biti
		for( l=0; l<31; ++l ){
			B[ l ]=0;
		}
		c = a;
		l=0;		
		while( c ){
			B[ l++ ] = c&1;
			c>>=1;
		}
		act=0;
		sum=0;
		for( l=30; l>=0; --l ){
			// ar fi recomantat sa o luam pe cealata parte
			if( T[ act ].Next[ B[l]^1 ] != -1 ){
				sum ^= ( 1<<l );
				act = T[ act ].Next[ B[l]^1 ];
			}
			else{
				act = T[ act ].Next[ B[l] ];
			}
		}
		if( sum > Max ){
			Max = sum;
			st = T[ act ].ind+1;
			dr = i;
		}
		// adaugam numarul curent
		act=0;
		for( l=30; l>=0; --l ){
			if( T[ act ].Next[ B[l] ] == -1 ){
				T.push_back( free_trie );
				T[ act ].Next[ B[l] ] = T.size()-1;
			}
			act = T[ act ].Next[ B[l] ];
			T[act].ind = i;
		}
	}
	out<<Max<<" "<<st<<" "<<dr<<"\n";
	return 0;
}
