#include <iostream>
#include <fstream>
using namespace std;

#define int64 long long

int64 el[100];
ifstream in("fibsmen.in");
ofstream out("fibsmen.out");

bool viz[100];

int dp[100][5];

const int kBufferSize = 10000;
int BufferInd = kBufferSize;
char Buffer[kBufferSize];
#define verf ((++BufferInd >= kBufferSize) ? (in.read(Buffer, kBufferSize), BufferInd = 0) : (0))
#define BufferC (Buffer[BufferInd])
#define char_ok (((BufferC >= '0' and BufferC <= '9') or BufferC == '-') ? (1) : (0))

void cit(int64 &n) {
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
	int n = 1;
    el[0] = el[1] = 1;
	while (el[n] < 1LL * 100000000 * 100000000) {
		el[n + 1] = el[n] + el[n - 1];
		n++;
	}

	int q;
    cit(q);
	while (q--) {
		int64 x;
        cit(x);
		for (int i = 0; i <= n; ++i) {
			viz[i] = false;
			for (int d = 0; d < 5; ++d)
				dp[i][d] = 0;
		}
		for (int i = n; i; --i)
			if (x >= el[i]) {
				viz[i] = true;
				x -= el[i];
			}

		dp[n][0] = 1;

		for (int i = n; i > 0; --i) {
        	// 0 = 00 	1 = 01	2 = 11	3 = 12	4 = 02
			if (viz[i] == 1) {
				dp[i][4] = dp[i][1];
 				dp[i][3] = dp[i][2];
				dp[i][2] = 0;
				dp[i][1] = dp[i][0];
				dp[i][0] = 0;
 				
				dp[i - 1][0] = (dp[i][0] + dp[i][1]);
 				dp[i - 1][1] = (dp[i][2]);   			
				dp[i - 1][2] = (dp[i][1] + dp[i][4]);
 				dp[i - 1][3] = (dp[i][2] + dp[i][3]);   			
			} else {
 				dp[i - 1][0] = (dp[i][0] + dp[i][1]);
 				dp[i - 1][1] = (dp[i][2]);   			
				dp[i - 1][2] = (dp[i][1] + dp[i][4]);
 				dp[i - 1][3] = (dp[i][2] + dp[i][3]);   			
			}
		}
/*		for (int i = 1; i <= 5; cout << viz[i] << '\t' << el[i] << '\n', i++)
			for (int d = 0; d < 4; ++d)
				cout << dp[i][d] << '\t';*/
		out << dp[0][0] << '\n';
	}
	return 0;
}
