#include <iostream>
#include <vector>
#include <map>

using namespace std;

char winner(char a, char b) {
    if (a == b) {
        return a;
    }

    if (a == 'S') {
        if (b == 'P') {
            return a;
        } else {
            return b;
        }
    }
    if (a == 'P') {
        if (b == 'R') {
            return a;
        } else {
            return b;
        }
    }
    if (a == 'R') {
        if (b == 'S') {
            return a;
        } else {
            return b;
        }
    }

    return '!';
}

int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i += 1) {
        string s; cin >> s;
        for (int j = 0; j < (int)s.size(); j += 4) {
            cout << winner(
                    winner(s[j + 0], s[j + 1]),
                    winner(s[j + 2], s[j + 3])
                    );
        }
        cout << '\n';
    }
}