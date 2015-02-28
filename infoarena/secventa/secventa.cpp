#include <fstream>
#include <iostream>
using namespace std;

const int kMaxN = 500005;

ifstream in("secventa.in");
ofstream out("secventa.out");

int el[kMaxN], deq[kMaxN];

#define MaxChar 1000000
#define verf ( (++CharB >= MaxChar) ? (in.read(Buffer, MaxChar), CharB = 0) : (1))

long CharB = MaxChar;
char Buffer[MaxChar];

void cit (int &a) {
	if (CharB >= MaxChar)
		verf;
    bool ok=0;
    for ( ; !((Buffer[CharB] >= '0' && Buffer[CharB] <= '9') || (Buffer [CharB] == '-')); verf)
        ;
    if (Buffer[CharB] == '-') {
        verf;
        ok=1;
    }
    for (a = 0; (Buffer[CharB] >= '0' && Buffer[CharB] <= '9'); a *= 10,a += (Buffer[CharB] - '0'), verf)
        ;
    if (ok) {
        a=-a;
    }
}


int main() {
	int n, k;
    cit(n);
    cit(k);
	for (int i = 1; i <= n; ++i)
        cit(el[i]);
	int st = 1;
	int dr = 0;
	for (int i = 1; i < k; ++i) {
		while (dr >= st and el[deq[dr]] >= el[i])
			--dr;

		deq[++dr] = i;
	}
	int mx = -0x3f3f3f3f, p;
	for (int i = k; i <= n; ++i) {
		if (deq[st] == i - k)
			++st;

		while (dr >= st and el[deq[dr]] >= el[i])
			--dr;

		deq[++dr] = i;
		if (mx < el[deq[st]]) {
			p = i;
			mx = el[deq[st]];
		}
	}
 	out << p - k + 1 << ' ' << p << ' ' << mx << '\n';
	return 0;
}
