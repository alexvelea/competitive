#include <cstdio>
#include <vector>
using namespace std;

	vector<int> T[100005];
	int n,m,h,t,a,b,i,it;

	void write ( int head, int tail ){
		printf("YES\n");
		printf("%d %d\n",head,tail);
		for ( i=1; 
	}

int main(){
	scanf ("%d %d %d %d", &n, &m, &h, &t );
	h++;
	t++;
	if ( h < t ){
		sw=1;
	}

	for ( i=1; i<=m; i++ ){
		scanf ("%d %d", &a, &b  );
		T[a].pb(b);
		T[b].pb(a);
	}
	for ( i=1; i<=n; i++ ){
		for ( it=0; it<T[i].size(); it++ ){
			if ( sw ){
				if ( h == min ( T[i].size(), T[ T[i][it] ].size() ) && t == max ( T[i].size(), T[ T[i][it] ].size() ) ){
					write ( i, T[i][it] );
					return ;
				}
			}
			else{
 				if ( h == max ( T[i].size(), T[ T[i][it] ].size() ) && t == min ( T[i].size(), T[ T[i][it] ].size() ) ){
					write ( i, T[i][it] );
					return ;
				}
			}
		}
	}
	printf("NO");
	return 0;
}                          
