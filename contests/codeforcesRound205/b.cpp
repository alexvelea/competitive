#include <iostream>
using namespace std;

const int max_n = 100005;

int sum[max_n], sum_el[max_n], T[max_n], el[max_n];
void get_max(int &a, int b) {
	if (a < b)
		a = b;
}

int main() {
	int n;
    cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> T[i];
	for (int i = 1; i <= n; ++i) {
		char c;
		cin >> c;
		el[i] = c - '0';
	}
    for (int i = 1; i <= n; ++i) {
		sum[i] = sum[i - 1] + T[i] * el[i];
   		sum_el[i] = sum_el[i - 1] + T[i];
	} 
	int mx = sum[n];
	for (int i = 1; i <= n; ++i)
		if (el[i])
			get_max(mx, sum[n] - sum[i] + sum_el[i - 1]);
	cout << mx << "\n";
	return 0;
}
