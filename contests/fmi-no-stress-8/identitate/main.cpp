#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

int days[13] = {0,
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

string T(int v, int padding) {
    string s = to_string(v);
    while ((int)s.size() != padding) {
        s = "0" + s;
    }

    return s;
}

struct Digits {
    bool is_valid = true;
    vector<int> num;
    Digits(string s) {
        num = vector<int>(10, 0);
        for (char itr : s) { num[itr - '0']++;}
    }

    Digits Substract(const string& s) {
        Digits d = *this;
        for (char itr : s) {
            d.num[itr - '0'] -= 1;
            if (d.num[itr - '0'] == -1) {
                d.is_valid = false;
            }
        }

        return d;
    }
};

int GetNum(Digits o) {
    if (not o.is_valid) {
        return 0;
    }

    int fact[7] = {1, 
                  1, 
                  1 * 2, 
                  1 * 2 * 3, 
                  1 * 2 * 3 * 4, 
                  1 * 2 * 3 * 4 * 5, 
                  1 * 2 * 3 * 4 * 5 * 6};

    int num_ways[7] = {fact[6], 0, 0, 0, 0, 0, 0};
    for (int d = 0; d < 10; d += 1) {
        for (int start_pos = 5; start_pos >= 0; start_pos -= 1) {
            for (int num_taken = 1; num_taken + start_pos <= 6 and num_taken <= o.num[d]; num_taken += 1) {
                if (num_ways[start_pos]) {
                    num_ways[start_pos + num_taken] += num_ways[start_pos] / fact[num_taken];
                }
            }
        }
    }

    return num_ways[6];
}

int GetNum(Digits o, bool) {
    int ans = 0;
    for (int i = 0; i < 1e6; i += 1) {
        if (o.Substract(T(i, 6)).is_valid) {
            ans += 1;
        }
    }
    return ans;
}

int main() {
    while (false) {
        string s = "";
        int n = rand() % 15 + 6;
        for (int i = 0; i < n; i += 1) {
            s += rand() % 10 + '0';
        }

        Digits o(s);
        if (GetNum(o) != GetNum(o, true)) {
            cerr << s << '\n';
            return 0;
        }

        cerr << "Ok!\n";
    }

    ifstream cin("identitate.in");
    ofstream cout("identitate.out");

    string s; cin >> s;
    Digits o(s);

    long long ans = 0;
    for (int sex = 1; sex <= 2; sex += 1) // sex? yes, please
        for (int year = 0; year < 100; year += 1)
            for (int month = 1; month <= 12; month += 1)
                for (int day = 1; day <= days[month] + (year % 4 == 0 and month == 2); day += 1) {
                    string cnp = T(sex, 1) + T(year, 2) + T(month, 2) + T(day, 2);
                    ans += GetNum(o.Substract(cnp));
                }

    cout << ans << '\n';
}
