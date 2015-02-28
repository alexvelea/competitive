#include <cstdio>
#include <fstream>
#include <iostream>
using namespace std;

ifstream in("radixsort.in");
ofstream out("radixsort.out");

const int kMaxN = 10000005, kMask = 8;

int n;
int ap[1 << kMask];

int aux[kMaxN], el[kMaxN];

void solve(int p) {
	int mask = (1 << kMask) - 1;
 	
    for (int i = 0; i <= mask; ++i)
		ap[i] = 0;

	for (int i = 1; i <= n; ++i)
		ap[(el[i] & (mask << p)) >> p]++;
	
	for (int i = 1; i <= mask; ++i)
		ap[i] += ap[i - 1];
	for (int i = mask; i > 0; --i) {
		ap[i] = ap[i - 1];
	}
	ap[0] = 0;

	for (int i = 1; i <= n; ++i)
		aux[++ap[(el[i] & (mask << p)) >> p]] = el[i];
	for (int i = 1; i <= n; ++i)
		el[i] = aux[i];
}

int main() {

    freopen("radixsort.in", "r", stdin);
	freopen("radixsort.out", "w", stdout);

 	int a, b, c;
	scanf("%d %d %d %d", &n, &a, &b, &c);
	el[1] = b;
	for (int i = 2; i <= n; ++i)
		el[i] = (1LL * a * el[i - 1] + b) % c;

	for (int i = 0; i < 32; i += kMask)
		solve(i);

	for (int i = 1; i <= n; i += 10)
		printf("%d ", el[i]);
	return 0;
}
