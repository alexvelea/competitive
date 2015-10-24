//Problem c @ 08-08-2015
#include <bits/stdc++.h>
using namespace std;

const int kMaxN = 3e2+5, kMaxLog = 10;

#define int64 long long

struct rmq {
    unsigned int el[kMaxLog][kMaxLog];
};

rmq RMQ[kMaxN][kMaxN];

const int kBufferSize = 20e6;
char Buffer[kBufferSize];
int bufferInd = kBufferSize;

#define actualChar Buffer[bufferInd]
inline void nextChar() {
    if (++bufferInd >= kBufferSize) {
        bufferInd = 0;
        cin.get(Buffer, kBufferSize, EOF);
    }
}

void get(int &a) {
    nextChar();
    a = 0;
    for (; not (actualChar >= '0' and actualChar <= '9'); nextChar());
    for (; actualChar >= '0' and actualChar <= '9'; nextChar()) {
        a *= 10;
        a += actualChar - '0';
    }
}

void get(unsigned int &a) {
    nextChar();
    a = 0;
    for (; not (actualChar >= '0' and actualChar <= '9'); nextChar());
    for (; actualChar >= '0' and actualChar <= '9'; nextChar()) {
        a *= 10;
        a += actualChar - '0';
    }
}  

int main() {
	ios::sync_with_stdio(false);
    int n, m; 
    get(n); get(m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            get(RMQ[i][j].el[0][0]);
        }
    }
    for (int l = 0; l < kMaxLog; ++l) {
        for (int c = 1; c < kMaxLog; ++c) {
	        for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    RMQ[i][j].el[l][c] = RMQ[i][j].el[l][c - 1];
                    if (j + (1 << (c - 1)) <= m) {
                        RMQ[i][j].el[l][c] = max(RMQ[i][j].el[l][c], RMQ[i][j + (1 << (c - 1))].el[l][c - 1]);
                    }
                }
            }
        }

        if (l + 1 == kMaxLog) {
            continue;
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                RMQ[i][j].el[l + 1][0] = RMQ[i][j].el[l][0];
                if (i + (1 << l) <= n) {
                    RMQ[i][j].el[l + 1][0] = max(RMQ[i][j].el[l + 1][0], RMQ[i + (1 << l)][j].el[l][0]);
                }
            }
        }
    }
    
    vector<int> log(kMaxN);
    log[1] = 0;
    for (int i = 2; i < kMaxN; ++i) {
        log[i] = log[i - 1];
        if ((1 << (log[i] + 1)) <= i) {
            ++log[i];
        }
    }
    
    int q; get(q);
    while (q--) {
        int x0, y0, x1, y1; 
        get(x0); get(y0); get(x1); get(y1);
        int dx = x1 - x0 + 1;
        int dy = y1 - y0 + 1;
        int lx = log[dx];
        int ly = log[dy];
        
        dx = (1 << lx) - 1;
        dy = (1 << ly) - 1;

        unsigned int mx = 0;
        mx = max(mx, RMQ[x0][y0].el[lx][ly]);
        mx = max(mx, RMQ[x1 - dx][y0].el[lx][ly]);
        mx = max(mx, RMQ[x1 - dx][y1 - dy].el[lx][ly]);
        mx = max(mx, RMQ[x0][y1 - dy].el[lx][ly]);
        cout << mx << ' ' << ((RMQ[x0][y0].el[0][0] == mx or RMQ[x0][y1].el[0][0] == mx or RMQ[x1][y0].el[0][0] == mx or RMQ[x1][y1].el[0][0] == mx) ? "yes" : "no") << '\n';
    }
    return 0;
}
