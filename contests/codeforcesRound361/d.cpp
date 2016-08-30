#include <algorithm>
#include <functional>

#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

const int kMaxN = 2e5+5;

int n; 

int a[kMaxN], b[kMaxN];
int left_val[kMaxN], right_val[kMaxN];
int go_left[2][kMaxN], go_right[2][kMaxN];

void f() {
    vector<int> A;
    for (int i = 1; i <= n; i += 1) {
        while (A.size() and a[A.back()] < a[i]) {
            A.pop_back();
        }

        if (A.size()) {
            go_left[0][i] = A.back();
        }

        A.push_back(i);
    }
    
    A.clear();
     for (int i = n; i; i -= 1) {
        while (A.size() and a[A.back()] <= a[i]) {
            A.pop_back();
        }

        if (A.size()) {
            go_right[0][i] = A.back();
        } else {
            go_right[0][i] = n + 1;
        }

        A.push_back(i);
    }
}

void g() {
    vector<int> B;
    for (int i = 1; i <= n; i += 1) {
        while (B.size() and b[B.back()] >= b[i]) {
            B.pop_back();
        }

        if (B.size()) {
            go_left[1][i] = B.back();
        }

        B.push_back(i);
    }
    
    B.clear();
    for (int i = n; i; i -= 1) {
        while (B.size() and b[B.back()] >= b[i]) {
            B.pop_back();
        }

        if (B.size()) {
            go_right[1][i] = B.back();
        } else {
            go_right[1][i] = n + 1;
        }

        B.push_back(i);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i += 1) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i += 1) {
        cin >> b[i];
    }

    map<int, int> last_b;
    for (int i = 1; i <= n; i += 1) {
        last_b[b[i]] = i;
        left_val[i] = last_b[a[i]];
    }

    last_b.clear();
    for (int i = n; i; i -= 1) {
        last_b[b[i]] = i;
        right_val[i] = last_b[a[i]];
    }

    f();
    g();


//    cout << "!!!\n";

    int64 result = 0;
    for (int i = 1; i <= n; i += 1) {
        pair<int, int> l, r, c = {go_left[0][i], go_right[0][i]};
        if (left_val[i] == 0 and right_val[i] == 0) {
            continue;
        }

        if (right_val[i] == 0) {
            l = {go_left[1][left_val[i]], go_right[1][left_val[i]]};
            r = {n + 1, n + 1};
        } else if (left_val[i] == 0) {
            r = {go_left[1][right_val[i]], go_right[1][right_val[i]]};
            l = {0, 0};
        } else {
            l = {go_left[1][left_val[i]], go_right[1][left_val[i]]};
            r = {go_left[1][right_val[i]], go_right[1][right_val[i]]};
        }

//        cerr << i << '\t' << l.first << '\t' << l.second << '\t' << r.first << '\t' << r.second << '\t';

        // merge shits
        if (l.second > i and r.first < i and c.first < left_val[i] and c.second > right_val[i]) {
            result += 1LL * (left_val[i] - max(c.first, l.first)) * (min(c.second, l.second) - i);
            result += 1LL * max(0, min(r.second, c.second) - right_val[i]) * max(0, i - max(left_val[i], r.first));
        } else if (l.second > i and c.first < left_val[i]) {
            result += 1LL * (left_val[i] - max(c.first, l.first)) * (min(c.second, l.second) - i);
        } else if (r.first < i and c.second > right_val[i]) {
            result += 1LL * max(0, min(r.second, c.second) - right_val[i]) * max(0, i - max(c.first, r.first));
        }

        cerr << result << '\n';
    }
    cout << result << '\n';
    return 0;
}
