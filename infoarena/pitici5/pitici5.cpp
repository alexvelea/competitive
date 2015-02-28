#include <cmath>

#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("pitici5.in");
ofstream out("pitici5.out");

vector<int> el[4];

#define cout out

int main() {
	int n;
	in >> n;
	char c;
	in >> c;
	int last = 0;
	
	if (c == 'A')
		last = 0;
	else
		last = 1;
	
	for (int i = 1; i <= n; ++i) {
		char a, b;
		in >> a >> b;
		int A, B;
		if (a == 'A')
			A = 0;
 		else
			A = 1;

		if (b == 'A')
			B = 0;
		else
			B = 1;
		el[A * 2 + B].push_back(-i);
	}

	for (int i = 0; i < 4; ++i)
		sort(el[i].begin(), el[i].end());

   	for (int i = 1; i <= n; ++i) {
		if (last == 0) {
			if (el[0].size() != 0 and (el[1].size() + el[2].size()) == 1) {
				cout << -el[0].back() << ' ';
				el[0].pop_back();
				last = 0;
			} else {
				if (el[0].size() == 0) {
					cout << -el[1].back() << ' ';
					el[1].pop_back();
					last = 1;
					continue;
				}
				if (el[1].size() == 0) {
                	cout << -el[0].back() << ' ';
					el[0].pop_back();
					last = 0;
					continue;
				}
				if (el[0].back() > el[1].back()) {
					cout << -el[0].back() << ' ';
					el[0].pop_back();
					last = 0;
				} else {
					cout << -el[1].back() << ' ';
					el[1].pop_back();
					last = 1;
				}
			}
		} else {
 			if (el[3].size() != 0 and (el[2].size() + el[1].size()) == 1) {
				cout << -el[3].back() << ' ';
				el[3].pop_back();
				last = 1;
			} else {
				if (el[3].size() == 0) {
					cout << -el[2].back() << ' ';
					el[2].pop_back();
					last = 0;
					continue;
				}
				if (el[2].size() == 0) {
                	cout << -el[3].back() << ' ';
					el[3].pop_back();
					last = 1;
					continue;
				}
				if (el[3].back() > el[2].back()) {
					cout << -el[3].back() << ' ';
					el[3].pop_back();
					last = 1;
				} else {
					cout << -el[2].back() << ' ';
					el[2].pop_back();
					last = 0;
				}
			}   		
		}
	}
	return 0;
}
