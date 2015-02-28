#include <cstdio>
#include <vector>
using namespace std;

	#define max_n 100005
	#define pb push_back

	bool Viz[max_n];
	int i,a,b,n,t;
	vector<int> T[max_n];

bool df ( int nod, int val ){
	int cnt=0;
	Viz[nod]=1;
	for ( int i=0; i< T[nod].size(); i++ ){
		if ( !Viz[ T[nod][i] ] ){
			cnt++;
			int ok = df ( T[nod][i], 1 );
			if ( !ok )
				return 0;
		}
	}
	if ( cnt > val )
		return 0;
	return 1;
}

int main(){

	freopen ("itree.in","r",stdin);
	freopen ("itree.out","w",stdout);

	scanf ("%d", &t );
	for ( ; t; t-- ){
		scanf ("%d", &n );
		for ( i=1; i<n; i++ ){
			scanf ("%d %d", &a, &b );
			T[a].pb(b);
			T[b].pb(a);
		}
		for ( i=1; i<=n; i++ ){
			if ( T[i].size() == 1 )
				Viz[i]=1;
		}
		int ok=0;
		for ( i=1; i<=n; i++ ){
			if ( !Viz[i] ){
				int val = df ( i,2 );
				if ( val ){
					printf("YES\n");
				}
				else{
					printf("NO\n");
				}
				ok=1;
				break;
			}
		}
		if ( !ok ){
			printf("YES\n");
		}
		for ( i=1; i<max_n; i++ )
			T[i].clear(), Viz[i]=0;
	}
	return 0;
}
