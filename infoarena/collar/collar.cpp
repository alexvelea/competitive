#include <fstream>
#include <iostream>
using namespace std;

#define int64 long long

ifstream in("collar.in");
ofstream out("collar.out");

const int kMaxN = 66600;

int el[2 * kMaxN], rez[kMaxN];
int deqMin[kMaxN], stMin, drMin;
int deqMax[kMaxN], stMax, drMax;

int64 mx = 0;

int main() {
	int n;
	in >> n;
	for (int i = 0; i < n; ++i)
		in >> el[i];
	for (int i = 0; i < n; ++i)
		el[i + n] = el[i];

	for (int l = 2; l <= n; ++l) 
		if (n % l == 0) {
			int stMin = 1, drMin = 0, stMax = 1, drMax = 0;
			for (int i = 0; i < l; ++i) {
				while (drMin >= stMin and el[i] <= el[deqMin[drMin]])
					--drMin;
				deqMin[++drMin] = i;
				while (drMax >= stMax and el[i] >= el[deqMax[drMax]])
					--drMax;
				deqMax[++drMax] = i;
			}
			for (int i = 0; i < n; ++i) {
				if (deqMin[stMin] == i - 1)
					++stMin;
				if (deqMax[stMax] == i - 1)
					++stMax;

 				while (drMin >= stMin and el[i + l - 1] <= el[deqMin[drMin]])
					--drMin;
				deqMin[++drMin] = i + l - 1;
				while (drMax >= stMax and el[i + l - 1] >= el[deqMax[drMax]])
					--drMax;
				deqMax[++drMax] = i + l - 1;	
				rez[i] = el[deqMax[stMax]] - el[deqMin[stMin]];
			}
			for (int i = 0; i < l; ++i) {
				int64 sum = 0;
				for (int j = i; j < n; j += l)
					sum = 1LL * (sum + rez[j]);
				if (sum > mx)
					mx = sum;
			}
		}
	out << mx << '\n';
	return 0;
}
