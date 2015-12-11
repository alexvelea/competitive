//Problem B from Codeforces Round 293
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

int viz[300];

int main() {
	int A = 0, B = 0;
	string a, b;
    cin >> a >> b;
	for (auto c : a) {
		viz[int(c)]++;
	}
    for (auto &c : b) {
		if (viz[int(c)]) {
			++A;
			--viz[int(c)];
			c = '#';
		}
	}	
	for (auto &c : b) {
		if (c != '#') {
			int oth = 0;
			if (c >= 'a' and c <= 'z') {
				oth = c - 'a' + 'A';
			} else {
				oth = c - 'A' + 'a';
			}
			if (viz[oth]) {
				++B;
				viz[oth]--;
			}
		}
	}
	cout << A << ' ' << B << '\n';
	return 0;
}
//Problem B from Codeforces Round 293
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

int main() {

return 0;
}
//Problem B from Codeforces Round 293
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

int main() {

return 0;
}
