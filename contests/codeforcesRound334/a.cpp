//Problem a @ 01-12-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;


#define int64 long long

void getMax(int &a, int b) {
	if (a < b) {
		a = b;
	}
}

int main() {
	ios::sync_with_stdio(false);
    int n; cin >> n;
    string txt; cin >> txt;
    char last = 'a';
    int mx = 0;
    for (int i = 0; i < int(txt.size()); i += 1) {
    	if (txt[i] != last) {
    		mx += 1;
    		last = txt[i];
    	}
    }
    int pairs = 0;
    for (int i = 0; i + 1 < int(txt.size()); i += 1) {
    	if (txt[i] == txt[i + 1]) {
    		pairs += 1;
    	}
    }
    if (pairs >= 2) {
    	cout << mx + 2 << '\n';
    } else if (pairs == 1) {
    	cout << mx + 1 << '\n';
    } else {
    	cout << mx << '\n';
    }
	return 0;
}