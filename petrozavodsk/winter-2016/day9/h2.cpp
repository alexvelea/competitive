#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;

const int kMaxN = 1e6, kMod = 1e9+7;

int perm[kMaxN];
int ord[4];

int n;

struct DSU {
    int size[kMaxN];
    int left[kMaxN], right[kMaxN];
    int num_dsu;
    
    void Reset() {
        for (int i = 0; i < n; i += 1) {
            size[i] = 0;
            left[i] = right[i] = i;
        }
        num_dsu = 0;
    }

    void Join(int a, int b) {
        if (size[a] and size[b]) {
        } else { return; }

        right[left[a]] = right[b];
        left[right[b]] = left[a];
        num_dsu -= 1;
        size[left[a]] += size[b];                  
    }

    void Add(int val) {
        size[val] = 1;
        num_dsu += 1;

        if (val) {
            Join(val - 1, val);
        }

        if (val + 1 < n) {
            Join(val, val + 1);
        }
    }

    bool Inside(int v) {
        return size[v] != 0;
    }

    int Size(int v) {
        return size[left[v]];
    }
} dsu;

void Reverse() {
    reverse(perm + 0, perm + n);
    reverse(ord + 0, ord + 4);
}

void Inverse() {
    for (int i = 0; i < n; i += 1) {
        perm[i] = n - perm[i] - 1;
    } 

    for (int i = 0; i < 4; i += 1) {
        ord[i] = 3 - ord[i];
    }
}

int cv[kMaxN];

void NoOffset() {
    dsu.Reset();

    int mn = perm[0];

    static int mn_count[kMaxN];
    for (int i = 0; i < n; i += 1) {
        mn_count[i] = 0;
    }

    for (int i = 0; i < n; i += 1) {
        dsu.Add(perm[i]);
        mn = min(mn, perm[i]);
        
        cv[i] = 0;
        if (dsu.num_dsu == 1) {
            cv[i] = mn_count[mn];
        }

        mn_count[mn] += dsu.num_dsu == 1;
    }
}

void Offset() {
    dsu.Reset();
    int mn = perm[0];
    static int mn_here[kMaxN];
    static int num_dsu[kMaxN];
    for (int i = 0; i < n; i += 1) {
        mn = min(mn, perm[i]);

        dsu.Add(perm[i]);

        mn_here[i] = mn;
        num_dsu[i] = dsu.num_dsu;

        int s = dsu.Size(mn);
        if (dsu.num_dsu == 2 and mn_here[s - 1] == mn and num_dsu[s - 1] == 1) {
            cv[i] = 1;
        } else {
            cv[i] = 0;
        }
    }
}

int prefix[kMaxN];
int sufix[kMaxN];

int Solve() {
    bool inverted = false;
    if (ord[0] > ord[1]) {
        Inverse();
        inverted ^= 1;
    }

    if (ord[0] + 1 == ord[1]) {
        NoOffset();
    } else {
        Offset();
    }

    for (int i = 0; i < n; i += 1) {
        prefix[i] = cv[i];
    }

    Reverse();

    if (ord[0] > ord[1]) {
        Inverse();
        inverted ^= 1;
    }   

    if (ord[0] + 1 == ord[1]) {
        NoOffset();
    } else {
        Offset();
    }

    for (int i = 0; i < n; i += 1) {
        sufix[i] = cv[n - i - 1];
    }

    Reverse();

    if (inverted) {
        Inverse();
    }

    
    if (ord[0] != 0 and ord[1] != 0) {
        for (int i = 0; i < n; i += 1) {
            swap(prefix[i], sufix[n - i - 1]);
        }
        
        Reverse();
    }

/*
    for (int i = 0; i < n; i += 1) { cerr << perm[i] << '\t'; } cerr << '\n';
    for (int i = 0; i < 4; i += 1) { cerr << ord[i] << '\t'; } cerr << '\n';
    for (int i = 0; i < n; i += 1) { cerr << prefix[i] << '\t'; } cerr << '\n';
    for (int i = 0; i < n; i += 1) { cerr << sufix[i] << '\t'; } cerr << '\n';
*/
    int result = 0;
    bool ok = false;
    for (int i = 0; i + 1 < n; i += 1) {
        ok |= (perm[i] == 0);
        if (ok) {
            result = (result + 1LL * prefix[i] * sufix[i + 1]) % kMod;
        }
    }
    
    return result;
}

int main() {
    while (cin >> n) {
        for (int i = 0; i < n; i += 1) {
            cin >> perm[i];
            perm[i] -= 1;
        }

        for (int i = 0; i < 4; i += 1) {
            cin >> ord[i];
            ord[i] -= 1;
        }

        int result = Solve();

        cout << result << '\n';
        
    }
    return 0;
}
