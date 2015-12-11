//When I wrote this, only God and I 
//understood what I was doing
//Now, God only knows

#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("inter.in");
ofstream out("inter.out");

const int kMaxN = 1005;

int n;

int aib[kMaxN];
int infront[kMaxN], rez[kMaxN];

int find_sum(int sum) {
	int p = 1, rez = 0;
	while (p <= n)
		p *= 2;
	for (; p; p /= 2) 
		if (rez + p <= n and aib[rez + p] <= sum) {
			rez += p;
			sum -= aib[rez];
		}
	return rez;
}

void aib_update(int ind, int val) {
	while (ind <= n) {
		aib[ind] += val;
		ind += ind & (-ind);
	}
	return ;
}

int main() {
	int m;
	in >> n >> m;
	while (m--) {
		int a, b;
		in >> a >> b;
		if (a > b)
			a = b;
		infront[a]++;
	}
	for (int i = 1; i <= n; ++i)
		aib_update(i, +1);
	for (int i = 1; i <= n; ++i) {
		int poz = find_sum(infront[i]);
		poz++;
		aib_update(poz, -1);
		rez[poz] = i;
	}
	for (int i = 1; i <= n; ++i)
		out << rez[i] << ' ';
    return 0;
}
