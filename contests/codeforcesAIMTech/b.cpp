// problem B from codeforces AIM Tech - 623
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 1e5, inf = 0x3f3f3f3f;

#define int64 long long

int a, b;

int gcd(int a, int b) {
	if (a == 0 or b == 0) {
		return max(a, b);
	}

	if (a == 1 or b == 1) {
		return 1;
	}

	return gcd(b, a % b);
}

int64 solve(vector<int> v) {
	int g_st = 0;
	vector<pair<int, int> > g_dr(v.size() + 1, {0, 0});
	for (int i = int(g_dr.size()) - 2; i >= 0; i -= 1) {
		g_dr[i].first = gcd(g_dr[i + 1].first, v[i]);
		g_dr[i].second = g_dr[i].first;
	}
	int dr = 0;
	int bad_pos = -1;
	int64 min_cost = 1LL * inf * inf;
	for (int st = 0; st < int(v.size()) - 1; st += 1) {
		while (gcd(g_st, g_dr[dr].first) == 1 and gcd(g_st, g_dr[dr].second) == 1) {
			if (bad_pos == dr) {
				bad_pos = -1;
			}
			dr += 1;
		}

		int64 current_cost = (bad_pos == -1) ? (0) : (b);
		current_cost += 1LL * (dr - st) * a;
		cout << current_cost << '\t' << st << '\t' << dr << '\t' << g_st << '\n';
		

		if (current_cost < min_cost) {
			min_cost = current_cost;
		}

		if (bad_pos == -1 and dr != 0) {
			g_dr[dr - 1].first = gcd(g_dr[dr].first, v[dr - 1] - 1);
			g_dr[dr - 1].second = gcd(g_dr[dr].second, v[dr - 1] - 1);

			if (gcd(g_st, g_dr[dr - 1].first) == 1 and gcd(g_st, g_dr[dr - 1].second) == 1) {
				
			} else {
				bad_pos = dr - 1;
				dr -= 1;
				while (dr >= st and not (gcd(g_st, g_dr[dr].first) == 1 and gcd(g_st, g_dr[dr].second) == 1)) {
					if (dr > 0) {
						g_dr[dr - 1].first = gcd(v[dr - 1], g_dr[dr].first);
						g_dr[dr - 1].second = gcd(v[dr - 1], g_dr[dr].second);
					}
					dr -= 1;
				}

				dr += 1;
			}

			int64 current_cost = (bad_pos == -1) ? (0) : (b);
			current_cost += 1LL * (dr - st) * a;
			cout << current_cost << '\t' << st << '\t' << dr << '\t' << g_st << '\n';

			if (current_cost < min_cost) {
				min_cost = current_cost;
			}
		}

		g_st = gcd(g_st, v[st]);
		cout << "!" << st << '\t' << g_st << '\n';
		
		if (g_st == 1) {
			break;
		}
	}

	cout << "\n\n\n";

	return min_cost;
}

int main() {
	ios_base::sync_with_stdio(false);
	vector<int> v;
	int n; cin >> n >> a >> b;
	while (n--) {
		int x; cin >> x;
		v.push_back(x);
	}
	
	int64 rez = 1LL * inf * inf;
	rez = min(rez, solve(v));
	reverse(v.begin(), v.end());
	rez = min(rez, solve(v));
	cout << rez << '\n';
	return 0;
}