#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
// const int inf = 100;
const int kMaxN = 2e5+5;

const int debug = false;

int S[kMaxN];
int l;

int first7[kMaxN];
int partial_sums[kMaxN][6];

struct AintNode {
    int constant[3]; // constant[i] = num_i_before - num_(i + 1) before
    int best01, best02, best12;

    AintNode() {
        for (int i = 0; i < 3; i += 1) {
            constant[i] = +inf;
        }
        best01 = +inf;
        best02 = +inf;
        best12 = +inf;
    }

    AintNode MergeLeft(const AintNode& rhs) {
        AintNode result;
        for (int i = 0; i < 3; i += 1) {
            result.constant[i] = min(constant[i], rhs.constant[i]);
        }

        result.best01 = min(best01, rhs.best01);
        result.best01 = min(result.best01, constant[0] + rhs.constant[1]);

        result.best12 = min(best12, rhs.best12);
        result.best12 = min(result.best12, constant[1] + rhs.constant[2]);

        result.best02 = min(best02, rhs.best02);
        result.best02 = min(result.best02, best01 + rhs.constant[2]);
        result.best02 = min(result.best02, constant[0] + rhs.best12);
        return result;
    }

    void Debug() {
        if (not debug) {
            return;
        }
        for (int i = 0; i < 3; i += 1) {
            printf("%d\t", constant[i]);
        }
        printf("%d\t%d\t%d\n", best01, best02, best12);
        printf("\n");
        return;
    }
} aint[4 * kMaxN];

void MakeAint(int node, int left, int right) {
    if (left == right) {
        if (S[left] >= 3) {
            return;
        }
        
        if (S[left] == 2) {
            aint[node].constant[2] = partial_sums[l - 1][3] - partial_sums[left][3] + partial_sums[left][2] - 1;
            return;
        } else {
            aint[node].constant[S[left]] = partial_sums[left][S[left]] - 1 - partial_sums[left][S[left] + 1];
        }
        
        return;
    }

    int mid = (left + right) / 2;
    MakeAint(2 * node, left, mid);
    MakeAint(2 * node + 1, mid + 1, right);
    aint[node] = aint[2 * node].MergeLeft(aint[2 * node + 1]);
    return;
}

void Debug(int node, int left, int right) {
    if (debug) { 
        printf("left:%d\tright:%d\t", left, right);
        aint[node].Debug();
    }

    if (left == right) {
        return;
    }

    int mid = (left + right) / 2;
    Debug(2 * node, left, mid);
    Debug(2 * node + 1, mid + 1, right);
}

AintNode Query(int node, int left, int right, int c1, int c2) {
    if (c1 <= left and right <= c2) {
        if (debug) {
            printf("Query [%d, %d]\t", left, right);
            aint[node].Debug();
        }
        return aint[node];
    }

    if (right < c1 or c2 < left) {
        return AintNode();
    }

    int mid = (left + right) / 2;
    return Query(2 * node, left, mid, c1, c2).MergeLeft(Query(2 * node + 1, mid + 1, right, c1, c2));
}

int main() {
    ios_base::sync_with_stdio(false);
    int q; cin >> l >> q;
    string s; cin >> s;
    for (int i = 0; i < l; i += 1) {
        S[i] = 5;
        if (s[i] == '2') {
            S[i] = 0;
        } else if (s[i] == '0') {
            S[i] = 1;
        } else if (s[i] == '1') {
            S[i] = 2;
        } else if (s[i] == '6') {
            S[i] = 3;
        } else if (s[i] == '7') {
            S[i] = 4;
        }
    }

    int last = -1;
    for (int i = 0; i < l; i += 1) {
        if (S[i] == 4) {
            last = i;
        }
        first7[i] = last;
    }

    for (int i = 0; i < l; i += 1) {
        partial_sums[i][S[i]] += 1;
        if (i == 0) {
            continue;
        }
        for (int j = 0; j < 6; j += 1) {
            partial_sums[i][j] += partial_sums[i - 1][j];
        }
    }
//    printf("!#@!#@!32\n");
    MakeAint(1, 0, l - 1);
    Debug(1, 0, l - 1);

    while (q--) {
        int left, r; cin >> left >> r;
        left -= 1;
        r -= 1;
        int rr = first7[r];
        if (rr < left) {
            cout << -1 << '\n';
            continue;
        }

        AintNode s = Query(1, 0, l - 1, left, rr);
        s.Debug();
        int result = s.best02;
        result -= partial_sums[l - 1][3] - partial_sums[r][3];
        if (left) {
            result -= partial_sums[left - 1][0];
        }
        if (result > l) {
            cout << -1 << '\n';
            continue;
        }
        cout << result << '\n';
    }
    
    return 0;
}
