#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE_
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

ifstream in("triopalindrom.in");
ofstream out("triopalindrom.out");

const int inf = 0x3f3f3f3f, sigma = 31, Mod = 16384;

string txt;
int rez[5005];

int main() {
	in >> txt;
	int p = 1, f = 0;
	for (int i = 0; i < txt.size(); ++i) {

		for (int l = 1; i + l < txt.size(); ++l) {

		}
	}
	out << f << '\n';
    return 0;
}
