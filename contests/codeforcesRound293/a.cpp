//Problem A from Codeforces Round 293
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
	string a, b;
	cin >> a >> b;
	int n = a.size();
	a[n - 1]++;
	for (int i = n - 1; i > 0; --i) {
		if (a[i] > 'z') {
			a[i] = 'a';
			a[i - 1]++;
		} else {
			break;
		}
	}
	if (a == b) {
		cout << "No such string\n";
	} else {
		cout << a << '\n';
	}
	return 0;
}
//Problem A from Codeforces Round 293
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
//Problem A from Codeforces Round 293
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
