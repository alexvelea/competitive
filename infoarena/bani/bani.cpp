#include <cmath>

#include <iomanip>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("bani.in");
ofstream out("bani.out");

const int kMaxN = 1005;

vector<pair<int, int> > A;
vector<pair<double, int> > B;

double bestB[kMaxN];
int bestA[kMaxN];

int main() {
	int t;
	in >> t;
	while (t--) {
		int n, g;
		in >> n >> g;
		A.clear();
		B.clear();
		for (int i = 1; i <= n; ++i) {
        	int a, b, t;
			in >> a >> b >> t;
 			if (t == 0) {
	        	A.push_back(make_pair(a, b));
			} else {
				B.push_back(make_pair(1.0 * a / b, b));
			}
		}
		
		for (int i = 0; i <= g; ++i) {
			bestA[i] = 0;
			bestB[i] = 0.0;
		}

        sort(B.begin(), B.end());
		reverse(B.begin(), B.end());
		int st = 0;
 		for (int i = 1; i <= g; ++i) {
			if (st == int(B.size())) {
				bestB[i] = bestB[i - 1];
				continue;
			}

			bestB[i] = bestB[i - 1] + B[st].first;
			B[st].second--;
			if (B[st].second == 0)
				++st;
		}

		for (int i = 0; i < int(A.size()); ++i) {
			for (int j = g; j >= A[i].second; --j) {
	        	bestA[j] = max(bestA[j], bestA[j - A[i].second] + A[i].first);
			}
		}

		double mx = 0.0;
		for (int i = 0; i <= g; ++i)
			mx = max(mx, bestA[i] + bestB[g - i]);
		out << fixed << setprecision(9) << mx << '\n';
	}
    return 0;
}
