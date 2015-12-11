#include <cstdio>
#include <vector>
using namespace std;

#define pb push_back
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define max_n 100005

vector<int> Vertex[max_n];

int El[max_n],nr;
bool Son[max_n],Viz[max_n];
int Rez[max_n],K[max_n];
int i,n;

void df(){
	int nod=El[nr];
	Viz[nod]=1;
	if( K[nod] )
		Rez[nod]=Rez[ El[nr-K[nod] ] ]+1;
	FORIT( it,Vertex[nod] ){
		if( !Viz[*it] ){
			El[++nr]=*it;
			df();
		}
	}
	nr--;
}

int main(){
	freopen("cerere.in","r",stdin);
	freopen("cerere.out","w",stdout);
	scanf("%d", &n );
	for( i=1; i<=n; ++i ){
    	scanf("%d", &K[i]);
	}
	int a,b;
	for( i=1; i<n; ++i ){
 		scanf("%d %d", &a, &b );
		Vertex[a].pb(b);
		Son[b]=1;
	}
	for( i=1; i<=n; ++i ){
		if(!Son[i]){
			El[1]=i;
			nr=1;
			df();
		}
	}
	for( i=1; i<=n; ++i ){
		printf("%d ", Rez[i]);
	}
	return 0;
}
