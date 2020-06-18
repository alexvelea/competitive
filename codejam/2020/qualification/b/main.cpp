#include <iostream>
using namespace std;

const int kMaxN = 105;

int start_here[kMaxN];
int end_here[kMaxN];
int els[kMaxN];

void Solve(int digit, int a, int b) {
    bool found = true;
    for (int i = a; i <= b; i += 1) {
        if (els[i] > digit) { found = true; }
    }
    if (not found) { return; }

    int last_digit = a - 1;
    auto EndStreak = [&](int position) {
        if (last_digit == position - 1) {
            return;
        }

        start_here[last_digit + 1] += 1;
        end_here[position - 1] += 1;
        Solve(digit + 1, last_digit + 1, position - 1);
    };

    for (int i = a; i <= b; i += 1) {
        if (els[i] == digit) {
            EndStreak(i);
            last_digit = i;
        }
    }

    EndStreak(b + 1);
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; t += 1) {
        string s; cin >> s;
        for (size_t i = 0; i < s.size(); i += 1) {
            els[i] = s[i] - '0';
            start_here[i] = 0;
            end_here[i] = 0;
        }

        Solve(0, 0, int(s.size()) - 1);
        string ans = "";
        for (size_t i = 0; i < s.size(); i += 1) {
            ans += string(start_here[i], '(');
            ans += s[i];
            ans += string(end_here[i], ')');
        }

        cout << "Case #" << t << ": " << ans << '\n';
    }
}
