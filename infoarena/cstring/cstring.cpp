#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("cstring.in");
ofstream out("cstring.out");

const int kMaxN = 1000005, inf = 0x3f3f3f3f;

string a, b, c;
int sol[kMaxN];

vector<int> fre, bad[3];
int deep[3];


int get_mn() {
	int mn = inf;
	for (int i = 0; i < 3; ++i)
		mn = min(deep[i], mn);
	for (int i = 0; i < 3; ++i)
		if (deep[i] == mn)
			return i;
	assert(0);
	return -1;
}

int get_mx() {
 	int mx = -1;
	for (int i = 0; i < 3; ++i)
		mx = max(deep[i], mx);
	for (int i = 0; i < 3; ++i)
		if (deep[i] == mx)
			return i;
	assert(0);
	return -1;   
}

int second_mx() {
	int mx = deep[get_mx()];
	int mn = deep[get_mn()];
	return deep[0] + deep[1] + deep[2] - mx - mn;
}

int ok() {
	int mx = deep[get_mx()];
	int nr = 0;
	for (int i = 0; i < 3; ++i)
		if (deep[i] == mx)
			++nr;
	return nr;
}

int main() {
	int n;
	in >> n;
	in >> a >> b >> c;
    for (int i = 0; i < n; ++i) {
		if (a[i] == b[i] and c[i] == b[i])
			continue;
		
		if (a[i] != b[i] and b[i] != c[i] and c[i] != a[i])
			fre.push_back(i);

		if (a[i] != b[i] and a[i] != c[i]) {
			bad[0].push_back(i);
			deep[0]++;
			sol[i] = 1;
		}
		if (b[i] != a[i] and b[i] != c[i]) {
			bad[1].push_back(i);
			deep[1]++;
			sol[i] = 2;
		}
		if (c[i] != a[i] and c[i] != b[i]) {
			bad[2].push_back(i);
			deep[2]++;
			sol[i] = 0;
		}
	}
	
	while (deep[get_mx()] - second_mx() > fre.size()) {
		int ind = get_mx();
		int p = bad[ind].back();
		bad[ind].pop_back();
		sol[p] = ind;
		for (int i = 0; i < 3; ++i)
			deep[i]++;
		deep[ind] -= 2;
	}

	for (int i = 0; i < int(fre.size()); ++i) {
		int mx = get_mx();
		deep[mx]--;
		sol[fre[i]] = mx;
	}

	for (int i = 0; i < n; ++i) {
    	if (sol[i] == 0)
			out << a[i];
		if (sol[i] == 1)
			out << b[i];
		if (sol[i] == 2)
			out << c[i];
	}
	return 0;
}
