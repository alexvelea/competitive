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

class RowAndManyCoins {
public:
    string getWinner( string cells )  {
		int n = cells.size();
		n--;
		if( cells[0] == 'A' || cells[n] == 'A' )
			return "Alice";
		return "Bob";
    }
};
