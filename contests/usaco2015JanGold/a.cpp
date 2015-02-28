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
		if (x == rhs.x)
			return good > rhs.good;
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
	int64 mnRectSize = 0;

	for (int st = 1; st <= n; ++st) {
		if (cow[st].good == false) {
			;
		} else {
			int mxY = +inf, mnY = -inf;
			int targetY = cow[st].y;
			while (pqAbove.size())
				pqAbove.pop();
			while (pqBelow.size())
				pqBelow.pop();

			int dr = st, cowsInside = 0;
			
			pqAbove.push(cow[st].y);
			pqBelow.push(-cow[st].y);

			while (dr <= n) {
				int x = cow[dr].x;
				while (dr <= n and cow[dr].x == x) {
					if (cow[dr].good) {
						int y = cow[dr].y;
						if (y < targetY) {
							// below
 							pqBelow.push(-y);
						} else if (y > targetY) {
							// above
 							pqAbove.push(y);   						
						}
						++cowsInside;	
					} else {
						int y = cow[dr].y;
						if (y == targetY)
							mxY = mnY = targetY;
						if (y < targetY) {
							mnY = max(mnY, y);
						} else {
							mxY = min(mxY, y);
						}
					}
					++dr;
				}
				
				if (mxY == targetY or mnY == targetY)
					break;

				while (pqAbove.size() and pqAbove.top() >= mxY) {
					pqAbove.pop();
					--cowsInside;
				}

				while (pqBelow.size() and -pqBelow.top() <= mnY) {
					pqBelow.pop();
					--cowsInside;
				}

				int64 rectSize = (x - cow[st].x) * (pqAbove.top() + pqBelow.top());

//				cerr << st << '\t' << pqAbove.top() << '\t' << pqBelow.top() << '\t' << mxY << '\t' << mnY << '\t' << cowsInside << '\t' << rectSize << '\n';

				if (cowsInside > mxCowsInside or
					(cowsInside == mxCowsInside and rectSize < mnRectSize)) {
					mxCowsInside = cowsInside;
					mnRectSize = rectSize;
				}
			}

		}
	}
	out << mxCowsInside << '\n' << mnRectSize << '\n';
	return 0;
}
