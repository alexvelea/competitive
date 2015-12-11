#include <cstdio>
using namespace std;

int pow( int a, int p, int Mod ){
	int El[40], i;
	int last=1, act=1;
	
	for( int i=0; i<32; ++i )
		El[i]=0;
	
	i=0;
	while( p ){
		El[i++]=p&1;
		p>>=1;
	}
	for( i--; i>=0; --i ){
		if( act == 1 && last != 1 && last != Mod-1 )
			return 0;
		last=act;
		act = (1LL*act*act)%Mod;
		if( El[i] )
			act = (1LL*act*a)%Mod;
		printf("%d#%d\t%d\n",last,act,a);
	}
 	return act;
}

bool MillerRabin( int el ){
	if( el == 1 )
		return 0;
	int Prime[3]={2,7,61};
	for( int i=0; i<3; ++i )
		if( (el != Prime[i]) && ( pow(Prime[i], el-1, el) != 1 ) ){
			printf("%d@%d<----\n",el,Prime[i]);
			return 0;
		}
	return 1;
}

int main(){
	freopen("dk.in","r",stdin);
	int t, rez=0;
	scanf("%d", &t );
	while( t-- ){
		int x;
		scanf("%d", &x );
    	rez += MillerRabin( x );
//		printf("%d$%d\n",x,MillerRabin(x));
	}
	
	freopen("dk.out","w",stdout);
	printf("%d\n",rez);
	return 0;
}
