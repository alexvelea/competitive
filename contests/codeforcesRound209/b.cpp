#include <algorithm>
#include <iostream>
using namespace std;
int el[2 * 50005];
int main() {
	int n, k;
	cin >> n >> k;
	n *= 2;
	for (int i = 1; i <= n; ++i)
		el[i] = i;
	for (int i = 1; i <= n / 2; ++i)
		swap(el[i * 2 - 1], el[2 * i]);
	k *= 2;
	int sum = 0;
	int ind = 1;
	while (sum < k) {
		sum += 2;
		swap(el[ind * 2 - 1], el[ind * 2]);
		ind ++;
	}
	for (int i = 1; i <= n; ++i)
		cout << el[i] << ' ';
}
