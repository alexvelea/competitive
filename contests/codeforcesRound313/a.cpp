//Problem a @ 22-07-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

int el[6];

int main() {
	ios::sync_with_stdio(false);
    for (int i = 0; i < 6; ++i) {
        cin >> el[i];
    }
    int side = el[0], rez = 0;;
	for (int l = 1; l <= el[1] + el[2]; ++l) {
        rez += side;
        if (el[1] >= l and el[5] >= l) {
            side++;
        } else if (el[1] < l and el[5] < l) {
            side--;
        }
        rez += side;
    }
    cout << rez << '\n';
    return 0;
}
