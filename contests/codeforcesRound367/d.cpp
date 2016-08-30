#include <algorithm>
#include <functional>

#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

typedef double float64;
typedef long double float128;

const int kInf = 0x3f3f3f3f;

struct TrieNode {
    int cnt;
    TrieNode* values[2];
    TrieNode() : cnt(0) {
        values[0] = nullptr;
        values[1] = nullptr;
    }

    TrieNode* require(int value) {
        if (values[value] == nullptr) {
            values[value] = new TrieNode;
        }

        return values[value];
    }

    void Add(int val, int bonus, int bit=30) {
        cnt += bonus;
        
        if (bit == -1) {
            return;
        }

        require(!!(val & (1 << bit)))->Add(val, bonus, bit - 1);
    }

    int MaxXor(int val, int bit=30) {
        if (bit == -1) {
            return 0;
        }

        int b = !!(val & (1 << bit));
        b ^= 1;

        if (values[b] != nullptr and (values[b]->cnt != 0)) {
            return (1 << bit) + values[b]->MaxXor(val, bit - 1);
        } else {
            return values[1 ^ b]->MaxXor(val, bit - 1);
        }
    }
} root;

int main() {
    ios_base::sync_with_stdio(false);
    int q; cin >> q;
    root.Add(0, +1);

    while (q--) {
        char c; cin >> c;
        int x; cin >> x;
        if (c == '+') {
            root.Add(x, +1);
        } else if (c == '-') {
            root.Add(x, -1);
        } else {
            cout << root.MaxXor(x) << '\n';
        }
    }
    cout << '\n';
    return 0;
}
