#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

#define int64 long long

ifstream in("tarabe.in");
ofstream out("tarabe2.out");

priority_queue<pair<int64, int>> pq;

int main() {
	int n, k;
	in >> n >> k;
	for (int i = 1; i <= n; ++i) {
		int b, a;
		in >> b >> a;
		pq.push(make_pair(1LL * -a, b));
	}
	int64 rez = 0;
	for (; k; --k) {
		pair<int64, int> a = pq.top();
		pq.pop();
		rez -= a.first;
		a.first -= a.second;
		pq.push(a);
	}
	out << rez << '\n';
	in.close();
	out.close();
	return 0;
}
