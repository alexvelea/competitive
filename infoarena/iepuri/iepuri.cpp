#include <cstdio>
#include <iostream>
using namespace std;

#define mod 666013

int El[3],x,y,z,T;
int rez,l,c;

struct matrice{
	int El[3][3];
	matrice(){
		int i,j;
		for( i=0; i<3; ++i ){
			for( j=0; j<3; ++j ){
				El[i][j]=0;
			}
		}
	}
	matrice( int _a, int _b, int _c ){
 		int i,j;
		for( i=0; i<3; ++i ){
			for( j=0; j<3; ++j ){
				El[i][j]=0;
			}
		}
		El[0][0]=_a;
		El[1][1]=_b;
		El[2][2]=_c;
	}
	void inm( matrice ro ){
		matrice fi(0,0,0);
		int l,c,p;
		for( l=0; l<3; ++l ){
			for( c=0; c<3; ++c ){
				for( p=0; p<3; ++p ){
					fi.El[l][c] += ( 1LL*El[l][p]*ro.El[p][c] ) % mod;
					if( fi.El[l][c] >= mod )
						fi.El[l][c]-=mod;
				}
			}
		}
		for( l=0; l<3; ++l ){
			for( c=0; c<3; ++c ){
				El[l][c]=fi.El[l][c];
			}
		}
	}
} start,finish;

matrice pow( matrice a, int p ){
	matrice rez(1,1,1);
	while(p){
		if( p&1 )
			rez.inm(a);
		a.inm(a);
		p>>=1;
	}
	return rez;
}

int main(){
	freopen("iepuri.in","r",stdin);
	freopen("iepuri.out","w",stdout);
	int t;
	scanf("%d", &t );
	for( ; t; --t ){
 		scanf("%d %d %d %d %d %d %d", &El[0], &El[1], &El[2], &x, &y, &z, &T );
		T-=2;

		start=matrice(0,0,0);
		start.El[0][1]=1;
		start.El[1][2]=1;
		start.El[2][0]=z;
		start.El[2][1]=y;
		start.El[2][2]=x;
		finish=pow(start,T);
		rez=0;
 		for( l=2; l<3; ++l ){
			for( c=0; c<3; ++c ){
				rez+=(1LL*El[c]*finish.El[l][c])%mod;
				if( rez >= mod )
					rez-=mod;
			}
		}
		printf("%d\n",rez);
	}
	return 0;
}
