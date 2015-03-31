//Problem dstar from Infoarena
// "We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

ifstream in("dstar.in");
ofstream out("dstar.out");

priority_queue<double> pq;

int main() {
	int n, q; in >> n >> q;
	double sum = 360.0;
	for (int i = 1; i <= n; ++i) {
		double x; in >> x;
		sum -= x;
		pq.push(x);
	}
	pq.push(sum);
	for (int i = 1; i <= q; ++i) {
		double x = pq.top();
		pq.pop();
		pq.push(x / 2.0);
		pq.push(x / 2.0);
	}
	out << fixed << setprecision(9) << pq.top() << '\n';
	return 0;
}
