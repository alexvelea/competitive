#include <iostream>
#include <vector>
using namespace std;
int prim[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

vector<int> number[1<<10], ind[20];
vector<int> rez;

int solve(int nr_el, int max_el) {
	vector<int> last, next;
	last.clear();
	last.push_back(1);
	for (int i = 0; i < 10; ++i) {
		rez.clear();
		next.clear();
		for (int j = 0; j < int(last.size()); ++j) {
	   		int el = last[j];
			while (el <= max_el) {
				next.push_back(el);
				el *= prim[i];
			}
		} 
		last = next;
		int req[20];
		for (int j = 0; j <= i; ++j)
			req[j] = nr_el / 2;
			
		for (int j = 0; j < (1 << (i + 1)); ++j)
			number[j].clear();
		for (int j = 0; j < int(next.size()); ++j) {
			int el = next[j];
			int o = 0;
			for (int p = 0; p <= i; ++p) 
				if (el % prim[p] == 0)
					o |= 1<<p;
			number[o].push_back(el);
		}
 		for (int j = 0; j < 20; ++j)
			ind[j].clear();
		for (int j = 0; j < (1 << (i + 1)); ++j) {
			int el = j;
			int sum = 0;
			while (el) {
				sum ++;
				el -= el & (-el);
			}       
			if (number[j].size())
	 			ind[sum].push_back(j);
		}
		int k = nr_el;
		for (int j = 20; j >= 0; --j) {
 			int ok = true;
			while (ok) {
				ok = false;
				for (int it = 0; k and it < int(ind[j].size()); ++it) {
					int el = ind[j][it];
					if (k and number[el].size()) {
						for (int p = 0; p < 10; ++p)                   	
							if (el & (1 << p))
								req[p] --;
						rez.push_back(number[el].back());
						number[el].pop_back();
						k--;
						ok = true;
					}
				}
			}
		}
		if (k)
			continue;

		for (int j = 0; j <= i; ++j)
			if (req[j] >= 0)
				continue;
        return true;
	}
	return false;
}

int main() {
	int k;
	cin >> k;
	solve(k, 2 * k * k);
	for (int j = 0; j < int(rez.size()); ++j)
		cout << rez[j] << ' ';
}


