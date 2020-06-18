#include <sys/time.h>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

typedef long long int64;

const int kMaxN = 65;

string a, b;

struct DPState {
    bool valid;
    string sol;
    int a, b; 
    int m_a, m_b;

    void Update(const DPState& rhs) {
        assert(a - b == rhs.a - rhs.b);
        assert(m_a == rhs.m_a and m_b == rhs.m_b);
        if (not valid or a > rhs.a) {
            *this = rhs;
        }
    };

    void FinalUpdate(const DPState& rhs) {
        int c_a = rhs.a + (::a.size() - rhs.m_a);
        int c_b = rhs.b + (::b.size() - rhs.m_b);
        if (c_a + c_b < a + b) {
            a = c_a;
            b = c_b;
            sol = rhs.sol;
        } else if (c_a + c_b == a + b and (abs(c_a - c_b) < abs(a - b))) {
            a = c_a;
            b = c_b;
            sol = rhs.sol;           
        }
    }
};

DPState dp[kMaxN][kMaxN][2 * kMaxN];

vector<pair<int, int>> make_changes(const string& txt, int pos, char ch) {
    // character is added
    vector<pair<int, int>> ans = { {+1, 0} };
    if (pos == (int)txt.size()) {
        return ans;
    }
    
    ans.push_back({+1, +1});
   
    // find nearest ch in txt
    for (int i = pos; i < (int)txt.size(); i += 1) {
        if (txt[i] == ch) {
            ans.push_back({i - pos, i - pos + 1});    
        }
    }

    return ans;
}

int main() {
    int T; cin >> T;

    for (int t = 1; t <= T; t += 1) {
        cin >> a >> b;
        int n = a.size(), m = b.size();
        for (int i = 0; i <= n; i += 1) {
            for (int j = 0; j <= m; j += 1) {
                for (int diff = -kMaxN; diff < kMaxN; diff += 1) {
                    dp[i][j][diff + kMaxN].valid = false;
                    dp[i][j][diff + kMaxN].m_a = i;
                    dp[i][j][diff + kMaxN].m_b = j;
                    dp[i][j][diff + kMaxN].a = diff;
                    dp[i][j][diff + kMaxN].b = 0;

                }
            }
        }

        dp[0][0][0 + kMaxN].valid = true;
        for (int sum = 0; sum <= n + m; sum += 1) {
            for (int match_a = 0; match_a <= min(n, sum); match_a += 1) {
                int match_b = sum - match_a;
                if (match_b > m) {
                    continue;
                }

                for (int diff = -kMaxN; diff < kMaxN; diff += 1) {
                    if (not dp[match_a][match_b][diff + kMaxN].valid) {
                        continue;
                    }
                    for (char ch = 'A'; ch <= 'Z'; ch += 1) {
                        auto A = make_changes(a, match_a, ch);
                        auto B = make_changes(b, match_b, ch);
                        for (auto ch_a : A) {
                            for (auto ch_b : B) {
                                auto new_state = dp[match_a][match_b][diff + kMaxN];
                                new_state.a += ch_a.first;
                                new_state.m_a += ch_a.second;
                                new_state.b += ch_b.first;
                                new_state.m_b += ch_b.second;
                                new_state.sol.push_back(ch);

                                dp[new_state.m_a][new_state.m_b][new_state.a - new_state.b + kMaxN].Update(new_state);
                            }
                        }
                    }
                }
            }
        }

        DPState f;
        f.a = 100000000;
        f.b = 100000000;
        for (int i = 0; i <= n; i += 1) {
            for (int j = 0; j <= m; j += 1) {
                for (int diff = -kMaxN; diff < kMaxN; diff += 1) {
                    if (dp[i][j][diff + kMaxN].valid) {
//                        auto& c = dp[i][j][diff + kMaxN];
//                        cerr << i << '\t' << j << '\t' << c.a << '\t' << c.b << '\t' << c.sol << '\n';
                        f.FinalUpdate(dp[i][j][diff + kMaxN]);
                    }
                }
            }
        }
        cout << "Case #" << t << ": " << f.sol << '\n';
        cerr << f.a << '\t' << f.b << '\n';
    }

    return 0;
}
