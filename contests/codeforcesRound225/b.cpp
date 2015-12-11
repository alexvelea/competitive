#include <cmath>

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

#define fi first
#define se second
#define DEBUG false
#define FORIT(it, v) for(vector<int>::iterator it = (v).begin(); it != (v).end(); ++it)

vector<pair<int, int> > segm, next_segm, coord;
vector<int> line, coord_n;

int main() {
	int n, m;
	cin >> n >> m;
	while (m--) {
		int x, y;
		cin >> x >> y;
		line.push_back(x);
		coord.push_back(make_pair(x, y));
	}
	line.push_back(0);
	sort(line.begin(), line.end());
	line.resize(unique(line.begin(), line.end()) - line.begin());
	sort(coord.begin(), coord.end());

	segm.push_back(make_pair(1, 1));
	int i_coord = 0;
 	for (int i = 1; i < line.size(); ++i) {
		if (segm.size() == 0) {
			cout << "-1";
			return 0;
		}

        coord_n.clear();
		coord_n.push_back(0);
		while (i_coord < int(coord.size()) and coord[i_coord].first == line[i]) {
			coord_n.push_back(coord[i_coord].second);
			++i_coord;
		}
		coord_n.push_back(n + 1);

		if (line[i] != line[i - 1] + 1) {
			int st = segm[0].first;
			segm.clear();
			segm.push_back(make_pair(st, n));
		}
		if (DEBUG) {
			cerr << line[i] - 1 << '\t';
	   	 	for (int j = 0; j < segm.size(); ++j)
				cerr << segm[j].first << '#' << segm[j].second << '\t';
			cerr << '\n';
		}
		int i1 = 0;
		for (int i2 = 1; i2 < coord_n.size() and i1 < segm.size(); ) {
			int b = coord_n[i2];
			int a = coord_n[i2 - 1];
			b--;
			a++;
			if (a > b) {
				++i2;
				continue;
			}
			if (DEBUG)
	  			cerr << a << '\t' << b << "###\n";   		   		
			if (segm[i1].second < a) {
				++i1;
			} else {
				if (segm[i1].first <= a) {
					next_segm.push_back(make_pair(a, b));
					++i2;
				} else {
					if (segm[i1].first <= b)
						next_segm.push_back(make_pair(segm[i1].first, b));
					++i2;
				}
			}
		}
		segm.clear();
		swap(segm, next_segm);
		if (DEBUG) {
			cerr << line[i] << '\t';
	 		for (int j = 0; j < segm.size(); ++j)
				cerr << segm[j].first << '#' << segm[j].second << '\t';
			cerr << '\n';
			cerr << '\n';
		}
	}
	if (segm.size() == 0) {
		cout << "-1\n";
		return 0;
	}
 	if (n != line.back()) {
		int st = segm[0].first;
		segm.clear();
		segm.push_back(make_pair(st, n));
	}      

	if (segm.back().second != n)
		cout << "-1\n";
	else 
		cout << 2 * n - 2;
	return 0;
}
