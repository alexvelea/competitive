#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

	#define pb push_back
	#define fi first
	#define se second
	#define max_n 0
	#define max_m 0
 	
	struct point {
		int x,y;
	} ;

	double yc1,yc2,yw,xb,yb,r;
	double m,a1,a2;
	double c1,c2;
	double h1,h2;

int main(){
	cin>>yc1>>yc2>>yw>>xb>>yb>>r;

	yc1=2.0*yw-yc1;
	yc2=2.0*yw-yc2;

	swap ( yc1,yc2 );

	a1=(yc2-yb)*xb;
	double xb1=xb*(yc1-yb)/(yc2-yb);
	a2=(yc1-yb)*xb1;

	// calculam catele.

	c1=sqrt((double)(xb*xb+(yc2-yb)*(yc2-yb)));
	c2=sqrt((double)(xb1*xb1+(yc1-yb)*(yc1-yb)));

	h1=a1/c1;
	h2=a2/c2;
//	printf("%.14lf\n",h1-h2-r);
	if ( h1-h2-r*2.0>=-0.00000001 ){
		// avem rezultat
 		h1+=r;
 		// c*h1 = x*
		double x = (h1+1)/h1;
	}
	else{
		printf("-1");
	}

	return 0;
}
