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
#define max_n 100005

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
struct sth{
	int Bit[2];
	sth(){
		Bit[1]=Bit[0]=-1;
	}
	sth( int _a, int _b ){
		Bit[0]=_a;
		Bit[1]=_b;
	}
} sth_gol;

long long El[max_n],XorSt[max_n],XorDr[max_n];
int n;
vector<sth> Trie;

void insert( long long val ){
	int Cif[66],i=0,act;
	for( i=0; i<66; ++i )
		Cif[i]=0;
	i=0;
	while( val ){
		Cif[i++]=val&1LL;
		val>>=1;
	}
	act=0;
	for( i=63; i>=0; --i ){
		if( Trie[act].Bit[ Cif[i] ]!=-1 )
			;
		else{
			Trie[act].Bit[ Cif[i] ]=Trie.size();
			Trie.push_back(sth_gol);
		}
		act=Trie[act].Bit[ Cif[i] ];
	}
	return ;
}

long long search( long long val ){
	int Cif[66],i,act,ind;
	long long rez=0LL;
	for( i=0; i<66; ++i ){
		Cif[i]=0;
	}
	i=0;
	while( val ){
		Cif[i++]=val&1LL;
		val>>=1;
	}
	act=0;
	for( i=63; i>=0; --i ){
		if( Trie[act].Bit[ Cif[i]^1 ]!=-1 )
			ind = Cif[i]^1;
		else
			ind = Cif[i];
		act=Trie[act].Bit[ind];
		rez=rez+1LL*(1LL<<i)*ind;
	}
	return rez;
}

int main(){
	Trie.push_back(sth_gol);
	int i;
	cin>>n;
	for( i=1; i<=n; ++i ){
		cin>>El[i];
		XorSt[i]=XorSt[i-1]^El[i];
	}
	for( i=n; i; --i ){
		XorDr[i]=XorDr[i+1]^El[i];
	}
	long long mx,rez;
	rez=0LL;
	mx=0LL;
    for( i=n; i>=0; --i ){
		insert( XorDr[i+1] );
		rez=XorSt[i]^search( XorSt[i] );
		if( rez > mx ) 
			mx=rez;
	}
	cout<<mx<<"\n";
	return 0;
}
