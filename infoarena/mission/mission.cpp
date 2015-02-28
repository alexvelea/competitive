#include <cmath>
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

const int kMaxN = 1005;

#define x first
#define y second

ifstream in("mission.in");
ofstream out("mission.out");

pair<int, pair<int, int> > coord[kMaxN];

int ind = -1;

bool mySort (pair<int, pair<int, int> > a, pair<int, pair<int, int> > b) {
	if (a.x == ind)
		return true;
	if (b.x == ind)
		return false;
	return 1LL * a.second.x * b.second.y < 1LL * b.second.x * a.second.y;
}

int main() {
	int n;
	in >> n;
	for (int i = 0; i < n; ++i) {
		pair<int, int> c;
		in >> c.x >> c.y;
		coord[i] = make_pair(i, c);
		if (ind == -1 or c.y < coord[ind].second.y) {
			ind = i;
		}
	}
 	for (int i = 0; i < n; ++i) {
		if (ind == i)
			continue;
		coord[i].second.x -= coord[ind].second.x;
 		coord[i].second.y -= coord[ind].second.y;
	}
	coord[ind].second.x = coord[ind].second.y = 0;
 	sort (coord, coord + n, mySort);
    int st = 0;
	while (coord[st].first != 0)
		++st;
	for (int i = st; i < n; ++i)
		out << coord[i].first << ' ';
	for (int i = 0; i < st; ++i)
		out << coord[i].first << ' ';
	return 0;
}


