//Problem #B from Codeforces 238
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define fi first
#define se second
#define int64 long long

const int kBufferSize = 10000;
int BufferInd = kBufferSize;
char Buffer[kBufferSize];
#define verf ((++BufferInd >= kBufferSize) ? (cin.read(Buffer, kBufferSize), BufferInd = 0) : (0))
#define BufferC (Buffer[BufferInd])
#define char_ok (((BufferC >= '0' and BufferC <= '9') or BufferC == '-') ? (1) : (0))

void cit(int &n) {
	verf;
	for (; not char_ok; verf)
		;
	
	bool sign = false;
	if (BufferC == '-') {
		verf;
		sign = true;
	}
    
	n = 0;
	for (; char_ok; verf) {
		n *= 10;
		n += BufferC - '0';
	}
	if (sign)
		n *= -1;
}

const int z6 = 1000000;
bool viz[z6 + 10];

int oth(int x) {
	return z6 - x + 1;
}

vector<int> rez;

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int x;
 		cin >> x;
		viz[x] = true;
	}
 	int p = 0;
	for (int i = 1; i <= z6; ++i) {
		if (viz[i] and (not viz[oth(i)])) {
			rez.push_back(oth(i));
		}
		if (viz[i] and viz[oth(i)]) {
			++p;
		}
	}
	p /= 2;
    for (int i = 1; i <= z6 and p; ++i) {
		if (not viz[i] and not viz[oth(i)]) {
			viz[i] = true;
			viz[oth(i)] = true;
			rez.push_back(i);
			rez.push_back(oth(i));
			--p;
		}
	}
	cout << rez.size() << '\n';
	for (int i = 0; i < int(rez.size()); ++i)
		cout << rez[i] << ' ';
    return 0;
}

