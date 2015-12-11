#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 3e5 + 5, inf = 0x3f3f3f3f;

ifstream fin("seriale.in");
ofstream fout("seriale.out");

vector<int> nEl;

bool canContinue[kMaxN];
int nPos[kMaxN], goRight[kMaxN];

int main() {
	int n, k; fin >> n >> k;
	for (int i = 1; i <= n; i += 1) {
		int x; fin >> x; nEl.push_back(x);
		nPos[x] = i;
	}

	bool isSorted = true;
	for (int i = 0; i + 1 < int(nEl.size()); i += 1) {
		if (nEl[i] > nEl[i + 1]) {
			isSorted = false;
		}
	}

	if (isSorted) {
		fout << "0\n";
		return 0;
	}

	sort(nEl.begin(), nEl.end());

	nEl.pop_back();
	int maxEl = n + k - 1;

	for (int i = 0; i + 1 < int(nEl.size()); i += 1) {
		canContinue[i] = (nPos[nEl[i]] < nPos[nEl[i + 1]]);
	}

	for (int i = int(nEl.size()) - 1; i >= 0; i -= 1) {
		if (not canContinue[i]) {
			goRight[i] = i;
		} else {
			goRight[i] = goRight[i + 1];
		}
	}

	int best = inf;	

	for (int i = 0; i < int(nEl.size()); i = goRight[i] + 1) {
		int st = i;
		int dr = goRight[i];
		// cerr << "~~~~~~~\n";
		// cerr << st << '\t' << dr << '\n';

		int mnEl = 1;
		if (st != 0) {
			mnEl = nEl[st - 1] + 1;
		}

		int mxEl = maxEl;
		if (dr + 1 < int(nEl.size())) {
			mxEl = nEl[dr + 1] - 1;
		}

		// cerr << mnEl << '\t' << mxEl << '\n';

		if (mxEl - mnEl + 1 < n) {
			continue;
		}

		int Time = 0;
		bool ok = true;
		int small, big;

		while (ok) {
			ok = false;
			if (Time < max(2 * st - 1, 2 * (int(nEl.size()) - dr - 1))) {
				Time = max(2 * st - 1, 2 * (int(nEl.size()) - dr - 1));
				ok = true;
			}


			small = (Time + 1) / 2;
			big = (Time) / 2;
			while (nEl[st] <= small) {
				st += 1;
			}

			while (maxEl - nEl[dr] < big) {
				dr -= 1;
			}

			if (st > dr) {
				break;
			}
		}

		// cerr << Time << '\n';
		// cerr << st << '\t' << dr << '\n';

		if (st > dr) {
			continue;
		}

		if (mxEl - small < n) {
			continue;
		}

		if ((maxEl - mnEl + 1) - big < n) {
			continue;
		}

		if (((st) + (int(nEl.size()) - dr - 1) + 1) + (dr - st + 1) < n) {
			continue;
		}

		best = min(best, Time + 1);
	}

	if (best == inf) {
		fout << "-1\n";
	} else {
		fout << best << '\n';
	}
	return 0;
}