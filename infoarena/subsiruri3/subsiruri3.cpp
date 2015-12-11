#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("subsiruri3.in");
ofstream out("subsiruri3.out");

const int Mod = 666013, inf = 0x3f3f3f3f, kMaxN = 1000005;
int n, k;

int aib[kMaxN];
int el[kMaxN];
vector<int> uniq;

void mod(int &a) {
	if (a >= Mod)
		a -= Mod;
}

void aib_update(int ind, int val) {
	while (ind <= n) {
		aib[ind] += val;
		mod(aib[ind]);
		ind += ind & (-ind);
	}
}
int aib_query(int ind) {
	int rez = 0;
	while (ind) {
		rez += aib[ind];
		mod(rez);
		ind -= ind & (-ind);
	}                       
	return rez;
}

int main() {
	int t;
	in >> t;
	while (t--) {
		in >> n >> k;
		uniq.clear();
		for (int i = 1; i <= n; ++i) {
			in >> el[i];
			uniq.push_back(el[i]);
		}
		uniq.push_back(-2 * inf);
		sort(uniq.begin(), uniq.end());
		uniq.resize(unique(uniq.begin(), uniq.end()) - uniq.begin());
 		
        int Rez = 0;

		for (int i = 1; i <= n; ++i) {
	    	int r = aib_query(lower_bound(uniq.begin(), uniq.end(), el[i]) - uniq.begin());
			int st = lower_bound(uniq.begin(), uniq.end(), el[i] - k - 1) - uniq.begin();
			while (uniq[st] >= el[i] - k)
				--st;
			r -= aib_query(st);
			r++;
			if (r < 0)
				r += Mod;
			if (r >= Mod)
				r -= Mod;

			Rez += r;
			mod(Rez);
			aib_update(lower_bound(uniq.begin(), uniq.end(), el[i]) - uniq.begin(), r);
		}
	
		out << Rez << '\n';

		for (int i = 0; i <= n; ++i)
			aib[i] = 0;
	}

    return 0;
}
