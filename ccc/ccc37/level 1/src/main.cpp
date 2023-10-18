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
    int n; cin >> n;
    for (int i = 0; i < n; i += 1) {
        string s; cin >> s;
        cout << winner(s[0], s[1]) << '\n';
    }
}