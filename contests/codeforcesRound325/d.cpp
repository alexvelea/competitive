//Problem d @ 12-10-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <ctime>
#include <unordered_map>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

vector<tuple<int, int, int, int> > a;

int val[3][30];

 
int64 bonus = 1e9;

unordered_map<int64, pair<int, int> > B;
 

void bt(int poz, int limit, int history, vector<int> vals, int target) {
    if (poz == limit + 1) {
        if (target == 1) {
            a.push_back(make_tuple(vals[0], vals[1], vals[2], history));
        } else {
        int x = vals[0], y = vals[1], z = vals[2];
        y = x - y;
        z = x - z;
        if (B.count(bonus * y + z) == 0) {
            B[bonus * y + z] = make_pair(x, history);
        } else {
            int _x = B[bonus * y + z].first;
            if (_x < x) {
                B[bonus * y + z] = make_pair(x, history);
            }
        }  
        }
    } else {                                                                        
        bt(poz + 1, limit, history * 3, {vals[0] + 1 * val[0][poz], vals[1] + 1 * val[1][poz], vals[2] + 0 * val[2][poz]}, target);
        bt(poz + 1, limit, history * 3 + 1, {vals[0] + 0 * val[0][poz], vals[1] + 1 * val[1][poz], vals[2] + 1 * val[2][poz]}, target);
        bt(poz + 1, limit, history * 3 + 2, {vals[0] + 1 * val[0][poz], vals[1] + 0 * val[1][poz], vals[2] + 1 * val[2][poz]}, target);
    }
}

string D(int n, int nr) {
    if (n == -1) {
        return "";
    }
    string val[3] = {"LM\n", "MW\n", "LW\n"};
    vector<string> rez;
    for (int i = 0; i < nr; ++i) {
        rez.push_back(val[n % 3]);
        n /= 3;
    }
    reverse(rez.begin(), rez.end());
    string r = "";
    for (auto itr : rez) {
        r += itr;
    }
    return r;
}

int main() {
	ios::sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> val[0][i] >> val[1][i] >> val[2][i];
    }
    time_t t = clock();
    int dr = min(13, n);
    bt(1, dr, 0, {0, 0, 0}, 1);
    if (dr < n) {
        bt(dr + 1, n, 0, {0, 0, 0}, 2);
    } else {
        B[0] = {0, -1};
    }

    int mx = -inf;
    int Ha = 0, Hb = 0;

    for (auto itr : a) {
        int x, y, z;
        int history;
        tie(x, y, z, history) = itr;
        if (B.count(bonus * (y - x) +  (z - x)) == 0) {
            continue;
        }
        pair<int, int> rez = B[(bonus * (y - x) + (z - x))];
            x += rez.first;
            if (x > mx) {
                mx = x;
                Ha = history;
                Hb = rez.second;
            }
    }

    if (mx == -inf) {
        cout << "Impossible\n";
    } else {
        cout << D(Ha, dr) << D(Hb, (n - dr)) << '\n';
    }

	return 0;
}
