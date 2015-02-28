#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 1005;

int big[kMaxN], viz[kMaxN];
vector<pair<int, int> > event;

void make_empty() {
	for (int i = 0; i < kMaxN; ++i)
		big[i] = viz[i] = 0;
	event.clear();
}

int main() {
	int n;
	while (cin >> n) {
		for (int i = 1; i <= n; ++i) {
			int a, b, c;
			cin >> a >> b >> c;
			big[i] = a;
			event.push_back(make_pair(-c, -b));
		}
		sort(event.begin(), event.end());
		int rez = 0;
		for (int i = 0; i < n; ++i) {
			int small = -event[i].second;
			int c = -event[i].first;
			int mx = 0, poz = 0;
	   	 	for (int j = 1; j <= n; ++j)
				if (not viz[j] && big[j] > mx && big[j] < small) {
					poz = j;
					mx = big[j];
				}
	 		viz[poz] = true;
			rez += c * (small - mx);
		}
		cout << rez << '\n';
		make_empty();
	}
	return 0;
}

