#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <sys/time.h>
using namespace std;

typedef long long int64;

struct DpState {
    bool ok = false;
    int bit_num = 0;
    int a_bit = 0;
    int b_bit = 0;
    DpState* parent = nullptr;
};

DpState dp[40][2][2];

int MxBit(int64 bitmask) {
    for (int64 i = 32; i >= 0; i -= 1) {
        if (bitmask & (1LL << i)) {
            return i;
        }
    }

    return -1;
}

void Expand(int bit, int old_a_roll, int old_b_roll, 
        int a_change, int b_change,
        int a_roll, int b_roll) {
    DpState new_dp;
    new_dp.ok=  true;
    new_dp.bit_num = bit + 1;
    new_dp.a_bit = a_change;
    new_dp.b_bit = b_change;
    new_dp.parent = &(dp[bit][old_a_roll][old_b_roll]);

    dp[bit + 1][a_roll][b_roll] = new_dp;
}

void Solve(int64 a, int64 b) {
    for (int bit = 0; bit < 35; bit += 1) {
        for (int a_roll = 0; a_roll < 2; a_roll += 1) {
            for (int b_roll = 0; b_roll < 2; b_roll += 1) {
                if (not dp[bit][a_roll][b_roll].ok) {
                    continue;
                }

                int64 a_required = !!((1LL << bit) & a);
                int64 b_required = !!((1LL << bit) & b);

                if (b_roll == b_required) {
                    if (a_required != a_roll) {
                        Expand(bit, a_roll, b_roll, -1, 0, true, b_roll);
                        Expand(bit, a_roll, b_roll, +1, 0, false, b_roll);
                    }
                }

                if (a_roll == a_required) {
                    if (b_required != b_roll) {
                        Expand(bit, a_roll, b_roll, 0, -1, a_roll, true);
                        Expand(bit, a_roll, b_roll, 0, +1, a_roll, false);
                    }
                }
            }
        }
    }
}


void Reset() {
    for (int i = 0; i < 40; i += 1) {
        for (int a = 0; a < 2; a += 1) {
            for (int b = 0; b < 2; b += 1) {
                dp[i][a][b] = DpState();
            }
        }
    }
}

int64 qa, qb;
string dict_a, dict_b;

string GoBack(int i, int a, int b) {
    DpState* head = &(dp[i][a][b]);
    i -= 1;
    int64 A = 0, B = 0;
    string ans;
    for (; i >= 0; i -= 1) {
        A += head->a_bit * (1LL << i);
        B += head->b_bit * (1LL << i);
        if (head->a_bit != 0)
            ans.push_back((head->a_bit == +1) ? dict_a[2] : dict_a[0]);
        if (head->b_bit != 0)
            ans.push_back((head->b_bit == +1) ? dict_b[2] : dict_b[0]);

        head = head->parent;
    }

//    cerr << A << '\t' << B << '\t' << ans << '\n';

    if (A == qa and B == qb) {
        reverse(ans.begin(), ans.end());
        return ans;
    } else {
        return "";
    }
}


int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; t += 1) {
        Reset();
        dp[0][0][0].ok = true;

        int64 a, b; cin >> a >> b;

        if (a > 0) { dict_a = "W*E"; } else { a *= -1; dict_a = "E*W"; }
        if (b > 0) { dict_b = "S*N"; } else { b *= -1; dict_b = "N*S"; }

        qa = a;
        qb = b;

        Solve(a, b);
        
        string ans = "IMPOSSIBLE";
        bool found = false;

        for (int i = 0; (not found) and i < 40; i += 1) {
            for (int a = 0; a < 2; a += 1) {
                for (int b = 0; b < 2; b += 1) {
                    if (dp[i][a][b].ok) {
                        auto aux = GoBack(i, a, b);
                        if (aux.size() == 0) {
                            continue;
                        } 

                        ans = aux;
                        found = true;
                    }
                }
            }
        }

        

        cout << "Case #" << t << ": ";
        cout << ans << '\n';
    }
}
