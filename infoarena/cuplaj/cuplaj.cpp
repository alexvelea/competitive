#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define max_n 10005
#define FORIT( it,v ) for(typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define pb push_back

bool Viz[max_n];
int St[max_n],Dr[max_n];
vector<int> Left[max_n], Rez;

int n,m,e;

bool cuplaj( int nod ){
	if( Viz[nod] )
		return 0;
	Viz[nod]=1;
	FORIT( it, Left[nod] ){
		if( !Dr[*it] || cuplaj( Dr[*it] ) ){
			St[nod]=*it;
			Dr[*it]=nod;
			return 1;
		}
	}
	return 0;
}

int main(){
	freopen("cuplaj.in","r",stdin);
	freopen("cuplaj.out","w",stdout);
	scanf("%d %d %d", &n, &m, &e );
	int a,b;
	for( ; e; --e ){
		scanf("%d %d", &a, &b );
		Left[a].pb(b);
	}
	bool ok=1;
	Viz[0]=1;
	while( ok ){
		ok=0;
		for( int i=1; i<=n; ++i )
			if( !St[i] && !Viz[i] )
				if( cuplaj(i) )
					ok=1;

		for( int i=1; i<=n; ++i )
			Viz[i]=0;
	}
	for( int i=1; i<=n; ++i )
		if( St[i] ){
			Rez.pb(i);
			Rez.pb(St[i]);
		}
	printf("%d\n",Rez.size()/2);
	for( int i=0; i< int(Rez.size()); i+=2 ){
		printf("%d %d\n",Rez[i],Rez[i+1] );
	}
	return 0;
}
