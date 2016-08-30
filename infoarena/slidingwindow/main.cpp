#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

#include <cassert>
using namespace std;

#define int64 long long

ifstream fin("slidingwindow.in");
ofstream fout("slidingwindow.out");

const unsigned int inf = 4e9 + 9;

const int kBufferSize = 1e4;
int bufferInd = kBufferSize;
char buffer[kBufferSize];

void nextChar() {
	if (++bufferInd >= kBufferSize) {
		fin.read(buffer, kBufferSize);
		bufferInd = 0;
	}
}

bool valid(char c) {
	return (c == '-' or ('0' <= c and c <= '9'));
}

char currentChar() {
	if (bufferInd > kBufferSize) {
		nextChar();
	}
	return buffer[bufferInd];
}

template<typename number>
void readNumber(number &a) {
	a = 0;
	bool signedNumber = false;
	if (currentChar() == '-') {
		signedNumber = true;
	}

	for (; not valid(currentChar()); nextChar())
		;

	for (; valid(currentChar()); nextChar()) {
		a *= 10;
		a += currentChar() - '0';
	}

	if (signedNumber) {
		a *= -1;
	}
	return ;
}

int solve(vector<int> &el, int d) {
	unsigned int rez = inf;
	set<int> S;

	auto shit([&]() {
		for (int i = 0; i < int(el.size()); i += 1) {
			if (i - d - 1 >= 0) {
				S.erase(el[i - d - 1]);
			}

			auto itr = S.lower_bound(el[i]);
			if (itr != S.end()) {
				rez = min(rez, (unsigned int) (*itr - el[i]));
			}

			S.insert(el[i]);
		}
	});

	shit();

	for (auto &itr : el) {
		itr *= -1;
	}

	S.clear();

	shit();

	return rez;
}

int main() {
	int n, d;
	readNumber(n);
	readNumber(d);
	vector<int> el(n, 0);
	for (int i = 0; i < n; i += 1) {
		readNumber(el[i]);
	}

	fout << solve(el, d) << '\n';
	return 0;
}