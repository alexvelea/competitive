#include <iostream>
#include <vector>
using namespace std;
const int max_n = 200005;
int a[max_n];

int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	long long sum = 0;
	int behind = 1;
	vector<int> rez;
	for (int i = 2; i <= n; ++i) {
		long long d = sum - 1LL * behind * (n - i) * a[i];
		if (d < k) {
			rez.push_back (i);
		} else {
			sum += behind * a[i];
			behind ++;
		}
	}
	for (int i = 0; i < int(rez.size()); ++i)
		cout << rez[i] << '\n';
	return 0;
}
