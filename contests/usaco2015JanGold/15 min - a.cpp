//Problem A from Codeforces Round usaco2015JanGold
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

const int inf = 0x3f3f3f3f, kMaxN = 505;

ifstream in("cowrect.in");
ofstream out("cowrect.out");

struct Cow {
	int x, y;
	bool good;
	bool operator < (const Cow &rhs) const {
		return x < rhs.x;
	}
} cow[kMaxN];

priority_queue<int> pqAbove, pqBelow;

int main() {
	int n;
	in >> n;
	for (int i = 1; i <= n; ++i) {
		char c;
		in >> cow[i].x >> cow[i].y >> c;
		if (c == 'H') {
            cow[i].good = true;
		} else {
			cow[i].good = false;
		}
	}
	sort(cow + 1, cow + n + 1);

    int mxCowsInside = 0;
	int64 mnRectSize = 1LL * inf * inf;

	for (int st = 1; st <= n; ++st) {
		if (cow[st].good == false) {
			;
		} else {
			int mxY = -inf, mnY = +inf;
			int targetY = cow[st].y;
			while (pqAbove.size())
				pqAbove.pop();
			while (pqBelow.size())
				pqBelow.pop();

			int dr = st, cowsInside = 0;
			
			pqAbove.push(cow[st].y);
			pqBelow.push(cow[st].y);

			while (dr <= n and mxY != targetY and mnY != targetY) {
				int x = cow[dr].x;
				while (dr <= n and cow[dr].x == x) {
					if (cow[dr].good) {
						int y = cow[dr].y;
						if (y < targetY) {
							// below
							pqAbove.push(y);
						} else if (y > targetY) {
							// above
							pqBelow.push(-y);
						}
						++cowsInside;	
					} else {
						int y = cow[dr].y;
						if (y == targetY)
							mxY = mnY = targetY;
						if (y < targetY) {
							mxY = max(mxY, y);
						} else {
							mnY = min(mnY, y);
						}
					}
				}
				while (pqAbove.size() and pqAbove.top() >= mxY) {
					pqAbove.pop();
					--cowsInside;
				}

				while (pqBelow.size() and -pqBelow.top() <= mnY) {
					pqBelow.pop();
					--cowsInside;
				}

				int64 rectSize = (x - cow[st].x) * (pqAbove.top() + pqBelow.top());

				if (cowsInside > mxCowsInside or
					(cowsInside == mxCowsInside and rectSize < mnRectSize)) {
					mxCowsInside = cowsInside;
					mnRectSize = rectSize;
				}
			}

		}
	}
	return 0;
}
