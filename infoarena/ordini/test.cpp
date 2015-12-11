#include <cstdio>
#include <iostream>
using namespace std;

int P[20], rez, target=2, i;

void bt( int nr ){
	if ( nr == target ){
		return ;
	}
	for( int i=0; i<10; ++i ){
		printf("rez -> %d\n",rez);
		rez += P[nr]*i;
		bt( nr+1 );
	}
}

int main(){
	P[1]=1;
	for( int i=2; i<=10; ++i )
		P[i] = P[i-1]*10;
	bt(1);
    printf("%d\n", rez );
	return 0;
}
