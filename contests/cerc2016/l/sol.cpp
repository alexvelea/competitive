#include <iostream>
#include <vector>
#include <set>

#define maxn 60

using namespace std;

int n;
int a[3][maxn];
vector<pair<int,int>> sol;

void add_fuck(int j, int k, int h) {
	int x = 1, y = j;
	if (k == 0) 
		x += n;
	if (h == 1)
		y += n;
	sol.push_back({x, y});
}

string sgn(int x) {
	if (x > n)
		return "!";
	return "";
}

int mod(int x) {
	if (x <= n)
		return x;
	return x-n;
}

void solve() {
	cin >> n;

	for (int i = 1; i <= 3; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> a[i][j];
		}
	}

	sol.clear();

	for (int j = 2; j <= n; ++j) {
		set<pair<int,int>> S;
		for (int i = 1; i <= 3; ++i) {
			S.insert({a[i][1], a[i][j]});
		}

		for (int k = 0; k < 2; ++k) {
			for (int h = 0; h < 2; ++h) {
				if (S.find({k, h}) == S.end()) {
					add_fuck(j, k, h);
				}
			}
		}
	}

	cout << sol.size() << "\n";

	for (auto el: sol) {
		cout << sgn(el.first) << "x" << mod(el.first) << " -> "
			 << sgn(el.second) << "x" << mod(el.second) << "\n";
	}
}

int main() {
	int k = 1;
	for (; k <= 2; ++k) {
		solve();
	}
}