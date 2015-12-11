#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

	#define pb push_back
	#define fi first
	#define se second
	#define MOD 666013
	#define max_n 1005
	#define max_m 100005

	int i,j,n,rez;

	char A[max_m],B[max_m],C[max_m];
	bool Used[max_m];
	int T[30],P[30];

int main(){

    freopen ("input.txt","r",stdin);
	freopen ("output.txt","w",stdout);

	cin>>A;
	cin>>B;
	n=strlen(A);

	for ( i=0; i<n; i++ ){
		T[ A[i]-'A' ]++;
	}

	for ( i=0; i<n; i++ ){
		P[ B[i]-'A' ]++;
	}                  

	for ( i=0; i<27; i++ ){
		if ( T[i] > P[i] ){
			rez+=T[i]-P[i];
		}
	}

 	for ( i=0; i<27; i++ ){
		int s=0;
		for ( j=0; s<P[i] && j<n; j++ ){
			if ( (!Used[j]) && 
				( 
				( ( T[ A[j]-'A' ] > P[ A[j]-'A' ] ) && ( s+1+T[i] <= P[i] ) )  
				|| ( (A[j]-'A') == i  ) 
				|| ( ( A[j]-'A' < i ) && ( T[ A[j]-'A' ] > 0 ) && ( s+1+T[i] <= P[i] ) ) ) ){
				s++;
				C[j]=char ( i+'A' );
				Used[j]=1;
				T[ A[j]-'A' ]--;
			}
		}
	}
	cout<<rez<<"\n"<<C;
	return 0;
}

