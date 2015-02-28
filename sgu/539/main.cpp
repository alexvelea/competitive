#include <cassert>

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 1005;

int n, el[kMaxN], where[kMaxN];
bool viz[kMaxN];


bool check(bool show) {
	bool ok = true;
	int nr = 0;
	for (int i = 1; i <= n; ++i)
		if (el[el[i]] != i) {
			ok = false;
		} else {
			if (el[i] != i)
				nr++;
		}
	if (ok and show) {
		cout << nr / 2 << ' ';
		for (int i = 1; i <= n; ++i)
			if (el[i] != i and el[i] <= i) {
				cout << i << ' ' << el[i] << ' ';
			}
		cout << '\n';
	} else {
		if (show and not ok)
			assert(0);
	}
	return ok;
}

vector<pair<int, int> > steps;
void swp(int a, int b) {
	swap(el[a], el[b]);
	swap(where[el[a]], where[el[b]]);
	viz[a] = viz[b] = true;
	steps.push_back(make_pair(a, b));
}


void solve(int poz) {
	if (el[poz] == poz or (el[el[poz]] == poz))
		return ;
	int oth = el[poz];
	int ind = where[poz];
	swp(oth, ind);
	solve(ind);
}


void make_two() {
	for (int i = 1; i <= n; ++i)
		if (not viz[i])
			solve(i);
	cout << steps.size() << ' ';
	for (int i = 0; i < int(steps.size()); ++i)
		cout << steps[i].first << ' ' << steps[i].second << ' ';
	cout << '\n';
}


bool is_sorted() {
	for (int i = 1; i < n; ++i)
		if (el[i] > el[i + 1])
			return false;
	return true;
}

pair<int, int> init[kMaxN];
int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> el[i];
		init[i] = make_pair(el[i], i);
	}
	sort(init + 1, init + n + 1);
	for (int i = 1; i <= n; ++i)
		el[init[i].second] = i;
	for (int i = 1; i <= n; ++i)
		where[el[i]] = i;
	if (is_sorted()) {
		cout << "0\n";
		return 0;
	}
	bool one;
 	one = check(false);
	if (one) {
		cout << "1\n";
		check(true);
	} else {
		cout << "2\n";
		make_two();
 		check(true);
	}
	return 0;
}
