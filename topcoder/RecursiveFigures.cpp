#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

#define FORIT(it, v) for (typeof((v).begin()) it = (v).begin(); it !=(v).end(); ++it)

class RecursiveFigures {
public:
    double getArea( int sideLength, int K )  {
		double r,rez=0.0;
		int i;
		r=sideLength/2.0;
		for( i=1; i<K; ++i ){
			rez+=r*r*M_PI;
 			r/=1.0*sqrt(2.0);
			rez-=4.0*r*r;
		}
		rez+=r*r*M_PI;
		return rez;
    }
};



// Powered by FileEdit
// Powered by moj 4.17 [modified TZTester]
// Powered by CodeProcessor
