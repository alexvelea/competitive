#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

	#define max_n 200005

	bool V[2*max_n];
	int start,a,b,n,i,step,j;
	int A[2*max_n],B[2*max_n];
	set<int> S[max_n];

int main(){
	freopen ("meneaito.in","r",stdin);
	freopen ("meneaito.out","w",stdout);
	cin>>n;
	for ( i=2; i<n; i++ ){
		cin>>A[i];
	}            
	for ( i=2; i<n; i++ ){
     	cin>>B[i];
	}
	for ( i=2; i<n; i++ ){
		if ( i-A[i] >= 0 )
			S[ i-A[i] ].insert ( 2*(B[i]-A[i]) );	
		if ( 2*(B[i]-i)-(A[i]-i) >= 0 )
			S[ 2*(B[i]-i)-(A[i]-i) ].insert ( 2*(B[i]-A[i]) );
	}
	for ( j=0; j< 200000; ++j ){
		if ( S[j].begin() != S[j].end() )
			V[j]=1;
		for ( std::set<int>:: iterator it=S[j].begin(); it!= S[j].end(); ++it ){
			if ( j+ (*it ) < max_n ){
				S[ j+(*it) ].insert( *it );
			}
		}
		if ( !V[j] ){
			printf("%d",j);
			return 0;
		}
		S[j].clear();
	} 
	printf("-1");
	return 0;
}
