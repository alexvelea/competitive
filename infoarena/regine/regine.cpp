#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("regine.in");
ofstream out("regine.out");

const int inf = 0x3f3f3f3f;

int main() {
	int n;
	in >> n;
	out << 3 * n * (n + 1) / 2 / (2 * n + 1) << '\n';
    return 0;
}
