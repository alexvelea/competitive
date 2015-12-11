#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int kMaxP = 25000, kMaxN = 225;

ifstream in("sume.in");
ofstream out("sume.out");

int p, n;

priority_queue <int> pq;
int sum[kMaxP], el[kMaxN];

int main() {
	in >> p;
	for (int i = 1; i <= p; ++i)
		in >> sum[i];

	sort(sum + 1, sum + p + 1);
	reverse(sum + 1, sum + p + 1);

	n = sqrt(2 * p);
	n++;

	if (n * (n - 1) / 2 != p) {
		out << "-1\n";
		return 0;
	}

	for (int dr = 3; dr <= n; ++dr) {
		el[1] = sum[1] + sum[2] - sum[dr];
		el[1] /= 2;
		int N = dr;
		for (int i = 1; i < N; ++i)
			el[i + 1] = sum[i] - el[1];
 		int ind = 1;
    	
		while (pq.size())
			pq.pop();
		for (int i = 1; i <= N; ++i)
			for (int j = i + 1; j <= N; ++j)
				pq.push(el[i] + el[j]);

		bool sol = true;

 		for (int e = N + 1; e <= n and sol; ++e) {
			int x;
			while (pq.size()) {
				x = pq.top();
				if (x > sum[ind]) {
					sol = false;
					break;
				}
				if (x == sum[ind]) {
					pq.pop();
					++ind;
					continue;
				}
				if (x < sum[ind]) 
					break;
		   	} 
			if (not sol)
				break;
			el[e] = sum[ind] - el[1];
			for (int i = 1; i < e; ++i)
				pq.push(el[i] + el[e]);
		}
		if (sol) {
 			while (ind <= p) {
				int x = pq.top();
				if (x > sum[ind]) {
					sol = false;
					break;
				}
				if (x == sum[ind]) {
					pq.pop();
					++ind;
					continue;
				}
				if (x < sum[ind])
					break;
		   	}
			if (pq.size() == 0) {
				out << n << '\n';
				for (int i = 1; i <= n; ++i)
					out << el[i] << ' ';
				return 0;
			}
		}
	}
	out << "-1\n";
	return 0;
}
