#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int kMaxN = 1e5 + 5;

int real_position[kMaxN];
int next_position[2 * kMaxN][26];
int jump_to[kMaxN];

int main() {
    ifstream cin("rightshift.in");
    ofstream cout("rightshift.out");
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

    int n = (int)given.size();
    for (int i = 2 * n - 1; i >= 0; i -= 1) {
        for (int j = 0; j < 26; j += 1) {
            next_position[i][j] = next_position[i + 1][j];
        }
        if (i + 1 < 2 * n) {
            next_position[i][required[(i + 1) % n] - 'a'] = i + 1;
        }
    }

    vector<int> next_jump_pos(26, 0);

    for (int i = 0; i < n; i += 1) {
        int j = next_position[next_jump_pos[given[i] - 'a']][given[i] - 'a'];
        jump_to[i] = j % n;
        next_jump_pos[given[i] - 'a'] = j % n;
    }

    vector<vector<int>> moves;

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
