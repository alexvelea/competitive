#include <cassert>
#include <cstdio>
using namespace std;

#define max_c 5000005
int Fact[3][max_c],Exp[3],Nr[3],Act[3];
int r,d;
int ok,rez,ind,p;
int i,j;

int main(){
    freopen("pascal.in","r",stdin);
	freopen("pascal.out","w",stdout);
 	scanf("%d %d", &r, &d );
	if( d==2 )
		Nr[0]=1;
	if( d==3 )
		Nr[1]=1;
	if( d==4 )
		Nr[0]=2;
	if( d==5 )
		Nr[2]=1;
	if( d==6 )
		Nr[0]=Nr[1]=1;

	Exp[0]=2;
	Exp[1]=3;
	Exp[2]=5;

	for( ind=0; ind<3; ++ind ){
		for( p=Exp[ind]; p<=r; p*=Exp[ind] ){
			for( i=p; i<=r; i+=p )
				Fact[ind][i]++;
		}
	}
	rez=0;
	for( i=1; i<=r-i; ++i ){
		ok=1;
		for( j=0; j<3; ++j ){
			Act[j]-=Fact[j][i];
			Act[j]+=Fact[j][r-i+1];
			if( Act[j]<Nr[j] )
				ok=0;
		}
		rez+=2*ok;
		if( i == r-i )
			rez-=ok;
	}
	printf("%d\n",rez);
	return 0;
}
