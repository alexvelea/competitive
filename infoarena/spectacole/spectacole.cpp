//Problem spectacole from Infoarena
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

const int inf = 0x3f3f3f3f, kMaxN = 2005;

ifstream in("spectacole.in");
ofstream out("spectacole.out");

vector<pair<pair<int, int>, int> > query;
vector<pair<int, int> > event[kMaxN];

int a[kMaxN], b[kMaxN], itr[kMaxN];

void get_max(int &a, int b) {
	if (a < b)
		a = b;
}

int main() {
	int n, m;
	in >> n >> m;
	for (int i = 1; i <= n; ++i)
		in >> a[i];
	for (int j = 1; j <= n; ++j)
		in >> b[j];

	for (int i = 1; i <= m; ++i) {
		int id, st, dr;
		in >> id >> st >> dr;
		query.push_back(make_pair(make_pair(st, dr), id));
		event[id].push_back(make_pair(dr, 0));
		event[0].push_back(make_pair(st - b[id], 0));
		event[0].push_back(make_pair(dr + a[id], 0));
	}

	for (int i = 0; i <= n; ++i) {
		event[i].push_back(make_pair(-inf, 1));
		event[i].push_back(make_pair(+inf, 0));
		sort(event[i].begin(), event[i].end());
	}

	sort(query.begin(), query.end());

	int R = 0;
	for (int i = 0; i < m; ++i) {
		int st = query[i].first.first, dr = query[i].first.second, id = query[i].second;
 		while (event[0][itr[0] + 1].first <= st) {
			get_max(event[0][itr[0] + 1].second, event[0][itr[0]].second);
			++itr[0];
		}

  		while (event[id][itr[id] + 1].first <= st) {
			get_max(event[id][itr[id] + 1].second, event[id][itr[id]].second);
			++itr[id];
		}
		vector<pair<int, int> > :: iterator st_0, dr_0, dr_id;
		st_0 = lower_bound(event[0].begin(), event[0].end(), make_pair(st - b[id], 0));
		dr_0 = lower_bound(event[0].begin(), event[0].end(), make_pair(dr + a[id], 0));
		dr_id = lower_bound(event[id].begin(), event[id].end(), make_pair(dr, 0));

		int r = max(st_0->second, event[id][itr[id]].second); r++;
		get_max(R, r);
		get_max(dr_0->second, r);
		get_max(dr_id->second, r);
	}	
	out << R - 1 << '\n';
	return 0;
}
