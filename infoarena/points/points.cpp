#include <cstdio>
#include <iostream>
using namespace std;

	long long n,a,b,T[2][2],Sol[4],i;
	long long rez;

long long abs ( long long a ){
	if ( a < 0 )
		return -a;
	return a;
}

void bt ( long long last, long long act ){
	if ( act == 4 ){
		// facem rezultatul
		long long at=0;
        int v = ( (Sol[1]&1)*(Sol[2]>1) )+( (Sol[2]&1)*(Sol[3]>1) )+( (Sol[3]&1)*(Sol[1]>1) ) - ( (Sol[2]&1)*(Sol[1]>1) )-( (Sol[3]&1)*(Sol[2]>1) )-( (Sol[1]&1)*(Sol[3]>1) );
		if ( !(v&1) ){
			at=0;
			at = (long long) ( ( T[ Sol[1]&1 ][ Sol[1]>1 ] ) * ( T[ Sol[2]&1 ][ Sol[2]>1 ] ) * ( T[ Sol[3]&1 ][ Sol[3]>1 ] ) );


			if ( Sol[1] == Sol[2] ) {
				at = (long long) (( T[ Sol[1]&1 ][ Sol[1]>1 ] ) * ( T[ Sol[2]&1 ][ Sol[2]>1 ] -1 ) * ( T[ Sol[3]&1 ][ Sol[3]>1 ] ) / 2 );
			}
			if ( Sol[2] == Sol[3] ) {
				at = (long long) ( ( T[ Sol[1]&1 ][ Sol[1]>1 ] ) * ( T[ Sol[2]&1 ][ Sol[2]>1 ] -1 ) * ( T[ Sol[3]&1 ][ Sol[3]>1 ] ) / 2);
			}
			if ( Sol[1] == Sol[3] ) {
				at = (long long) ( ( T[ Sol[1]&1 ][ Sol[1]>1 ] ) * ( T[ Sol[2]&1 ][ Sol[2]>1 ] ) * ( T[ Sol[3]&1 ][ Sol[3]>1 ] -1 ) / 2);
			}
			if ( ( Sol[1] == Sol[2] ) && ( Sol[2] == Sol[3] ) ) {
				at = (long long) ( ( T[ Sol[1]&1 ][ Sol[1]>1 ] ) * ( T[ Sol[2]&1 ][ Sol[2]>1 ] -1 ) * ( T[ Sol[3]&1 ][ Sol[3]>1 ] -2 ) / 6);
			}
		}
		rez=(long long) rez + at;

		return ;
	}
	for ( long long i=last; i<4; i++ ){
		Sol[act]=i;
		bt ( i, act+1 );
	}
	return ;	
}

int main(){
    freopen ("points.in","r",stdin);
	freopen ("points.out","w",stdout);

	cin>>n;
	for ( i=1; i<=n; i++ ){
		cin>>a>>b;
    	T[a%2][b%2]++;
	}
	bt ( 0, 1 );
	cout<<rez;
	return 0;
}
