#include <cstdio>
#include <iostream>
using namespace std;
	
	#define max_n 10005

	int n,i;
	double X[max_n],Y[max_n],RX[max_n],RY[max_n];
	double a,b;

bool ok ( double a ){
	if ( ( a > -0.001 ) && ( a < 0.01 ) )
		return 0;
	return 1;
}

int main(){
	freopen ("poligon2.in","r",stdin);
	freopen ("poligon2.out","w",stdout);
	cin>>n;
	for ( i=1; i<=n; i++ ){
		cin>>a>>b;
		X[i]=a*2.0;
		Y[i]=b*2.0;
	}
	RX[1]=123.0;
	RY[1]=-123.0;
	for ( i=2; i<=n; i++ ){
		RX[i]=X[i-1]-RX[i-1];
		RY[i]=Y[i-1]-RY[i-1];
	}
	
	if ( ok (RX[1]+RX[n]-X[n]) || ok(RY[1]+RY[n]-Y[n]) ){
		printf("fara solutie\n");
		return 0;
	}
	for ( i=1; i<=n; i++ ){
    	printf("%.3lf %.3lf\n", RX[i], RY[i]);
	}
	return 0;
}
