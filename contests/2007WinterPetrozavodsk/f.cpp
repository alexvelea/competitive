//Problem f @ 26-09-2015
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

int main() {
	ios::sync_with_stdio(false);
    ifstream fin("nim.in");
    ofstream fout("nim.out");
    int64 n; fin >> n;
    
    int64 diff = 1;
    int64 lastBad = 2, newBad;
    while (1) {
//        cerr << lastBad << '\n';
        if (lastBad == n) {
            fout << "LOSE";   
            return 0;
        }

        if (lastBad > n) {
            fout << "WIN";
            return 0;
        }
        newBad = lastBad + diff;
        if (newBad - lastBad > sqrt(newBad)) {
            lastBad = newBad;
        } else {
            ++diff;
        }
    }

	return 0;
}
