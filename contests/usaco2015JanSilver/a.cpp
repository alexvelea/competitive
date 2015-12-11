//Problem A from Codeforces Round usaco2014JanSilver
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

ifstream in("stampede.in");
ofstream out("stampede.out");

vector<pair<int, int> > event;
map<int, bool> rez, inside;
priority_queue<int> pq;

int main() {
	int n;
    in >> n;
	for (int i = 1; i <= n; ++i) {
		int start, h, speed;
		in >> start >> h >> speed;
		event.push_back(make_pair(-(start + 1) * speed, +h));
		event.push_back(make_pair(-start * speed, -h));
	}

	sort(event.begin(), event.end());
	int fin = 0;

    for (int itr = 0; itr < int(event.size()); ) {
		int time = event[itr].first;
		while (itr < int(event.size()) and event[itr].first == time) {
			int id = event[itr].second;
			++itr;
			if (id < 0) {
				inside[-id] = false;
			} else {
				inside[+id] = true;
				pq.push(-id);
			}
		}

		while (pq.size() and inside[-pq.top()] == false)
			pq.pop();
		if (pq.size()) {
			fin++;
			fin -= rez[pq.top()];
			rez[pq.top()] = true;
		}
	}

	out << fin << '\n';
	
	return 0;
}
