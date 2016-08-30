#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>
using namespace std;

#define int64 long long

ifstream fin("per.in");
ofstream fout("per.out");

int doDeqShit(vector<int> el, int k, int target) {
	int dSt = 0, dDr = -1;
    int dSum = 0;
    vector<int> deq(el.size(), 0);
    for (int i = 0; i < int(el.size()); i += 1) {
        if (deq[dSt] == i - k) {
            dSt += 1;
        }
 
        while (dDr >= dSt and el[i] <= el[deq[dDr]]) {
            dDr -= 1;
        }
 
        deq[++dDr] = i;
        if (i >= k) {
        	if (el[deq[dSt]] >= target) {
        		dSum += 1;
        	}
        }
    }
    return dSum;
}

int main() {
	int n, k; fin >> n >> k;
	string el; fin >> el;
	int rez = 0;
	vector<int> dp(n, 0);
	for (int u = 1; k * u <= n; u += 1) {
		for (int i = 0; i < u; i += 1) {
			dp[i] = 0;
		}
		for (int i = u; i < n; i += 1) {
			if (el[i] == el[i - u]) {
				dp[i] = dp[i - u] + 1;
			} else {
				dp[i] = 0;
			}
		}

		rez += doDeqShit(dp, u, k - 1);
	}
	fout << rez << '\n';
	return 0;
}