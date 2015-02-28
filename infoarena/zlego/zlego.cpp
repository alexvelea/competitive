#include <fstream>
#include <iostream>
using namespace std;

const int kBuffer = 1000000;

ifstream in("zlego.in");
ofstream out("zlego.out");

char Buffer[kBuffer];
int BufferInd = kBuffer;

#define bufferC Buffer[BufferInd]
#define verf ((++BufferInd >= kBuffer) ? (in.read(Buffer, kBuffer), BufferInd = 0) : (0))
#define ok_char (((bufferC >= '0' and bufferC <= '9') or (bufferC == '-')) ? (1) : (0))

void cit(int &n) {
	n = 0;
	verf;
	for (; not ok_char; verf)
		;

	bool sign = false;

	if (bufferC == '-') {
		sign = true;
		verf;
	}
	for (; ok_char; verf) {
		n *= 10;
		n += bufferC - '0';
	}
	if (sign)
		n *= -1;
}

#define int64 long long

const int kMaxN = 250005;

int el[kMaxN], val[kMaxN], n;
int kmp[kMaxN];
int64 rez[kMaxN];

void make_kmp() {
	kmp[1] = 0;
	for (int i = 2; i <= n; ++i) {
		kmp[i] = kmp[i - 1];
		while (kmp[i] and el[i] != el[kmp[i] + 1])
			kmp[i] = kmp[kmp[i]];
		if (el[i] == el[kmp[i] + 1])
			++kmp[i];
	}
//	for (int i = 1; i <= n; ++i)
//		cerr << kmp[i] << '\t';
//	cerr << '\n';
}                    

int main() {
	int t;
	cit(t);
	while (t--) {
		cit(n);
		for (int i = 1; i <= n; ++i)
			cit(el[i]);
		for (int i = 1; i <= n; ++i)
			cit(val[i]);
		make_kmp();
	    for (int i = 1; i <= n; ++i)
			rez[kmp[i]] += val[i];

		for (int i = n; i; --i) {
			rez[kmp[i]] += rez[i];
			rez[i] += val[i];
		}

		for (int i = 1; i <= n; ++i) {
			out << rez[i] << '\n';
			rez[i] = 0;
		}
	}
	in.close();
	out.close();
}
