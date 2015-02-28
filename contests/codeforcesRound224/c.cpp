#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 100005;

vector<int> rez;

int el[kMaxN], sum[kMaxN];

void show(vector<int> x) {
	cout << x.size() << '\n';
	sort(x.begin(), x.end());
	for (int i = 0; i < int(x.size()); ++i)
		cout << x[i] << ' ';
	return ;
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> el[i];
	sort(el + 1, el + n + 1);
	for (int i = 1; i < n; ++i)
		sum[i] = el[i + 1] - el[i];
	sort(sum + 1, sum + n);
	if (n == 1) {
		cout << "-1\n";
		return 0;
	}
	if (n == 2) {

		if (el[1] == el[2]) {
			rez.push_back(el[1]);
		} else {
 			rez.push_back(el[1] - (el[2] - el[1]));
			rez.push_back(el[2] + (el[2] - el[1]));   		
			if((el[1] + el[2]) % 2 == 0)
				rez.push_back((el[1] + el[2]) / 2);
		}
		show(rez);
		return 0;
	}
	if (el[1] == el[n]) {
		rez.push_back(el[1]);
		show(rez);
		return 0;
	}
	if (sum[1] == sum[n - 1]) {
		// perfect
 		rez.push_back(el[1] - sum[1]);
		rez.push_back(el[n] + sum[1]);
		show(rez);
		return 0;
	}
 	if (sum[1] == sum[n - 2]) {
		if (sum[1] * 2 == sum[n - 1]) {
			for (int i = 1; i < n; ++i)
				if (el[i + 1] - el[i] == sum[n - 1]) {
					cout << "1\n" << sum[1] + el[i] << '\n';
					return 0;
				}
		} else
			cout << '0';
	} else
		cout << '0';
	return 0;
}
