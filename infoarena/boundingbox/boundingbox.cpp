// toate fractiile din rez_dreptunghi au la numitor 50
// lucram cu numitorul 2^50 peste tot
// indiferent cate valori de 1 avem
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
using namespace std;
 
#define int64 long long
 
ifstream in("boundingbox.in");
ofstream out("boundingbox.out");
 
map<int64, int64> rez_dreptunghi;
 
int el[50][50], sum[50][50];
 
inline int64 codif(int a, int b, int c, int d, int t) {
    return 1LL * t * 51 * 51 * 51 * 51 + 1LL * a * 51 * 51 * 51 + 1LL * b * 51 * 51 + 1LL * c * 51 + 1LL * d; }
 
void solve_back(int a, int b, int c, int d, int t) {
    int64 nr_sol = 0;
    int under_pow = a + b + c + d;   
    for (int i = 0; i < 4; ++i)
        if (t & (1 << i))
            ++under_pow;
    int x[4] = {a, b, c, d};
 
    for (int i = 0; i < 16; ++i)
        if ((i | t) == t) {
            int64 now = 1;
            int T = i | ((i & 1) << 4);
            for (int p = 0; p < 4; ++p) {
                if ((T & (1 << p)) or (T & (1 << (p + 1))))
                    now *= 1LL << x[p];
                else
                    now *= (1LL << x[p]) - 1;
            }
            nr_sol += now;
        }
    nr_sol = (1LL * nr_sol) << (50LL - under_pow);
    rez_dreptunghi[codif(a, b, c, d, t)] = nr_sol;
}
 
int main() {
    for (int sta = 0; sta <= 48; ++sta)
        for (int stb = 0; stb <= 48; ++stb)
            for (int dra = 0; dra <= 48 and (dra + 2) * (max(sta, stb) + 2) <= 50; ++dra)
                for (int drb = 0; (drb + 2) * (max(sta, stb) + 2) <= 50; ++drb) {
                    for (int t = 0; t < 16; ++t) {
                        solve_back(sta, dra, stb, drb, t);
                    }
                }
     
    int t;
    in >> t;
    while (t--) {
        int n, m, total;
        total = 0;
        in >> n >> m;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                char c;
                in >> c;
                el[i][j] = c - '0';
                total += c - '0';
            }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                sum[i][j] = sum[i][j - 1] + el[i][j];
 
        int64 rez = total * (1LL << (50 - total));
        for (int l = 1; l <= n; ++l) 
            for (int c1 = 1; c1 <= m; ++c1) {
                int inside;
                inside = el[l][c1];
                if (el[l][c1])
                    for (int c2 = c1 + 1; c2 <= m; ++c2) {
                        inside += el[l][c2];
                        if (el[l][c2] == 1)
                            rez += 1LL * (1LL << (50 - total + (inside - 2))) * (c2 - c1 + 1);
                    }
            }
 
        for (int c = 1; c <= m; ++c)
            for (int l1 = 1; l1 <= n; ++l1) {
                int inside;                                       
                inside = el[l1][c];
                if (el[l1][c])
                    for (int l2 = l1 + 1; l2 <= n; ++l2) {
                        inside += el[l2][c];
                        if (el[l2][c])
                            rez += 1LL * (1LL << (50 - total + (inside - 2))) * (l2 - l1 + 1);
                    }
            }
         
        for (int c1 = 1; c1 <= m; ++c1)
            for (int c2 = c1 + 1; c2 <= m; ++c2) 
                for (int l1 = 1; l1 <= n; ++l1) {
                    int inside, b1, b2, top;
                    inside = sum[l1][c2] - sum[l1][c1 - 1];
                    top = sum[l1][c2 - 1] - sum[l1][c1];
                    b1 = b2 = 0;
                    for (int l2 = l1 + 1; l2 <= n; ++l2) {
                        inside += sum[l2][c2] - sum[l2][c1 - 1];
                         
                        int bottom, outside;
                        bottom = sum[l2][c2 - 1] - sum[l2][c1];
                        outside = total - inside;
                        int T;
 
                        T = el[l2][c1] + el[l1][c1] * 2 + el[l1][c2] * 4 + el[l2][c2] * 8;
                        int64 val = (1LL * rez_dreptunghi[codif(b1, top, b2, bottom, T)]) / (1LL << outside);
                        val = 1LL * val * (l2 - l1 + 1) * (c2 - c1 + 1);
                        rez += val;
 
                        b1 += el[l2][c1];
                        b2 += el[l2][c2];                       
                    }
                }
        int p = 50;
        while (rez % 2 == 0 and rez != 0 and p != 0) {
            p--;
            rez /= 2;
        }
        if (rez == 0)
            p = 0;
        out << rez << '/' << (1LL << p) << '\n';
    }
    return 0;
}
