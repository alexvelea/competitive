#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

#define pb push_back
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

int n,m,i,j,target;
char El;
vector<int> Vertex[55];

int Other[55];
bool Viz[55], Ok[55];

void litera( int nod ){
	if( nod<=26 )
		printf("%c", 'A'+nod-1 );
	else
		printf("%c", 'a'+nod-27);
}

bool find_cuplaj( int nod ){
	if( Viz[nod] || (!nod) )
		return false;
	Viz[nod]=true;
	FORIT( it, Vertex[nod] )
		if( Ok[*it] && ( (!Other[*it]) || find_cuplaj( Other[*it] ) ) ){
			Other[nod]=*it;
			Other[*it]=nod;
			return true;
		}
	return false;
}

int cuplaj(){
	bool ok=1;
	int rez=0,i;
	for( i=0; i<55; ++i )
		Viz[i]=false;
 	while( ok ){
		ok=0;
		for( i=1; i<=52; ++i )
			if( Ok[i] && !Other[i] && find_cuplaj(i) )
				rez++, ok=1;
		for( i=0; i<55; ++i )
			Viz[i]=false;
	}
	for( i=0; i<55; ++i )
		Other[i]=0;
	return rez;
}

int main(){
	freopen("paznici.in","r",stdin);
	freopen("paznici.out","w",stdout);
	scanf("%d %d", &n, &m );
	scanf("%c", &El );
	for( i=1; i<=n; ++i ){
		for( j=1; j<=m; ++j ){
			scanf("%c", &El );
			if( El=='1' ){
				Vertex[i].pb(j+26);
				Vertex[j+26].pb(i);
			}
		}
		scanf("%c", &El );
	}
	for( i=1; i<=52; ++i )
		Ok[i]=Vertex[i].size()>0;
	target=cuplaj();
	for( i=1; i<=52; ++i )
		if( Ok[i] ){
			Ok[i]=0;
			if( cuplaj() == target-1 ){
				target--;
				litera(i);
			}else{
				Ok[i]=1;
			}
		}
	return 0;
}
