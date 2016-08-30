#include <cassert>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 1e5+5;

ifstream fin("romania.in");
ofstream fout("romania.out");

struct Point {
	int outgoing, left, right;
	bool valid();
} point[kMaxN];

bool Point::valid() {
	if (outgoing == 0 and point[right].outgoing != 0) {
		return true;
	}

	return false;
}

void SkipPoint(int index) {
	assert(point[index].valid());

	fout << point[index].right << ' ' << point[index].left << '\n';

	int left = point[index].left;
	int right = point[index].right;

	point[right].outgoing -= 1;
	point[left].right = right;
	point[right].left = left;

	return ;
}

int main() {
	int n, m; fin >> n >> m;
	for (int i = 1; i <= m; i += 1) {
		int x; fin >> x;
		point[x].outgoing += 1;
	}

	for (int i = 1; i <= n; i += 1) {
		point[i].left = i - 1;
		point[i].right = i + 1;
	}

	point[n].right = 1;
	point[1].left = n;

	vector<int> good_indices;

	for (int i = 1; i <= n; i += 1) {
		if (point[i].valid()) {
			good_indices.push_back(i);
		}
	}

	while (good_indices.size()) {
		int index = good_indices.back();
		good_indices.pop_back();

		int left = point[index].left;
		int right = point[index].right;

		SkipPoint(index);

		if (point[left].valid()) {
			good_indices.push_back(left);
		}

		if (point[right].valid()) {
			good_indices.push_back(right);
		}
	}

	fout.close();
	return 0;
}