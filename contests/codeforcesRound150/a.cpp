#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

	#define max_n 105005

	int i,j,n,rez;
	int P[21][max_n];
	int T[max_n],last;
	int zero;

	vector< pair<int,int> > C;
	set<int> V;

int main(){
	scanf ("%d", &n );
	for ( i=1; i<=n; i++ ){
		scanf ("%d", &T[i] );
		if ( T[i] == 0 )
			zero=1;
	}
	for ( i=20; i>=0; i-- ){
		last=2*n;
		for ( j=n; j>=1; j-- ){
			last++;
			if ( last > 2*n )
				last=2*n;
			if ( T[j] & ( 1<<i ) ){
				last=0;
			}
			P[i][j]=last;
		}
	}
	for ( i=1; i<=n; i++ ){
		C.clear();
		for ( j=0; j<=20; j++ ){
			C.push_back ( make_pair ( P[j][i], (1<<j) ) );
		}
		sort ( C.begin(), C.end() );
		int rez=0,l;
		for ( j=0; j<=20;  ){
       		l=j;
			while ( ( j<=20 ) && C[l].first == C[j].first ){
				rez|=C[j].second;
				j++;
			}
			if ( C[l].first < 2*n ){
				V.insert ( rez );
			}
		}		
	}
	printf("%d", V.size()+zero );
	return 0;

}
