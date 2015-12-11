// 11:54
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

#define FORIT( it, v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

const int max_n=1005;

bool Viz[max_n];
int Other[max_n];
vector<int> Vertex[max_n];

int n, m, i, j, a, b;

bool df( int nod ){
	if( Viz[nod] ) 
		return false;
	FORIT( it, Vertex[nod] )
		if( !Other[*it] && !Viz[*it] ){
			Other[nod] = *it;
			Other[*it] = nod;
			return true;
		}
	Viz[nod]=true;
	FORIT( it, Vertex[nod] )
		if( !Viz[Other[*it]] && df(Other[*it] ) ){
			Other[nod] = *it;
			Other[*it] = nod;
			return true;
		}
	return false;
}

int main(){
    freopen("autostrazi2.in","r",stdin);
    freopen("autostrazi2.out","w",stdout);
    scanf("%d %d", &n, &m );
    while( m-- ){
        scanf("%d %d", &a, &b );
        Vertex[a].push_back(b);
        Vertex[b].push_back(a);
    }
	bool ok=1;
    while( ok ){
		ok=0;
		for( i=1; i<=n; ++i )
	        if( !Viz[i] && !Other[i] ){
	            df(i);
				ok=1;
			}
		for( j=1; j<=n; ++j )
			Viz[j]=0;
    }
    for( i=1; i<=n; ++i )
        if( Other[i] > i )
            printf("%d %d\n", i, Other[i] );
    return 0;
}
