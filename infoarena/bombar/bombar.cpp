#include <cstdio>
#include <cassert>
#include <algorithm>
#include <iostream>
using namespace std;

#define sigma 1000000000
#define max_cif 2000

struct nrmare{
	unsigned int El[max_cif];
	int nrcif;
	nrmare(){
		for( int i=0; i<max_cif; ++i ){
			El[i]=0;
		}
		nrcif=0;
	}
	nrmare( int _el){
		El[0]=_el;
		nrcif=1;
		for( int i=1; i<max_cif; ++i ){
			El[i]=0;
		}
	}
	void afisare(){
		int i,j,x,Cif[10];
		for( i=nrcif-1; i>=0; --i ){
			if( i==nrcif-1 ){
				printf("%d",El[i]);
//				cout<<El[i];
			}else{
				assert(El[i]<sigma);
				x=El[i];
				for( j=0; j<9; ++j )
					Cif[j]=0;
				j=0;
				while( x ){
					Cif[j++]=x%10;
					x/=10;
				}
				for( j=8; j>=0; --j )
					printf("%d",Cif[j]);
//					cout<<Cif[j];
			}
		}
		printf("\n");
//		cout<<"\n";
	}
} N[2];

void add(){	
	// 0 = plin, 1 = gol
	int i, t;
	for( i=0; i<= max( N[0].nrcif, N[1].nrcif )+3; ++i ){
	    if( i>1 ){
			t = 0;
			while( N[0].El[i-2] >= sigma ){
				t++;
				N[0].El[i-2]-=sigma;
			}
			N[0].El[i-1] += t;
			if( N[0].El[i-2] > 0 )
				N[0].nrcif = max( N[0].nrcif, i-1 );

            t = 0;
			while( N[1].El[i-2] >= sigma ){
				t++;
				N[1].El[i-2]-=sigma;
			}
			N[1].El[i-1] += t;
			if( N[1].El[i-2] > 0 )
				N[1].nrcif = max( N[1].nrcif, i+1 );

		}
		N[1].El[i] = ( N[1].El[i] + ( N[0].El[i] << 1 ) ); 		
		N[0].El[i] = ( N[1].El[i] + N[0].El[i] );    
	}
}

int main(){

	freopen("bombar.in","r",stdin);
	freopen("bombar.out","w",stdout);

	int T;
	scanf("%d", &T );
	N[0]=N[1]=nrmare(1);
	T--;
	while( T ){
		add();
		T--;
	}
    N[0].afisare();
	return 0;
}
