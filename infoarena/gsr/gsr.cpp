#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#ifdef __APPLE_
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

ifstream in("gsr.in");
ofstream out("gsr.out");

const int inf = 0x3f3f3f3f;


int main() {
	int k, b;
 	in >> b >> k;
	int64 nr = 0;
	char txt;
	while (in >> txt) {
		int x;
		if (txt >= 'A' and txt <= 'F')
			x = txt - 'A' + 10;
		else
			x = txt - '0';
		nr *= 1LL * b;
		nr += x;
		nr %= k;
	}
	out << nr << '\n';
    return 0;
}
