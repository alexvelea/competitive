//Problem b @ 09-12-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

const int inf = 0x3f3f3f3f, kMaxN = 1e5 + 5;
const double eps = 1e-7;

#define int64 long long

pair<int, int> rez[kMaxN];

int main() {
	ios::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	vector<tuple<int, int, int> > el;
	for (int i = 1; i <= m; i += 1) {
		int c, inside; cin >> c >> inside;
		el.push_back(make_tuple(c, 1 ^ inside, i));
	}
	sort(el.begin(), el.end());
	int currentNode = 1;
	pair<int, int> currentBadEdge = {3, 1};
	for (auto itr : el) {
		int c, inside, index;
		tie(c, inside, index) = itr;
		if (1 ^ inside) {
			rez[index] = {currentNode, currentNode + 1};
			currentNode += 1;
		} else {
			if (currentBadEdge.first > currentNode) {
				cout << -1 << '\n';
				return 0;
			}
			rez[index] = currentBadEdge;
			currentBadEdge.second -= 1;
			if (currentBadEdge.second == 0) {
				currentBadEdge.first += 1;
				currentBadEdge.second = currentBadEdge.first - 2;
			}
		}
	}
	for (int i = 1; i <= m; i += 1) {
		cout << rez[i].first << ' ' << rez[i].second << '\n';
	}
	return 0;
}
