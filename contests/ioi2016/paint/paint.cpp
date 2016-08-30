#include "paint.h"

#include <cassert>

#include <vector>
#include <string>
#include <iostream>
using namespace std;

const int kMaxN=2e5;

string solve_puzzle(string txt, vector<int> lens) {
    int n = txt.size();
    int m = lens.size();

    vector<int> white_sums(n, 0);
    for (int i = 0; i < n; i += 1) {
        if (txt[i] == '_') {
            white_sums[i] = +1;
        }
    }

    int sum = 0;
    for (auto& itr : white_sums) {
        sum += itr;
        itr = sum;
    }

    auto WhiteSum = [&](int a, int b) -> int {
        if (a == 0) {
            return white_sums[b];
        } else {
            return white_sums[b] - white_sums[a - 1];
        }
    };

    vector<vector<bool>> left(m + 1, vector<bool>(n, 0)), right(m + 1, vector<bool>(n, 0));

    for (int i = 0; i < n; i += 1) {
        if (txt[i] == 'X') {
            break;
        }
        
        left[0][i] = true;
    }

    for (int i = n - 1; i >= 0; i -= 1) {
        if (txt[i] == 'X') {
            break;
        }

        right[0][i] = true;
    }


    auto OkLeft = [&](int pos, int index) -> bool {
        int l = lens[index - 1];
        if (pos - l + 1 < 0) {
            return false;
        }
        
        if (WhiteSum(pos - l + 1, pos) != 0) {
            return false;
        }

        if (index == 1) {
            if (pos - l + 1 == 0) {
                return true;
            }
            
            return left[0][pos - l];
        }

        if (not (pos - l - 1 >= 0)) {
            return false;
        }

        if (txt[pos - l] == 'X') {
            return false;
        }

        return left[index - 1][pos - l - 1];
    };

    auto OkRight = [&](int pos, int index) -> bool {
        int l = lens[m - index];
        if (pos + l - 1 >= n) {
            return false;
        }
        
        if (WhiteSum(pos, pos + l - 1) != 0) {
            return false;
        }

        if (index == 1) {
            if (pos + l == n) {
                return true;
            }
            
            return right[0][pos + l];
        }

        if (pos + l + 1 >= n) {
            return false;
        }

        if (txt[pos + l] == 'X') {
            return false;
        }

        return right[index - 1][pos + l + 1];
    };
 
    // compute left
    for (int i = 0; i < n; i += 1) {
        for (int k = 0; k <= m; k += 1) {
            if (txt[i] != 'X' and i > 0) {
                left[k][i] = left[k][i - 1];
            }
        }
        for (int k = 1; k <= m; k += 1) {
            if (OkLeft(i, k)) {
                left[k][i] = true;
            } 
        }
    }

    // compute right
    for (int i = n - 1; i >= 0; i -= 1) {
        for (int k = 0; k <= m; k += 1) {
            if (txt[i] != 'X' and i + 1 < n) {
                right[k][i] = right[k][i + 1];
            }
        }

        for (int k = 1; k <= m; k += 1) {
            if (OkRight(i, k)) {
                right[k][i] = true;
            }
        }
    }

    vector<int> black_final_sums(n + 1, 0);
    vector<int> white_answers(n, 0);
 
    for (int i = 0; i < n; i += 1) {
        if (txt[i] == 'X') {
            continue;
        }
        
        if (i == 0) {
            white_answers[i] = right[m][1];
            continue;
        }
        
        if (i == n - 1) {
            white_answers[i] = left[m][i - 1];
            continue;
        }

        for (int k = 0; k <= m; k += 1) {
            white_answers[i] = white_answers[i] | (left[k][i - 1] && right[m - k][i + 1]);
        }
    }
/*
    for (int i = 0; i < n; i += 1) {
        cerr << i << '\t';
        for (int k = 0; k <= m; k += 1) {
            cerr << left[k][i];
        }
        cerr << '\n';
    }
    cerr << "\n\n\n\n";

    for (int i = 0; i < n; i += 1) {
        cerr << i << '\t';
        for (int k = 0; k <= m; k += 1) {
            cerr << right[k][i];
        }
        cerr << '\n';
    }
*/
    for (int i = 0; i < n; i += 1) {
        for (int k = 1; k <= m; k += 1) {
            int l = i;
            int r = lens[k - 1] + l - 1;
            bool ok = true;

            if (r >= n) {
                ok = false;
            }

            if (l > 0 and txt[l - 1] == 'X') {
                ok = false;
            }

            if (r + 1 < n and txt[r + 1] == 'X') {
                ok = false;
            }

            if (WhiteSum(l, r) != 0) {
                ok = false;
            }

            if (not ok) {
                continue;
            }

            if (k == m) {
                if (r + 1 < n and (not right[0][r + 1])) {
                    ok = false;
                }

                if (l - 2 >= 0 and left[m - 1][l - 2] != true) {
                    ok = false;
                }

                if (l - 2 < 0 and m != 1) {
                    ok = false;
                }
            } else if (k == 1) {
               // cerr << "1\t" << i << "#@!#!@\n";
                if (l - 1 >= 0 and (not left[0][l - 1])) {
                    ok = false;
                }

 //               cerr << "1\t" << i << "(((())))\n";
   //             cerr << m - 1 << '\t' << r + 2 << '\n';
                if (r + 2 < n and right[m - 1][r + 2] != true) {
                    ok = false;
                }

                if (r + 2 >= n and m != 1) {
                    ok = false;
                }
     //           cerr << "1\t" << i << "??????\n";
            } else {
                if (l - 2 < 0) {
                    ok = false;
                }
                if (l - 2 >= 0 and left[k - 1][l - 2] != true) {
                    ok = false;
                }

                if (r + 2 >= n) {
                    ok = false;
                }

                if (r + 2 < n and right[m - k][r + 2] != true) {
                    ok = false;
                }
            }
    
            if (ok) {
                black_final_sums[l] += 1;
                black_final_sums[r + 1] += -1;
            }
        }
    }

    sum = 0;
    for (auto& itr : black_final_sums) {
        sum += itr;
        itr = sum;
    }
/*
    for (int i = 0; i < n; i += 1) {
        cerr << !!white_answers[i];
    }

    cerr << '\n';
    for (int i = 0; i < n; i += 1) {
        cerr << !!black_final_sums[i];
    }
    cerr << '\n';
*/
    string result(n, ' ');
    for (int i = 0; i < n; i += 1) {
        if (white_answers[i] and black_final_sums[i]) {
            result[i] = '?';
        } else if (white_answers[i]) {
            result[i] = '_';
        } else if (black_final_sums[i]) {
            result[i] = 'X';
        } else {
            assert(0);
        }
    }
    return result;
}
