#include <iostream>
#include <vector>
using namespace std;

int print = 0;
void Rotate(string& s, vector<int> ord) {
    if (ord.size() == 0) { return; }
    ord.push_back(ord[0]);
    char last_ch = s[ord[0]];
    for (int i = 1; i < (int)ord.size(); i += 1) {
        char c_char = s[ord[i]];
        s[ord[i]] = last_ch;
        last_ch = c_char;
    }
}

void Back(string given, string required, int moves_left) {
    if (given == required) {
        cout << print << '\n';
        exit(0);
    }

    if (moves_left == 0) {
        return;
    }

    for (int i = 0; i < (1 << given.size()); i += 1) {
        vector<int> perm = {};
        for (int j = 0; j < (int)given.size(); j += 1) {
            if (i & (1 << j)) {
                perm.push_back(j);
            }
        }

        auto new_given = given;
        Rotate(new_given, perm);
        Back(new_given, required, moves_left - 1);
    }
}

int main() {
    string given, required; cin >> given >> required;

    for (int num_moves = 0; ; num_moves += 1) {
        print = num_moves;
        Back(given, required, num_moves);
    }
}
