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

class SlimeXSlimesCity {
public:
    int merge( vector <int> population )  {
		sort(population.begin(), population.end());
    	int rez = 0;
    	for (int itr : population) {
			int64 sum = 0;
			bool find = false, ok = true;
 			for (int el : population) {
				if (find) {
					if (sum < el)
						ok = false;
					sum = 1LL * (sum + el);
				} else {
					if (el == itr)
						find = true;
					sum = 1LL * (sum + el);
				}
			}
			rez += ok;
		}
		return rez;
	}
};



// Powered by FileEdit
// Powered by moj 4.17 [modified TZTester]
// Powered by CodeProcessor
