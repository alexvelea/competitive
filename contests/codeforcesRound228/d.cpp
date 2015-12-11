#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int inf = 0x3f3f3f3f;

int ok[1 << 26];

int solve(int k) {
	int rez = 0;
	for (int i = 1; i < (1 << (k + 1)); ++i)
		rez += ok[i];
	return rez;

}

bool is_ok(int st) {
	for (int i = 0; i < 25; ++i)
		for (int j = 0; j < 25; ++j)
			if ((st & (1 << i)) and (st & (1 << j))) {
				if ((i ^ j) >= 25)
					return 0;
				if ((st & (1 << (i ^ j))) == 0)
					return 0;
			}
	return 1;
}

int main() {
 	for (int i = 1; i < (1 << 13); ++i) {
 		ok[i] = is_ok(i);
		if (ok[i]) {
			for (int j = 0; j < 25; ++j)
				if (i & (1 << j))
					cerr << j << '\t';
			cerr << '\n';
		}
	}
	int s[100];
	for (int i = 0; i < 25; ++i)
		s[i] = solve(i);
	for (int i = 1; i < 25; ++i)
		cout << i << '\t' << s[i] - s[i - 1] << '\n';
	return 0;
}
