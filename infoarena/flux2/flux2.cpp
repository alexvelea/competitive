#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define fi first
#define se second

const int max_n=1005, INF=0x3f3f3f3f;

vector< pair<int,int> > Vertex[max_n];
queue<int> Q;
bool InQ[max_n];
int NrInside[max_n];
int Best[max_n], n, m, s, d;
int a, b, f, c, cost;
int i;
int t;

int main(){
	freopen("flux2.in","r",stdin);
	freopen("flux2.out","w",stdout);
 	scanf("%d", &t );
	while( t-- ){
        bool ciclu=false;
		int nod;

		scanf("%d %d", &n, &m );
		scanf("%d %d", &s, &d );
		while( m-- ){
			scanf("%d %d %d %d %d", &a, &b, &cost, &f, &c );
			if( c == 0 )
				continue;

			if( f<c )
				Vertex[a].push_back( make_pair(b,cost) );

			if( f )
				Vertex[b].push_back( make_pair(a,-cost) );
		}
        Q.push(s);
		InQ[s]=true;
		while( !Q.empty() ){
			nod = Q.front();
			Q.pop();
			FORIT( it, Vertex[nod] ){
				if( !InQ[it->fi] ){
					Q.push(it->fi);
					InQ[it->fi]=true;
				}
			}
		}
		if( InQ[d] )
			ciclu=true;
		
		for( i=1; i<=n; ++i ){
			Best[i]=INF;
			InQ[i]=false;
		}
		Best[d]=0;
		InQ[d]=1;
 		Q.push(d);
		while( !Q.empty() && !ciclu ){
			nod = Q.front();
			Q.pop();
			InQ[nod]=false;
			FORIT( it, Vertex[nod] ){
				if( Best[it->fi] > Best[nod]+it->se ){
					Best[it->fi] = Best[nod]+it->se;
 					if( !InQ[it->fi] ){
						NrInside[it->fi] ++;
						if( NrInside[it->fi] > n ){
							ciclu=1;
							break;
						}
						InQ[it->fi]=true;
						Q.push( it->fi );
					}
				}
			}
		}
		while( !Q.empty() )
			Q.pop();
 		if( ciclu )
			printf("0\n");
		else
			printf("1\n");
		for( i=1; i<=n; ++i ){
			Vertex[i].clear();
			InQ[i]=false;
			NrInside[i]=0;
		}
	}
}
