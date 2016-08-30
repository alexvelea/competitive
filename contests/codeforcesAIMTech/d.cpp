// problem D from codeforces AIM Tech - 623
#include <cmath>

#include <iomanip>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMaxN = 1e5, inf = 0x3f3f3f3f;

double dp[200];

int main() {
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	vector<long double> chx;
	long double sum = 0;
	for (int i = 1; i <= n; i += 1) {
		double x; cin >> x;
		x /= 100.0;
		chx.push_back(x);
	}

	vector<long double> chx_not_selected(n, 1.0);
	vector<int> how_many_times(n, 1);

	
	int index = n;

	long double last_finish_chx = 1.0;
	for (int i = 0; i < n; i += 1) {
		chx_not_selected[i] = 1 - chx[i];
		last_finish_chx *= 1 - chx_not_selected[i];
	}

	long double rez = index * last_finish_chx;

	while (index <= 1000000) {
		int chosen_person = -1;
		long double best_finish_chx = -1.0;
		for (int i = 0; i < n; i += 1) {
			long double current_chx = last_finish_chx / (1 - chx_not_selected[i]);
			current_chx *= (1 - chx_not_selected[i] * (1 - chx[i]));
			if (current_chx > best_finish_chx) {
				best_finish_chx = current_chx;
				chosen_person = i;
			}
		}

		index += 1;
		rez += (best_finish_chx - last_finish_chx) * index;
		how_many_times[chosen_person] += 1;

		// cerr << best_finish_chx << '\n';
		// for (int i = 0; i < n; i += 1) {
		// 	cerr << i << '\t' << chx_not_selected[i] << '\n';
		// }
		// cerr << '\n';

		last_finish_chx /= (1 - chx_not_selected[chosen_person]);
		chx_not_selected[chosen_person] *= (1 - chx[chosen_person]);
		last_finish_chx *= (1 - chx_not_selected[chosen_person]);
	}

	cout << fixed << setprecision(9) << rez << '\n';

	return 0;
}