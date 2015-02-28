#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream in("puncte.in");
ofstream out("puncte.out");

const int kBufferSize = 1000005;
int BufferInd = kBufferSize;
char Buffer[kBufferSize];
#define verf ((++BufferInd >= kBufferSize) ? (in.read(Buffer, kBufferSize), BufferInd = 0) : (0))
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

#define int64 long long

const int inf = 0x3f3f3f3f, kMaxN = 100005;

struct Line {
	int64 a, b;
	int ind;
	Line() {
		a = b = ind = 0;
	}
	Line(int64 _a, int64 _b, int _ind) {
		a = _a;
		b = _b;
		ind = _ind;
	}
	bool operator < (const Line &rhs) const {
		if (a == rhs.a)
			return b < rhs.b;
		return a > rhs.a;
	}
	int64 time(Line &rhs) {
		int64 B = b - rhs.b;
		int64 A = a - rhs.a;
		B *= -1;

		if (A == 0)
			return 1LL * inf * inf;

		int64 rez = B / A;
		if (1LL * rez * A == B or ((B > 0) != (A > 0)))
			return rez;
		else
			return rez + 1;
	}
	int64 get(int64 x) {
		return 1LL * x * a + b;
	}
} ecu[kMaxN];

int64 min(int64 a, int64 b) {
	if (a < b)
		return a;
	return b;
}
	
int stv[kMaxN];

int main() {
	int n, m;
    cit(n); cit(m);
	for (int i = 1; i <= n; ++i) {
		int64 x = 0, y = 0;
        int a, b;

        cit(a);
        cit(b);
        
		y = 1LL * b * b;
		y += 1LL * a * a;
		x = -2LL * a;;
 		ecu[i] = Line(x, y, i);
	}

	sort(ecu + 1, ecu + n + 1);
	int st = 0;

	for (int i = 1; i <= n; ++i) {
		while (st > 1) {
			int a = stv[st - 1];
			int b = stv[st];
			if (ecu[a].time(ecu[b]) >= ecu[b].time(ecu[i]))
				--st;
			else
				break;
		}
		stv[++st] = i;
	}

	while (m--) {
		int rez = 1, p = 1 << 18;
		int x;
        cit(x);
		for (; p; p /= 2)
			if (rez + p + 1 <= st) {
				int a = stv[rez + p];
				int b = stv[rez + p + 1];
 				if (ecu[a].time(ecu[b]) <= x)
					rez += p;
			}
		int64 a = ecu[stv[rez]].get(x) + 1LL * x * x;
		int64 b = ecu[stv[rez + 1]].get(x) + 1LL * x * x;
		out << min(a, b) << '\n';
	}
	in.close();
	out.close();
    return 0;
}
