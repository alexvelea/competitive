//11:30
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int INF=0x3f3f3f3f, max_n=1005;

ifstream in("tastatura.in");
ofstream out("tastatura.out");

struct nod_trie{
	int El[10], under;
	nod_trie(){
		for( int i=0; i<10; ++i )
			El[i]=-1;
		under=0;
	}
} empty;
vector<nod_trie> Trie;

string Text, cuvant;
int Best[max_n], n;
int i, j, nod;

int main(){
	Trie.push_back(empty);
	for( i=0; i<10; ++i ){
		Trie.push_back(empty);
		Trie[0].El[i]=i+1;
		Trie[i+1].under=1;
	}
	in>>Text;
	while( in>>cuvant ){
		nod=0;
 		i=0;
 		while( i<cuvant.size() ){
			if( Trie[nod].El[cuvant[i]-'0'] == -1 ){
				Trie[nod].El[cuvant[i]-'0'] = Trie.size();
				Trie.push_back( empty );
			}
			nod = Trie[nod].El[cuvant[i]-'0'];
			i++;
		}
		Trie[nod].under=1;
	}
 	n=Text.size();
	for( i=0; i<=n; ++i )
		Best[i]=INF;
	Best[0]=0;
	for( i=0; i<n; ++i ){
		nod = 0;
		j=0;
		while( i+j < n && nod != -1 ){
			nod = Trie[nod].El[ Text[i+j]-'0' ];
			if( nod == -1 )
				break;
			if( Trie[nod].under )
				Best[i+j+1] = min( Best[i+j+1], Best[i]+1 );
			j++;
		}
	}
	out<<Best[n]<<"\n";
	return 0;
}
