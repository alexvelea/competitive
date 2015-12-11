#include <cstdio>

#include <iostream>
using namespace std;

struct nrmare {
	int val[300000];
	nrmare (){
		int i;
		for ( i=0; i<300000; ++i )
			val[i]=0;
	}
	nrmare ( int z ){
		val[0]=1;
		val[1]=z;
		for ( int i=2; i<300000; ++i )
			val[i]=0;
	}
} rez,pow[30],empty_nrmare,act,aux[5];

int i,j,cn,n;
int gcd[ 200005 ], Nr[ 200005 ];

int max ( int a, int b ){
	if ( a > b )
		return a;
	return b;
}

nrmare multiply ( nrmare a, nrmare b ){
	nrmare c(0);
	int i,j;
	for ( i=1; i<=a.val[0]; ++i ){
		for ( j=1; j<=b.val[0]; ++j ){
			c.val[i+j-1]+=a.val[i]*b.val[j];
		}
	}
	int t=0;
	for ( i=1; i<= b.val[0]+a.val[0]+4 || t; ++i ){
		// posibil sa crashuiasca
		c.val[i]+=t;
		t=c.val[i]/10;
		c.val[i]%=10;
	}
	for ( ; c.val[i]==0; --i )
		;
	c.val[0]=i;
	return c;
}

void afisare ( nrmare a ){
	int i;
	for ( i=a.val[0]; i; --i )
		cout<<a.val[i];
	cout<<"\n";
}
void multy_int ( int val ){
	int i,t=0;
	for ( i=1; i<=aux[0].val[0]; ++i ){
		aux[0].val[i]*=val;
	}
	for ( i=1; i<=aux[0].val[0] || t; ++i ){
		aux[0].val[i]+=t;
		t=aux[0].val[i]/10;
		aux[0].val[i]%=10;
	}
	aux[0].val[0]=i-1;
}
void add ( nrmare a ){
	int i=0,t=0;
	for ( i=1; i<= a.val[0] || t; ++i ){
		rez.val[i]+=a.val[i]+t;
		t=rez.val[i]/10;
		rez.val[i]%=10;
	}
	rez.val[0]=max ( rez.val[0], i-1 );
}
int main(){

    scanf ("%d", &n );
	cn=n;
	for ( i=1; i<=n; ++i ){
		gcd[i]=1;
	}
	for ( i=2; i<=n; ++i ){
		if ( cn%i == 0 ){
			j=1;
			while ( cn%i == 0 ){
				j*=i;
            	for ( int l=j; l<=n; l+=j )
					gcd[l]*=i;
				cn/=i;
			}
		}
	}
	pow[0]=nrmare(1);
    pow[1]=nrmare(2);
	rez=nrmare(0);
	for ( i=2; i<=18; ++i ){
		pow[i]=multiply ( pow[i-1],pow[i-1] );
	}
	for ( i=1; i<=n; ++i ){
		Nr[ gcd[ i ] ] ++;
	}
	for ( i=1; i<=n; ++i ){
		if ( Nr[ i ] ){
			aux[0]=nrmare(1);
			int ind=1, p=i;
			while ( p ){
				if ( p&1 ){
					aux[0]=multiply(aux[0],pow[ind]);
				}
				ind++;
				p/=2;
		    } 
			multy_int( Nr[i] );
			add ( aux[0] );
		}
	}
	int ok=0;
	int act = 0;
	for ( i=rez.val[0]; i; --i ){
		act*=10;
		act+=rez.val[i];
		int nr=0;
		while ( act >= n ){
			act -= n;
            nr++;
		}
		if ( nr )
			ok=1;
        if ( ok ){
        	printf("%d",nr);
		}
	}
	return 0;
}

