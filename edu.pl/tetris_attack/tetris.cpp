#include <iostream>
using namespace std;

const int kMaxN = 100005;

int el[kMaxN], aib[kMaxN], pos[kMaxN];
int n;


void update_aib(int ind, int val) {
	while (ind < kMaxN) {
		aib[ind] += val;
		ind += ind & (-ind);
	}
	return ;
}
int aib_query(int ind) {
	int rez = 0;
	while (ind) {
		rez += aib[ind];
		ind -= ind & (-ind);
	}
	return rez;
}

int main() {
	cin >> n;
	for (int i = 1; i <= 2 * n; ++i)
		cin >> el[i];
	int nr_el = 0, rez = 0;
	for (int i = 1; i <= 2 * n; ++i) {
		if (pos[el[i]]) {
			rez += nr_el - aib_query(pos[el[i]]);
			update_aib(pos[el[i]], -1);
			--nr_el;
		} else {
			update_aib(i, +1);
			pos[el[i]] = i;
			++nr_el;
		}
	}
	cout << rez / 2;
	return 0;
}
