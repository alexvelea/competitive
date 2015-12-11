#include <fstream>
#include <iostream>
using namespace std;

ifstream in("rompetrol.in");
ofstream out("rompetrol.out");

const int max_n = 100005, inf = 0x3f3f3f3f;
#define ll long long

int n, k, d[max_n], el[max_n], a[max_n];
ll sp_1[max_n], sp_n[max_n], sum_el[max_n];
ll down[max_n], up[max_n], down_last[max_n], up_last[max_n];
int deq[max_n];

pair <ll, ll> down_time (int o, int j) {
	return make_pair(1LL * (up_last[o] - up_last[j] + sp_n[o + 1] - sp_n[j + 1]), 1LL *  (sum_el[j] - sum_el[o]));
}
pair <ll, ll> up_time (int o, int j) {
	return make_pair(1LL * (down[j] - down[o] - sp_1[j] + sp_1[o] + d[j] * sum_el[j] - d[o] * sum_el[o]), 1LL * (d[j] - d[o]));
}


void solve() {
	int st, dr;
	st = 1;
	dr = 0;
	for (int i = 1; i <= n; ++i) {
		while (dr > st) {
			pair <ll, ll> a = down_time (deq[dr - 1], deq[dr]), b = down_time(deq[dr], i);
            if ((up_last[i] < up_last[deq[dr]]) || (a.first * b.second <= b.first * a.second)) {
				--dr;
				continue;
			}
			break;
		}
		deq[++dr] = i - 1;

		while (st < dr) {
			pair <ll, ll> x = down_time (deq[st], deq[st + 1]);
			if ((up_last[deq[st]] > up_last[deq[st + 1]]) || (1LL * (d[n] - d[i]) * x.second < x.first)) {
				++st;
				continue;
			}
			break;
		}	
		int j = deq[st];
		down[i] = 1LL * up_last[j] + sp_n[j + 1] - sp_n[i + 1] - 1LL * (d[n] - d[i]) * (sum_el[i] - sum_el[j]) + a[i];
	}
	st = 1;
	dr = 0;
	for (int i = 1; i <= n; ++i) {
		while (dr > st) { 
			pair <ll, ll> a = up_time (deq[dr - 1], deq[dr]), b = up_time (deq[dr], i);
			if ((down[i] < down[deq[dr]]) || (a.first * b.second >= b.first * a.second)) {
				--dr;
				continue;
			}

			break;
		}
		deq[++dr] = i;
		while (st < dr) {
			pair <ll, ll> a = up_time (deq[st], deq[st + 1]);
			if ((down[deq[st]] >= down[deq[st + 1]]) || (1LL * sum_el[i] * a.second >= a.first)) {
				++st;
				continue;
			}
			break;
		}
		int j = deq[st];
		up[i] = 1LL * down[j] + sp_1[i] - sp_1[j] -1LL * d[j] * (sum_el[i] - sum_el[j]);
	}
	for (int i = 0; i <= n; ++i)
		up_last[i] = up[i], down_last[i] = down[i];
}


int main() {
	in >> n >> k;
	for (int i = 1; i <= n; ++i)
		in >> d[i] >> el[i] >> a[i];
	for (int i = 1; i <= n; ++i) {
		sum_el[i] = sum_el[i - 1] + el[i];
		sp_1[i] = sp_1[i - 1] + 1LL * d[i] * el[i];
	}
	for (int i = n; i; --i)
		sp_n[i] = sp_n[i + 1] + 1LL * (d[n] - d[i]) * el[i];
	for (int i = 0; i <= n; ++i)
		up[i] = down[i] = up_last[i] = down_last[i] = 1LL * inf * inf;
	up_last[0] = 0;
	down[0] = 1LL * inf * inf;
	for (int i = 1; i <= k; ++i)
		solve();
	out << up[n] << '\n';
	return 0;
}
