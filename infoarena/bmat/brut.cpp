#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>
using namespace std;

const int w = 6, h = 4, k = 3;

vector<pair<int,int> > coord;
bitset<(1<<30)> ok;

int solve (int st, int ind) {
	int x = ind % w;
	int y = ind / w;
	for (int i = 0; i < int(coord.size()); ++i) {
		int nx = x + coord[i].first;
		int ny = y + coord[i].second;
		if (nx >= 0 && ny >= 0)
			;
		else
			continue;
		st ^= (1<<(nx + w * ny));
	}
	return st;
}

int main() {
	for (int i = 0; i < k; ++i)
		for (int j = 0; j < k; ++j)
			coord.push_back(make_pair(-i, -j));
   for (int i = 1; i < 1 << (h*w); ++i)
		for (int j = 0; j < h*w; ++j)
			if (i & (1<<j))
				if (not ok[solve(i, j)])
					ok[i] = true;
	for (int i = 0; i < h * w; ++i) 
		cout << i << '\t' << ok[1<<i] << '\n';
	return 0;
}
