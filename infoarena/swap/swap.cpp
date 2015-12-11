#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

	#define max_n 55005	
	#define pb push_back

	char A[max_n],B[max_n];
	vector<int> Poz[30];
	int T[max_n],Fi[max_n],Nr[max_n];
	int Aib[max_n];
	int rez;
	int i,n;

void add ( int ind ){
	for ( ; ind<=n; ind+=((ind)&(-ind)) )
		Aib[ind]+=1;
}
int query ( int ind ){
	int rez=0;
	for ( ; ind; ind-=((ind)&(-ind)) ){
		rez+=Aib[ind];
	}
	return rez;
}

int main(){

	freopen ("swap.in","r",stdin);
	freopen ("swap.out","w",stdout);

	scanf ("%s", &A );
	scanf ("%s", &B );

	n=strlen(A);
	for ( i=0; i<n; i++ ){
		Poz[ A[i]-'a' ].pb(i);
		Fi[ A[i]-'a' ]++;
	}
	for ( i=0; i<n; i++ ){

		if ( Nr[ B[i]-'a' ]+1 > Fi[ B[i]-'a' ] ){
			printf("-1\n");
			return 0;
		}
		T[ i ] = Poz[ B[i]-'a' ][ Nr[ B[i]-'a'] ];
		T[i]++;
		Nr[ B[i]-'a' ]++;
	}
	// trebuie sa vedem T[i] cati are mai mici inaintea lui 
	for ( i=n-1; i>=0; i-- ){
		rez += query ( T[i] );
		add ( T[i] );
	}
	printf("%d\n",rez);
	return 0;
}
