#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in("plagiat.in");
ofstream out("plagiat.out");

#define fi first
#define se second

const int kMaxN = 405;

pair<int, int> coord[kMaxN];
int nr[kMaxN][kMaxN];

struct Event {
	int ind, x, y;
	Event() {
		ind = x = y = 0;
	}
	Event(int _ind, int _x, int _y) {
		ind = _ind;
		x = _x;
		y = _y;
	}
	bool operator < (const Event &rhs) const {
		if (x == rhs.x)
			return y < rhs.y;
		return x < rhs.x;
	}
};
vector<Event> event;

int main() {
	int t;
	in >> t;
	while (t--) {
		int n;
		in >> n;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				nr[i][j] = 0;
		for (int i = 1; i <= n; ++i)
			in >> coord[i].fi >> coord[i].se;
 		
		event.clear();
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (i != j)
					event.push_back(
					  Event(i,
						coord[j].fi - coord[i].fi,
						coord[j].se - coord[i].se));
		sort(event.begin(), event.end());

		int st = 0, dr = 0;
		bool ok = false;
//		for (auto itr : event)
//			cerr << itr.x << '\t' << itr.y << '\t' << itr.ind << '\n';
		for (; st < int(event.size()) and not ok; ) {
			while (dr < int(event.size())
		 	  and event[st].x == event[dr].x
			  and event[st].y == event[dr].y)
				++dr;
 			for (int i = st; i < dr and not ok; ++i)
				for (int j = i + 1; j < dr; ++j) {
					nr[event[i].ind][event[j].ind]++;
 					nr[event[j].ind][event[i].ind]++;
					if (nr[event[i].ind][event[j].ind] == 2)
						ok = true;
				}
			st = dr;
		}
		if (ok)
			out << "DA\n";
		else
			out << "NU\n";
	}
	return 0;
}
