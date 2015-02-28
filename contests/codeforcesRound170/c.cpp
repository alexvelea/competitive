#include <cstdio>

#include <algorithm>
#include <queue>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

#define pb push_back
#define FORIT( it,v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )
#define mp make_pair
#define fi first
#define se second
#define INF 0x3f3f3f3f
#define max_k 100005

int n,m,rez,target;
int k,i,st,dr;
int a,b,c,d,p;

struct edge {
    int a,b,c;
	edge(){
		a=b=c=0;
	}
	edge( int z, int x, int p ){
		a=z;
		b=x;
		c=p;
	}
	bool operator < ( const edge o ) const{
		if( a == o.a )
			return b < o.b;
		return a < o.a;
	}
} Bit[40];
int c1,c2,nr,nrl,nrc;
int l,mx,poz;
int liniesize,coloanasize;
edge Linie[max_k],Coloana[max_k];

void desc( int nr, int poz, int tip ){
	int i=0;
	for( i=0; i<32; ++i )
		if( nr&(1<<i) )
		Bit[ i ] = edge( nr, poz, tip );
}

int main(){
 	scanf("%d %d %d", &n, &m, &k );
	if( ((n-1)&1) ){
		rez^=m;
	}
	if( ((m-1)&1) ){
		rez^=n;
	}
	for( i=1; i<=k; ++i ){
		scanf("%d %d %d %d", &a, &b, &c, &d );
		if( a == c ){
			// linie
			if( b > d )
				swap(b,d);
			Linie[ liniesize++ ] = edge( a, b, d );
		}
		else{
			// coloana
			if( a > c )
				swap(a,c);
			Coloana[ coloanasize++ ] = edge( b, a, c );
		}
	}
	sort( Linie+0, Linie+liniesize  );
	sort( Coloana+0, Coloana+coloanasize );
	st=0;
	for( ; st<liniesize;  ){
		dr=st;
		while( dr<liniesize && Linie[st].a == Linie[dr].a )
			++dr;
		c1 = -1;
 		c2 = -1;
		rez ^= m;
		nr = m;
		for( i=st; i<dr; ++i ){
			if( Linie[i].b > c2 ){
				nr-=(c2-c1);
				c1=Linie[i].b;
				c2=Linie[i].c;
			}else{
				c2=max(c2,Linie[i].c);
			}
		}
		nr-=(c2-c1);	
		rez^=nr;
 		desc( nr, Linie[st].a, 0 );
		st=dr;
		nrl++;
	}
	st=0;
 	for( ; st<coloanasize;  ){
		dr=st;
		while( dr<coloanasize && Coloana[st].a == Coloana[dr].a )
			++dr;
		c1 = -1;
 		c2 = -1;
		rez ^= n;
		nr = n;
		for( i=st; i<dr; ++i ){
			if( Coloana[i].b > c2 ){
				nr-=(c2-c1);
				c1=Coloana[i].b;
				c2=Coloana[i].c;
			}else{
				c2=max(c2,Coloana[i].c);
			}
		}
		nr-=(c2-c1);
		rez^=nr; 		
		desc( nr, Coloana[st].a, 1 );
		st=dr;
		nrc++;
	}
	nr = rez;
	for( i=0; i<32; ++i ){
		if( nr&(1<<i) )
			target=i;
	}
	if( rez && nrl != n-1 && (m&(1<<target)) ){
		st=0;
		nr = rez^m;
		nr = m-nr;
		for( i=1; i<n; ++i ){
			while( st<liniesize && Linie[st].a < i )
				++st;
			if( Linie[st].a != i ){
				printf("FIRST\n%d %d %d %d\n",i,0,i,nr);
				return 0;
			}
		}
	}
	if( rez && nrc != m-1 && (n&(1<<target)) ){
		st=0;
		nr = rez^n;
		nr = n-nr;
		for( i=1; i<m; ++i ){
			while( st<coloanasize && Coloana[ st ].a < i )
				++st;
			if( Coloana[ st ].a != i ){
				printf("FIRST\n%d %d %d %d\n",0,i,nr,i);
				return 0;
			}
		}
	}
	if( rez && Bit[ target ].b ){
		if( Bit[ target ].c == 0 ){
			// linie 
			st=0;
			while( Linie[st].a != Bit[ target ].b )
				++st;
			dr=st;
			while( dr<liniesize && Linie[dr].a == Bit[ target ].b )
				++dr;
			c1=c2=0;
			p = rez^Bit[ target ].a;
			p = Bit[ target ].a - p;
			nr=0;
			poz=-1;
			for( i=st; i<dr && nr<p; ++i ){
				if( Linie[i].b > c2 ){
					nr+=Linie[i].b-c2;
					c2=Linie[i].c;
					poz = Linie[i].b;
				}
				else{
					c2=max(c2,Linie[i].c);
				}
			}     
			if( poz == -1 ){
				poz=c2;
            }
			printf("FIRST\n%d %d %d %d\n",Bit[ target ].b, 0, Bit[ target ].b, poz-(nr-p) );
			return 0;
		}else{
			st=0;
            while( Coloana[st].a != Bit[ target ].b )
				++st;
			dr=st;
			while( dr<coloanasize && Coloana[dr].a == Bit[ target ].b )
				++dr;
			c1=c2=0;
			p = rez^Bit[ target ].a;
			p = Bit[ target ].a - p;
			nr=0;
			poz=-1;
			for( i=st; i<dr && nr<p; ++i ){
				if( Coloana[ i ].b > c2 ){
					nr += Coloana[i].b-c2;
					c2=Coloana[i].c;
					poz=Coloana[i].b;
				}else{
					c2=max(c2,Coloana[i].c);
				}
			}
			if( poz == -1 ){
				poz=c2;
			}
			printf("FIRST\n%d %d %d %d\n",0,Bit[target].b,poz-(nr-p),Bit[target].b);
			return 0;
		}
	}else{
		printf("SECOND\n");
	}
	return 0;
}
