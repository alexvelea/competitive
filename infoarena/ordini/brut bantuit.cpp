#include <cstdio>
#include <iostream>
using namespace std;

int Ap[10], n, i, Mod, P[10], Rez=0;

int bt( int nr ){
	int r=0;
	for( int i=0; i<10; ++i ){
		if( Ap[i] ){
			if( nr == 1 && i == 0 )
				continue;
			Ap[i]--;
	
			int aux = bt( nr+1 );			
//			cerr<<i*P[nr]*aux<<" <- ce adun\n";
			printf("%d -> Rez inainte de adunare\n", Rez );
			Rez=( i*P[nr]*aux + Rez ) % Mod;
			printf("%d <- Rez dupa adunare\n", Rez );
			cerr<<1LL*i*P[nr]*aux<<"\n";
			if( 0 ){
				cerr<<aux<<"@";
				cerr<<i<<"#"<<nr<<"\n";
				cerr<<Rez<<"\n";
			}
			r+=aux;
			Ap[i]++;
		}
	}
	r=max(r,1);
	return r;
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
		P[i]=(1LL*10*P[i+1]);
	bt( 1 );
//	cerr<<Rez<<"\n";
	printf("Rez -> %d\n", Rez );
	return 0;
}
