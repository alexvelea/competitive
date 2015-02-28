//Problem #B from Codeforces MindCodingFinal2
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

bool edge[105][105];

int main() {
	int k, n, m;
	cin >> k >> n >> m;
	if (k == 1) {
		cout << "0\n";
		return 0;
	}
	if (k == 2) {
    	if (n == 2 and m == 2) {
			cout << "-1";
			return 0;
		}
		if (n == 1 and m == 1) {
			cout << "-1";
			return 0;
		}
		if (n == 1 and m == 2) {
			cout << "0";
			return 0;
		}
		if (n == 2 and m == 1) {
			cout << "1\n1 2\n";
			return 0;
		}
	}
	if (k == 3) {
		if (n == 1 and m == 1) {
	    	cout << "-1";
			return 0;
		}
 		if (n == 1 and m == 2) {
	    	cout << "-1";
			return 0;
		}   	
 		if (n == 1 and m == 3) {
	    	cout << "1\n1 2";
			return 0;
		}   	
 		if (n == 2 and m == 1) {
	    	cout << "-1";
			return 0;
		}   	
 		if (n == 2 and m == 2) {
	    	cout << "-1";
			return 0;
		}   	
 		if (n == 2 and m == 3) {
	    	cout << "1\n1 2";
			return 0;
		}   	
 		if (n == 3 and m == 1) {
	    	cout << "2\n1 2\n2 3\n";
			return 0;
		}   	
 		if (n == 3 and m == 2) {
	    	cout << "2\n1 2\n2 3\n";
			return 0;
		}   	
 		if (n == 3 and m == 3) {
	    	cout << "-1";
			return 0;
		}   	
	}
	if (k > 3) {
		if (n != k and m != k)
			cout << "-1\n";
		if (m == k) {
			cout << n - 1 << '\n';
			for (int i = 1; i < n; ++i)
				cout << i << ' ' << i + 1 << '\n';
		} else {
			for (int i = 1; i <= k; ++i)
				for (int j = i + 1; j <= k; ++j)
					edge[i][j] = true;
			for (int i = 1; i < m; ++i)
				edge[i][i + 1] = edge[i + 1][i] = false;
			int r = 0;
			for (int i = 1; i <= k; ++i)
				for (int j = i + 1; j <= k; ++j)
					r += edge[i][j];
			cout << r << '\n';
			for (int i = 1; i <= k; ++i)
				for (int j = i + 1; j <= k; ++j)
					if (edge[i][j])
						cout << i << ' ' << j << '\n';
			cout << '\n';
		}
	}
	return 0;
}

