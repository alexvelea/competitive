//Problem comentariu from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 755;

ifstream fin("comentariu.in");
ofstream fout("comentariu.out");

vector<pair<int, int> > event(kMaxN);
pair<int, int> el[kMaxN];

int bestCase(int v) {
	sort(event.begin(), event.end());
	// sortate dupa (st, dr)
	int rez = 1;
	int minDr = event[0].second;
	for (int ind = 0; ind < int(event.size()); ++ind) {
		if (event[ind].first <= minDr) {
			minDr = min(minDr, event[ind].second);
		} else {
			++rez;
			minDr = event[ind].second;
		}
	}
	
	if (event.size()) {
		++rez;
	}
	return rez;
}

int worstCase(int v) {
	sort(event.begin(), event.end());
	priority_queue<int> pq;
	int ind = 0, rez = 1;
	while (ind < int(event.size()) or pq.size()) {
		if (pq.size() == 0) {
			v = max(v, event[ind].first);
		}

    	while (ind < int(event.size()) and event[ind].first <= v) {
			pq.push(-event[ind].second);
			++ind;
		}

		while (pq.size() and (-pq.top()) < v) {
			pq.pop();
		}

		if (pq.size()) {
			++rez;
			pq.pop();
		}
		++v;
	}
	return rez;
}

int main() {
	int t; fin >> t;
	while (t--) {
		int n; fin >> n;
		for (int i = 1; i <= n; ++i) {
			fin >> el[i].first >> el[i].second;
 			el[i].second += el[i].first;
		}
//		sort(el + 1, el + n + 1);
		for (int i = 1; i <= n; ++i) {
//			cerr << el[i].first << '\t' << el[i].second << '\n';
        	event.clear(); // bestCase
			int v = el[i].second;
 			for (int j = 1; j <= n; ++j) {
				if (el[j].first > v) {
					event.push_back(el[j]);
				}
			}
			fout << bestCase(v) << ' ';

			event.clear(); // worstCase
			v = el[i].first + 1;
			for (int j = 1; j <= n; ++j) {
				if (el[j].second >= v and i != j) {
					event.push_back(el[j]);
				}
			}
			fout << worstCase(v) << '\n';
		}
	}
	return 0;
}
