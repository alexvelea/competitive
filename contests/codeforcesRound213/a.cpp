#include <iostream>
#include <vector>
using namespace std;

int ap[40000];

int main() {
	string text;
	int a, sum, b;
	long long rez = 0;
	cin >> a;
	cin >> text;
	int n = text.size();
	for (int i = 0; i < n; ++i) {
		sum = 0;
		for (int j = i; j < n; ++j) {
			sum += text[j] - '0';
 			ap[sum] ++;
		}
	}
	if (a == 0) {
		rez = 1LL * (n) * (n + 1) / 2;
		rez -= ap[0];
		rez = 2LL * rez * ap[0];
		rez = 1LL * rez + 1LL * ap[0] * ap[0];
		cout << rez << '\n';
		return 0;
	}
	for (int i = 0; i < n; ++i) {
		sum = 0;
		for (int j = i; j < n; ++j) {
			sum += text[j] - '0';
			if (sum != 0 and a % sum == 0) {
				b = a / sum;
				if (b < 40000)
					rez += 1LL * ap[b];
			}
		}
	}
	cout << rez << '\n';
	return 0;
}
