//Problem meciul from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 100005;

ifstream in("meciul.in");
ofstream out("meciul.out");

pair<int, bool> father[kMaxN];

pair<int, int> getFather(int a) {
	if (father[a].first != a) {
	 	pair<int, int> f = getFather(father[a].first);
		f.second ^= father[a].second;
		father[a] = f;
	}

	return father[a];
}

int main() {
	int t;
	vector<int> rez;
	in >> t;
	while (t--) {
		int n, m;
		in >> n >> m;
		for (int i = 1; i <= n; ++i) {
			father[i] = make_pair(i, 0);
		}

		bool ok = true;

		while (m--) {
			int a, b;
			in >> a >> b;
			pair<int, int> A = getFather(a), B = getFather(b);
			if (A.first != B.first) {

/*				int x = rand() % 2;
				if (x & 1) 
					swap(A, B);*/

				father[B.first] = make_pair(A.first, 1 ^ A.second ^ B.second);
			} else {
				if (A.second == B.second)
                    ok = false;
			}
			if (ok) 
				out << "YES\n";
			else
				out << "NO\n";
		}
	}
	return 0;
}
