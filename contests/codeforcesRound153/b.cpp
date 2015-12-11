#include <cstdio>
using namespace std;
	
	#define max_n 105
   	int n,i,j,k;

	struct perm {
		int el[max_n];
		int init[max_n];
		void next ( ){
			int T[max_n],i;
			for ( i=1; i<=n; i++ ){
				T[ i ]= el[ init[i] ];
			}
			for ( i=1; i<=n; i++ ){
				el[i]=T[i];
			}
		
			return ;
		}
		void back ( ){
			int T[max_n],i;
			for ( i=1; i<=n; i++ ){
				T[ init[i] ]= el[ i ];
			}
			for ( i=1; i<=n; i++ ){
				el[i]=T[i];
			}
		
			return ;
		}   
		void debug (){
			int i;
			for ( i=1; i<=n; i++ ){
				printf("%d ",el[i] );
			}
			printf("\n");
			return ;
		}
	} A,B,Ca;

	bool egal (){
		for ( int i=1; i<=n; i++ ){
			if ( A.el[i] != B.el[i] ){
				return 0;
			}
		}
		return 1;
	}

int main(){
	scanf ("%d %d", &n, &k );
	for ( i=1; i<=n; i++ ){
		scanf ("%d", &A.init[i] );
		A.el[i]=i;
	}
	Ca=A;
	for ( i=1; i<=n; i++ ){
		scanf ("%d", &B.el[i] );
		B.init[i]=A.el[i];
	}
	for ( i=0; i<=k; i++ ){
		if ( egal () ){
			if ( i!=k && i<2 ){
				break;
			}
			if ( !( ( k-i )&1 ) ){
				printf("YES");
				return 0;
			}
		}
		A.next();
	}
	A=Ca;
	for ( i=0; i<=k; i++ ){
 		if ( egal () ){    
			if ( i!=k && i<2 ){
				break;
			}                   
			if ( !( ( k-i )&1 ) ){
				printf("YES");
				return 0;
			}
		}
		A.back();
	}
	printf("NO");
	return 0;
}
