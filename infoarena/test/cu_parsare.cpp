#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;

ifstream in("date.in");

const int kBufferSize = 10000;
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


int main() {
	time_t t = clock();
	int n;
    cit(n);
	long long rez = 0;
	for (int i = 1; i <= n; ++i) {
		int aux;
        cit(aux);
		rez += aux;
	}
	cerr << "BufferSize in MB:\t" << 1.0 * kBufferSize / 1000000 << '\n';
	cerr << rez << '\n';
	cerr << 1.0 * (clock() - t) / CLOCKS_PER_SEC << '\n';
	return 0;
}
