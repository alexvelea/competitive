#include <fstream>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int kMaxN = 1e5 + 5;

int real_position[kMaxN];
int jump_to[kMaxN];

int main() {
    string given, required;
    cin >> given >> required;

    {
        string a, b;
        for (int i = 0; i < (int)given.size(); i += 1) {
            if (given[i] != required[i]) {
                real_position[a.size()] = i;
                a += given[i];
                b += required[i];
            }
        }

        given = a;
        required = b;
    }

    vector<int> cnt_check(26, 0);
    for (char itr : given) { cnt_check[itr - 'a'] += 1; }
    for (char itr : required) { cnt_check[itr - 'a'] -= 1; }
    for (auto& itr : cnt_check) { if (itr != 0) { cout << -1 << '\n'; return 0; } }

    int n = required.size();

    set<int> next_position[26];
    for (int i = 0; i < n; i += 1) {
        next_position[required[i] - 'a'].insert(i);
    }
    
    for (int i = 0; i < n; i += 1) {
        int c = given[i] - 'a';
        auto q = next_position[c].lower_bound(i);
        int j;
        if (q == next_position[c].end()) {
            j = *next_position[c].begin();
        } else {
            j = *q;
        }

        jump_to[i] = j;
        next_position[c].erase(j);
    }

    vector<vector<int>> moves;

    cerr << given << '\n' << required << '\n';

    auto Rotate =
        [&](vector<int> ord) {
            if (ord.size() == 0) {
                return;
            }
            ord.push_back(ord[0]);
            char last_ch = given[ord[0]];
            int last_jump = jump_to[ord[0]];
            for (int i = 1; i < (int)ord.size(); i += 1) {
                char c_char = given[ord[i]];
                int c_jump = jump_to[ord[i]];

                given[ord[i]] = last_ch;
                jump_to[ord[i]] = last_jump;

                last_ch = c_char;
                last_jump = c_jump;
            }
        };

    for (int i = 0; i < n; i += 1) {
        if (jump_to[i] == i) {
            continue;
        }

        cerr << "~~~~~~~\n";
        for (int i = 0; i < n; i += 1) { cerr << jump_to[i] << '\t'; } cerr << '\n';
        for (int i = 0; i < n; i += 1) { cerr << given[i] << '\t'; } cerr << '\n';

        vector<int> op_stack = {};
        int index = i;

        while (1) {
            op_stack.push_back(index);
            if (jump_to[index] < index) {
                break;
            } else {
                index = jump_to[index];
            }
        }

        Rotate(op_stack);
        moves.push_back(op_stack);
        i -= 1;
    }

    cout << moves.size() << '\n';
    for (auto& v : moves) {
        cout << v.size() << ' ';
        for (auto& itr : v) {
            cout << real_position[itr] << ' ';
        }
        cout << '\n';
    }
}
