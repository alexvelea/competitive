//Problem f @ 03-10-2015
#include <cstdio>

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

string Nice(int a) {
    string rez;
    if (a < 10) {
        rez += '0';
        rez += (a % 10 + '0');
    } else {
        rez += char((a / 10 + '0'));
        rez += char((a % 10 + '0'));
    }
    return rez;
}


int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int getVal(int y, int m, int d) {
    int num = 0;
    for (int Y = 100; Y < y; Y += 100) {
        if (Y % 400 != 0) {
            num++;
        }
    }
 
    if (y % 100 == 0 and y % 400 != 0) {
        if (m >= 3 or (m == 2 and d == 29)) {
            num++;
        }
    }
    return num;
}

void nextDay(int &y, int &m, int &d) {
    if (m == 2 and d == 28 and y % 4 == 0) {
        ++d;
        return ;
    }
    d++;
    if (days[m] < d) {
        d = 1;
        m++;
    }

    if (m > 12) {
        m = 1;
        y++;
    }
}

bool dayIsBad(int &y, int &m, int &d) {
    if (m == 2 and d == 29 and (y % 100 == 0 and y % 400 != 0)) {
        return true;
    }
    return false;
}

void solve(int &y, int &m, int &d, int bonus) {
    while (bonus--) {
//        cerr << y << '\t' << m << '\t' << d << '\n';
        nextDay(y, m, d);
        if (dayIsBad(y, m, d)) {
            ++bonus;
        }
    }
}

int toNumber(string txt, int a, int b) {
    int rez = 0;
    for (int i = a; i < b; ++i) {
        rez *= 10;
        rez += txt[i] - '0';
    }
    return rez;
}

int main() {
	ios::sync_with_stdio(false);
    int y, m, d;
    string txt;
    while (cin >> txt) {
        y = toNumber(txt, 0, 4);
        m = toNumber(txt, 5, 7);
        d = toNumber(txt, 8, 10);
        solve(y, m, d, getVal(y, m, d) - 1);
        cout << y << '-' << Nice(m) << '-' << Nice(d) << '\n';
    } 
	return 0;
}
