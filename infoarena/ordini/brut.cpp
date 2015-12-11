#include <cstdio>
#include <iostream>
using namespace std;

int Ap[10], n, i, Mod, P[100], Rez=0, Cif[100];

void bt( int nr ){
	int ok=0;
	for( int i=0; i<10; ++i ){
		if( Ap[i] ){
			if( nr == 1 && i == 0 )
				continue;
			Ap[i]--;
			Cif[nr] = i;
			bt( nr+1 );
			Ap[i]++;
			ok=1;
		}
	}
	if( ok == 0 ){
		int c = 1, sum = 0, i;
		for( i=nr; i; --i ){
			sum += c * Cif[i];
			sum %= Mod;
			c *= 10;
			c %= Mod;
		}
		Rez += sum;
		Rez %= Mod;
	}
}

int main(){
	freopen("ordini.in","r",stdin);
	for( i=0; i<10; ++i ){
		scanf("%d", &Ap[i] );
		n += Ap[i];
	}
	scanf("%d", &Mod );
	P[n]=1;
	for( i=n-1; i; --i )
		P[i]=(1LL*10*P[i+1])%Mod;
	bt( 1 );
	printf("Rez -> %d\n", Rez );
	return 0;
}
