#include<iostream>
#include <cstdio>
using namespace std;

	#define max_n 105

	int n,m,i,j,last,A[max_n][max_n],B[max_n][max_n],T[max_n][max_n];
	char c;

int main(){

    	freopen ("cruce.in","r",stdin);
		freopen ("cruce.out","w",stdout);

	cin>>n>>m;
	for ( i=1; i<=n; i++ ){
		for ( j=1; j<=m; j++ ){
			cin>>c;
			T[i][j]=c-'a'+1;
		}
	}
	// facem pscpld pe linii
	for ( i=1; i<=n; i++ ){
		last=0;
		for ( j=1; j<=m; j++ ){
			if ( last+A[i][j] >= j )
				A[i][j]=min( last+A[i][last]-j, A[i][2*last-j] );
            while ( ( j-A[i][j]-1 >=1 ) && 
					( j+A[i][j]+1 <=m ) &&
					( T[i][ j+A[i][j]+1 ] == T[i][ j-A[i][j]-1 ] ) )
				A[i][j]++;
			if ( last+A[i][last] < j+A[i][j] )
				last=j;
		}
	}
	// facem pscpld pe coloane
	for ( j=1; j<=m; j++ ){
     	last=0;
		for ( i=1; i<=n; i++ ){
			if ( last+B[i][j] >= i )
				B[i][j]=min( last+B[i][j]-i, B[2*last-i][j] );
			while ( ( i-B[i][j]-1 >=1 ) &&
					( i+B[i][j]+1 <=n ) && 
					( T[i+B[i][j]+1][j]==T[i-B[i][j]-1][j] ) )
				B[i][j]++;
			if ( last+B[last][j] < last+B[i][j] )
				last=i;
		}
	}                             
	long long rez=0;
	for ( i=1; i<=n; i++ ){        
		for ( j=1; j<=m; j++ ){
			rez+=(A[i][j])*(B[i][j]);
		}
	}
	cout<<rez;
	return 0;
}

