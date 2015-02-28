#include <cstdio>

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

#define max_n 100005
#define max_m 500005
#define pb push_back

bool VizEdge[max_m];

struct edge{
	int a,b,ind;
	edge(){
		a=b=ind=0;
	}
	edge( int _a, int _b, int _ind ){
		a=_a;
		b=_b;
		ind=_ind;
	}
 	int other( int nod ){
		return a+b-nod;
	}
	int viz(){
		return VizEdge[ind];
	}
	void setViz(){
		VizEdge[ind]=1;
	}
} Edge[max_m];
vector<int> Vertex[max_n], Rez;
stack<int> St;

int n,i;
int It[max_n];

int main(){
	int m,a,b;
	freopen("ciclueuler.in","r",stdin);
	freopen("ciclueuler.out","w",stdout);
	scanf("%d %d", &n, &m );
	for( i=1; i<=m; ++i ){
		scanf("%d %d", &a, &b );
		Vertex[a].pb(i);
		Vertex[b].pb(i);
		Edge[i]=edge(a,b,i);
	}
	for( i=1; i<=n; ++i ){
   		if( Vertex[i].size()&1 ){
			printf("-1\n");
			return 0;
		}
	}
	St.push(1);
	bool ok;
	while( St.size() ){			
		#define mu Vertex[nod][It[nod]]  
		#define nod St.top()
		ok=1;
		for( ; It[nod]< int( Vertex[nod].size() ); ++It[nod] ){

			if( !Edge[mu].viz() ){
				Edge[mu].setViz();
				St.push( Edge[mu].other(nod) );
				ok=0;
				break;
			}
		}
		if( ok ){
			Rez.pb(nod);
			St.pop();
		}
	}
	for( i=Rez.size()-2; i>=0; --i )
		printf("%d ",Rez[i]);
	return 0;
}
