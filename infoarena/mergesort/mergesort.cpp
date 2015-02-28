#include <cstdio>
using namespace std;

    #define MOD 1000003
	int n,Viz[199],Nr[199],val;

void merge_sort ( int st, int dr ){
	val++;
	val%=MOD;
	int ok=1;
	for ( int i=st; i<dr; ++i ){
		if ( Nr[ i ] > Nr[ i+1 ] ){
			ok=0;
		}
	}
	if ( ok ){
		return ;
	}
	int mid = (st+dr)/2;
	merge_sort( st, mid );
	merge_sort( mid+1, dr );
}

void bt ( int k ){
	if ( k == n ){
		merge_sort(1,n);
	}
	else{
		for ( int i=1; i<=n; ++i ){
			if ( !Viz[ i ] ){
				Viz[ i ] =1;
				Nr[ k+1 ] = i;
				bt ( k+1 );
				Viz[ i ] =0;
			}
		}
	}
}

int main(){

	scanf("%d", &n );
    bt ( 0 );
	printf("%d\n",val);


	return 0;
}
