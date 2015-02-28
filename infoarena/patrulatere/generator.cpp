#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct point {
	int x,y;
	bool operator == ( const point b ) const {
		if( x==b.x && y==b.y )
			return 1;
		return 0;
	}
	void debug(){
		printf("%d\t%d\n",x,y);
	}
} Point[300],Act;

int n,mod,beg;
int i,j,l;

bool coliniar( point a, point b, point c ){
	if( a.x == b.x && c.x!=a.x )
		return 0;
	if( a.x == c.x && c.x!=b.x )
		return 0;
	if( b.x == c.x && a.x!=b.x )
		return 0;

	if( a.x>b.x )
		swap(a,b);
	if( a.x>c.x )
		swap(a,c);
	if( b.x>c.x )
		swap(b,c);
	
 	double y=1.0*(b.x-a.x)/(c.x-a.x)*(c.y-a.y);
	y+=1.0*a.y;
	if( abs(y-b.y) < 0.001 )
		return 1;
	return 0;
}

int main(){
	srand( time(NULL) );
	freopen("patrulatere.in","w",stdout);
	// constante
	n=5;
	mod=20;
	beg=0;

	for( i=1; i<=n; ++i ){
		int ok=0;
		while( !ok ){
			ok=1;
			Act.x=rand()%mod;
			Act.y=rand()%mod;
			Act.x+=beg;
			Act.y+=beg;
			// vedem daca avem deja elementul 
			for( j=1; j<i; ++j )
				if( Point[j]==Act )
					ok=0;
			if( !ok )
				continue;
			for( j=1; j<i; ++j ){
				for( l=j+1; l<i; ++l ){
					if( coliniar( Point[j], Point[l], Act ) )
						ok=0;	
				}
			}
		}
		Point[i]=Act;
	}
	printf("%d\n",n);
	for( i=1; i<=n; ++i ){
		printf("%d %d\n",Point[i].x, Point[i].y );
	}
	return 0;
}
