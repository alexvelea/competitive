//Problem e @ 08-08-2015
#include <cmath>

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

int abs(int a) {
    if (a > 0) {
        return a;
    } else {
        return -a;
    }
}

bool absSort(int a, int b) {
    return abs(a) > abs(b);
}

void show(vector<int> &el, int k) {
    el.resize(k);
    sort(el.begin(), el.end());
    reverse(el.begin(), el.end());
    for (int i = 0; i < k; ++i) {
        cout << el[i] << ' ' ;
    }
    exit(0);
}


int main() {
	ios::sync_with_stdio(false);
    int n, k; cin >> n >> k;
    vector<int>  el;

    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        el.push_back(x);
    }
    sort(el.begin(), el.end(), absSort);

    if (el[k - 1] == 0 or n == k) {
        show(el, k);    
        return 0;
    }

    bool isPositive = false;
    for (int i = 0; i < n; ++i) {
        if (el[i] >= 0) {
            isPositive = true;
        }
    }

    if (not isPositive and k % 2 == 1) {
        reverse(el.begin(), el.end());
        show(el, k);
        return 0;
    }

    bool negative = false;
    for (int i = 0; i < k; ++i) {
        int nr = el[i];
        if (nr < 0) {
            negative ^= 1;
        }
    }
    
    if (negative == true) {
        int nextP = n, nextN = n;
        int lastP = -1, lastN = -1;
        
        for (int i = 0; i < k; ++i) {
            if (el[i] >= 0) {
                lastP = i;
            } else {
                lastN = i;
            }
        }

        for (int i = n - 1; i >= k; --i) {
            if (el[i] >= 0) {
                nextP = i;
            } else {
                nextN = i;
            }
        }

        if (nextN != n and lastP != -1 and (nextP == n or lastN == -1 or fabs(1.0 * el[nextN] / el[lastP]) > fabs(1.0 * el[nextP] / el[lastN]))) {
            swap(el[nextN], el[lastP]);
        } else {
            swap(el[nextP], el[lastN]);
        }
   }
    for (int i = 0; i < k; ++i) {
        show(el, k);
    }
 
	return 0;
}
