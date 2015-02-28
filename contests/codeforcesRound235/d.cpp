//Problem #D from Codeforces 235
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE__
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define fi first
#define se second
#define int64 long long

const int inf = 0x3f3f3f3f;

int64 rez[1 << 18][100];

int main() {
	int k;
	string el;
	cin >> el >> k;
	sort(el.begin(), el.end());

	for (int i = 0; i < el.size(); ++i) {
		if (el[i] != '0' and (i == 0 or el[i - 1] != el[i]))
			rez[1 << i][(el[i] - '0') % k] = 1;
	}
	for (int st = 1; st < 1 << int(el.size()); ++st) 
		for (int sum = 0; sum < k; ++sum) {
			for (int l = 0; l < int(el.size()); ++l)
				if (((st & (1 << l)) == 0) and (l == 0 or (el[l - 1] != el[l] or ((1 << (l - 1)) & st)))) {
					rez[st | (1 << l)][(sum * 10 + el[l] - '0') % k] += rez[st][sum];
				}
		}
	cout << rez[(1 << el.size()) - 1][0] << '\n';
    return 0;
}

