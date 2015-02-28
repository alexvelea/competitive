#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

ifstream in("copaci.in");
ofstream out("copaci.out");

const int kMaxN = 100005;

pair<int, int> coord[kMaxN];

int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main() {
	int n;
	in >> n;
	for (int i = 0; i < n; ++i)
		in >> coord[i].first >> coord[i].second;
	coord[n] = coord[0];
	long long a = 0;
	for (int i = 0; i < n; ++i) {
		a += 1LL * coord[i].first * coord[i + 1].second - 1LL * coord[i].second * coord[i + 1].first;
	}
	long long b = 0;
	for (int i = 0; i < n; ++i) {
		b += 1LL * gcd(abs(coord[i].first - coord[i + 1].first), abs(coord[i].second - coord[i + 1].second));
	}
	if (a < 0)
		a *= -1LL;
	// A = I + b/2 - 1
	// I = A + 1 - b / 2
//	a += 2LL;
//	a -= b;
// 	a = a / 2LL + b;
//	out << a << '\n';
  	out << 1LL * (a / 2LL) - (b / 2LL) + 1LL << '\n';  
	return 0;
}
