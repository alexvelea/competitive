#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

	#define max_n 100005
	#define pb push_back
	vector<int> T[max_n];
	int i,n,m,a,b;     
	int C[max_n];
	int maxim=-1,c;
int main(){
	scanf  ("%d %d", &n, &m );
	for ( i=1; i<=n; i++ ){
		scanf ("%d", &C[i] );
		T[ C[i] ].pb( C[i] );
	}
	for ( i=1; i<=m; i++ ){
		scanf ("%d %d", &a, &b );
		T[ C[a] ].pb ( C[b] );
		T[ C[b] ].pb ( C[a] );
	}
	for ( i=1; i<=100000; i++ ){
    	if ( T[i].size() ){
			sort ( T[i].begin(), T[i].end() );
			int l,j,nr=0;
			j=0;
			while ( j<T[i].size() ){
				l=j;
				while ( (j<T[i].size() ) && ( T[i][j] == T[i][l] )) {
					j++;
				}
				if ( T[i][l]!= i )
					nr++;
			}
			if ( nr > maxim ){
				maxim=nr;
				c=i;
			}
		}
	}
	printf("%d\n",c);
	return 0;
}
