#include <cstdio>
#include <cmath>

#include <algorithm>
#include <vector>

using namespace std;

#define FORIT( it, v ) for( typeof((v).begin()) it=(v).begin(); it!=(v).end(); ++it )

struct point{
	double x,y;
	point(){
		x=y=0.0;
	}
	point( double _x, double _y ){
   		x=_x;
		y=_y;
	} 
	point rotate( int alf ){
		point rez;
		// sin(a+b) = sin(a)*cos(b) + sin(b)*cos(a)
		// cos(a+b) = cos(a)*cos(b) - sin(b)*sin(a)

		// sin(a) = x;
		// cos(b) = y;
 		double Si = sin( alf/180.0*M_PI );
		double Co = cos( alf/180.0*M_PI );

		rez.x = x*Co + Si*y;
		rez.y = y*Co - Si*x;

		return rez;
	}
	bool operator<( const point b ) const {
		return atan2( y, x )<atan2( b.y, b.x );
	}
	void debug( ){
		printf("%.5lf\t\t%.5lf\n",x,y);
	}
} P[10];

vector<point> Rez;

point intersectie( point o1, point o2, point p1, point p2 ){
	// y = a*x + b
    double a2=1.0*(p2.y-p1.y)/(p2.x-p1.x);
	double b2=1.0*p1.y-a2*p1.x;
	if( o1.x == o2.x ){
		double x=1.0*o1.x;
		double y=1.0*a2*x+b2;
		return point( x,y );
	}else{
	    double y=o1.y;
		double x=1.0 * ( y-b2 ) / a2;
		return point( x,y );
	}
}
	
bool on_segment( point a, point b, point c ){
	bool ok=1;
	if( ( a.x <= c.x && c.x <= b.x ) || ( b.x <= c.x && c.x <= a.x ) )
		;
	else
		ok=0;

	if( ( a.y <= c.y && c.y <= b.y ) || ( b.y <= c.y && c.y <= a.y ) )
		;
	else
		ok=0;
	return ok;
}

int main(){
	int w,h,alf;
	scanf("%d %d %d", &w, &h, &alf );
	if( alf == 0 || alf == 180 ){
		printf("%.9lf\n", double(1.0*w*h) );
		return 0;
	}
	if( alf == 90 ){
		printf("%.9lf", double(min(h,w)*min(h,w)) );
		return 0;
	}
	P[1]=point( h, w );
	P[2]=point( -h, w );
	P[3]=point( -h, -w );
	P[4]=point( h, -w );
	for( int i=1; i<=4; ++i )
		P[ i+4 ] = P[i].rotate( alf );
	for( int d1=1; d1<=4; ++d1 ){
		int d2=d1+1;
		if( d2 == 5 )
			d2=1;
		for( int l1=5; l1<=8; ++l1 ){
			int l2=l1+1;
			if( l2 == 9 )
				l2=5;

			point cross=intersectie( P[d1], P[d2], P[l1], P[l2] );
			if( on_segment( P[d1], P[d2], cross ) )
				Rez.push_back( cross );
		}
	}
	sort( Rez.begin(), Rez.end() );
    Rez.push_back( Rez[0] );
	double rez=0.0;
	for( int i=0; i+1 < int( Rez.size() ); ++i ){
		rez+=(Rez[i].x-Rez[i+1].x)*(Rez[i].y+Rez[i+1].y)/2.0;
	}
	rez=abs(rez);
	rez/=4.0;
	printf("%.9lf",rez);
	return 0;
}
