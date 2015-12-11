//Problem divizori from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

ifstream in("divizori.in");
ofstream out("divizori.out");

vector <pair<int, int> > dv;
vector <int> rez;

int main() {
	int n;
	in >> n;
	for (int d = 2; 1LL * d * d <= n; ++d) {
		if (n % d == 0) {
			int p = 0;
        	while (n % d == 0) {
				n /= d;
				++p;
			}
			dv.push_back(make_pair(d, p));
		}
	}
	if (n != 1) {
		dv.push_back(make_pair(n, 1));
	}
	rez.push_back(1);
	for (pair<int, int> itr : dv) {
		int st = 0;
		int dr = rez.size() - 1;
		for (int i = 1, p = itr.first; i <= itr.second; ++i, p *= itr.first) {
			if (i % 2 == 0)
				for (int j = st; j <= dr; ++j)
					rez.push_back(rez[j] * p);
			else
				for (int j = dr; j >= st; --j)
					rez.push_back(rez[j] * p);
		}
	}
	out << rez.size() << '\n';
	for (int itr : rez)   	
		out << itr << ' ';
	return 0;
}
