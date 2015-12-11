#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>
using namespace std;

const int z6 = 1000000, max_n = z6 + 5;

deque<int> min_deq;
vector<int> el;
int min_id[max_n], max_id[max_n];
int id[max_n];


int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		int x;
		cin >> x;
		el.push_back(x);
	}
 	el.push_back(-(0x3f3f3f3f));
	sort(el.begin(), el.end());
	el.resize(unique(el.begin(), el.end()) - el.begin());

	for (int i = 1; i < int(el.size()); ++i)
		id[el[i]] = i;
	int mx = -1;
	for (int i = 0; i <= k; ++i) {
		if (id[i]) {
			min_deq.push_back(i);
			mx = i;
		}
	}
	for (int i = 0; i <= z6; ++i) {
		if (min_deq.size())
			min_id[i] = id[min_deq.front()];
		if (mx >= i)
			max_id[i] = id[mx];
        if (i + k + 1 < max_n && id[i + k + 1]) {
			mx = i + k + 1;
			min_deq.push_back(i + k + 1);
		}
		if (min_deq.size() && min_deq.front() == i)
			min_deq.pop_front();
	}
/*	for (int i = 0; i <= 20; ++i)
		cerr << i << "#" << min_id[i] << ' ';
	cerr << '\n';
	for (int i = 0; i <= 20; ++i)
		cerr << i << "#" << max_id[i] << ' ';*/
	int rez = 0;
	for (int i = 1; i <= z6; ++i) {
		int dr = 0;
		bool ok = true;
 		for (int j = i; ok && j <= z6; j += i) {
			if (min_id[j] - 1 > dr)
				ok = false;
			dr = max(dr, max_id[j]);
		}
		if (ok && dr == el.size() - 1)
			rez = i;
	}
	cout << rez << '\n';
	return 0;
}
