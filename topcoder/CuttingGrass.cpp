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

#define FORIT(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

class CuttingGrass {
public:
    int theMin( vector <int> init, vector <int> grow, int H )  {
    	int t=0, n=init.size();
		int i,j, Best[100];
		for( i=0; i<n; ++i )
			for( j=i+1; j<n; ++j )
				if( grow[i]<grow[j] ){
					swap( grow[i], grow[j] );
					swap( init[i], init[j] );
				}
 		for( ; t<=n; ++t ){
 			// initializam suma
            int sum=0;
 			FORIT( it,init )
				sum+=*it;
			FORIT( it,grow )
				sum+=(*it)*t;
			// facem dinamica
			for( i=0; i<t; ++i )
				Best[i]=0;
 			for( i=0; i<n; ++i ){
				for( j=t-1; j>=0; --j ){
					if( j>0 )
						Best[j]=max( Best[j-1] + init[i] + grow[i]*(t-j), Best[j] );
					else
						Best[j]=max( init[i] + grow[i]*t, Best[j] );
				}
			}
			int mx=0;
			for( j=0; j<t; ++j )
				mx=max(mx,Best[j] );
			sum-=mx;
			if( sum <= H )
				return t;
		}
		return -1;
    }
};
