//Problem geometrie from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 200005;

ifstream in("geometrie.in");
ofstream out("geometrie.out");

struct Event {
	int x, y, type;
	Event() {
		x = y = type = 0;
	}

	Event(int _x, int _y, int _type) {
		x = _x;
		y = _y;
		type = _type;
	}

	bool operator < (const Event &rhs) const {
		if (x == rhs.x) {
			return type > rhs.type;
		}
		return x < rhs.x;
	}
};

vector<Event> event;

int64 arieUp[kMaxN], arieDown[kMaxN], rez[kMaxN];
Event evUp[kMaxN], evDown[kMaxN];

int64 arieTriunghi(Event &a, Event &b, Event &c) {
	int64 rez = 1LL * (a.x - b.x) * (a.y + b.y) 
		+ 1LL * (b.x - c.x) * (b.y + c.y)
		+ 1LL * (c.x - a.x) * (c.y + a.y);
	return rez;
}

int main() {
	int n, m; in >> n >> m;
	for (int i = 1; i <= n; ++i) {
		int x, y; in >> x >> y;
		event.push_back(Event(x, y, 0));
	}

	for (int i = 1; i <= m; ++i) {
		int x, y; in >> x >> y;
		event.push_back(Event(x, y, i));
	}

	Event last;
	int itrUp = 0, itrDown = 0;
	sort(event.begin(), event.end());
	for (auto itr : event) {
		if (itr.type == 0) {
			// insert element :)
			
			// insert up
			while (itrUp >= 2 and arieTriunghi(itr, evUp[itrUp - 1], evUp[itrUp]) >= 0) {
				--itrUp;
			}
			evUp[++itrUp] = itr;

			// insert down
            while (itrDown >= 2 and arieTriunghi(itr, evDown[itrDown], evDown[itrDown - 1]) >= 0) {
				--itrDown;
			}
			evDown[++itrDown] = itr;

			if (itrUp >= 2) {
				arieUp[itrUp] = 1LL * (evUp[itrUp].x - evUp[itrUp - 1].x) * (evUp[itrUp].y + evUp[itrUp - 1].y);
				arieDown[itrDown] = 1LL * (evDown[itrDown].x - evDown[itrDown - 1].x) * (evDown[itrDown].y + evDown[itrDown - 1].y);

				arieUp[itrUp] += arieUp[itrUp - 1];
				arieDown[itrDown] += arieDown[itrDown - 1];
			}
			last = itr;
		} else {
			int copyItrUp = itrUp;
			int copyItrDown = itrDown;

//			cerr << itrUp << '\t' << itrDown << '\n';
			// query :(
			if (itrUp <= 1) {
				rez[itr.type] = 0;
				continue;
			} 

            if (itr.x == last.x) {
				// am citit prost problema la inceput :)
				// doom
				if (itr.y >= last.y) {
					itrUp--;
				} else {
					itrDown--;
				}
			}

			// incercam sa scoatem

			for (int p = 20; p >= 0; --p) {
				if (itrUp - (1 << p) >= 1) {
					int _itr = itrUp - (1 << p);
					if (arieTriunghi(itr, evUp[_itr], evUp[_itr + 1]) >= 0) {
						itrUp = _itr;
					}
				}
			}

 			for (int p = 20; p >= 0; --p) {
				if (itrDown - (1 << p) >= 1) {
					int _itr = itrDown - (1 << p);
					if (arieTriunghi(itr, evDown[_itr + 1], evDown[_itr]) >= 0) {
						itrDown = _itr;
					}
				}
			}
			int64 Rez = arieUp[itrUp] + 1LL * (itr.x - evUp[itrUp].x) * (itr.y + evUp[itrUp].y);
			Rez -= (arieDown[itrDown] + 1LL * (itr.x - evDown[itrDown].x) * (itr.y + evDown[itrDown].y));
			rez[itr.type] = Rez;

			itrUp = copyItrUp;
			itrDown = copyItrDown;
		}
	}

	for (int i = 1; i <= m; ++i) {
		out << fixed << setprecision(1) << rez[i] / 2.0 << '\n';
	}
	return 0;
}
