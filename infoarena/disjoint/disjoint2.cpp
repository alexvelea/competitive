#include <cstdio>

#include <vector>

using namespace std;

#define max_n 100005
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define pb push_back

int Father[max_n];
vector<int> El[max_n];
int n,m,i,a,b,t;

void move( int where, int from ){
	FORIT( it, El[from] ){
		Father[*it]=where;
		El[where].pb(*it);
	}
	El[from].erase( El[from].begin(), El[from].end() );
}

int main(){
	freopen("disjoint.in","r",stdin);
	freopen("disjoint.out","w",stdout);
	scanf("%d %d", &n, &m );
	for( i=1; i<=n; ++i ){
    	Father[i]=i;	
		El[i].pb(i);
	}
	for( ; m; --m ){
		scanf("%d %d %d", &t, &a, &b );
		if( t == 2 ){
			if( Father[a] == Father[b] ){
				printf("DA\n");
			}else{
				printf("NU\n");
			}
		}else{
			if( El[Father[a]].size() > El[Father[b]].size() )
				move( Father[a], Father[b] );
			else
				move( Father[b], Father[a] );
			// n*logn
		}
	}
	return 0;
}
