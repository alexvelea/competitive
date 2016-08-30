#include <cstring>
#include <algorithm>
#include <functional>

#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long int64;

typedef double float64;
typedef long double float128;

const int kInf = 0x3f3f3f3f, kMaxN = 1e3+5;

#pragma pack(4)
struct Shit {
    short a; char b;
    Shit(int x) {
        a = x >> 15;
        b = x & ((1 << 16) - 1);
    }
    Shit() {
        a = b = 0;
    }

    int get() {
        return (a << 15) + b;
    }
};

int cell[kMaxN][kMaxN];
Shit _buffer[kMaxN];
Shit _cell[kMaxN][kMaxN];

const int kMaxBuff = 2e7;

volatile char Bufer[kMaxBuff];
volatile char* poz;

// #########    parsare
/*
    1e5 int32   fin     0.06s   read    0.012s  optimization    0.048
    1e6 int32   fin     0.56s   read    0.1s    optimization    0.46 
    1e7 int32   fin     4.89s   read    0.79s   optimization    4.1
    1e8 int32   fin     49.230s read    7.836s  optimization    41.3
*/

const int kBufferSize = 1e4;
int bufferInd = kBufferSize;
char buffer[kBufferSize];

void nextChar() {
    if (++bufferInd >= kBufferSize) {
        cin.read(buffer, kBufferSize);
        bufferInd = 0;
    }
}

bool valid(char c) {
    return (c == '-' or ('0' <= c and c <= '9'));
}

char currentChar() {
    if (bufferInd > kBufferSize) {
        nextChar();
    }
    return buffer[bufferInd];
}

template<typename number>
void readNumber(number &a) {
    a = 0;
    bool signedNumber = false;
    if (currentChar() == '-') {
        signedNumber = true;
    }

    for (; not valid(currentChar()); nextChar())
        ;

    for (; valid(currentChar()); nextChar()) {
        a *= 10;
        a += currentChar() - '0';
    }

    if (signedNumber) {
        a *= -1;
    }
    return ;
}

// #########    endParsare

#define read(x) for(;*poz<'0';poz++); for(x=0;*poz>='0';poz++) x =(x<<3)+(x<<1) + ((*poz) &  207 );

int main() {
    poz=Bufer;
    ios_base::sync_with_stdio(false);

    fread((void*) Bufer,1,kMaxBuff,stdin);
    int n, m, q;
    read(n);
    read(m);
    read(q);

    // readNumber(n);
    // readNumber(m);
    // readNumber(q);
    
    vector<int> u;

    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            read(cell[i][j]);
            // readNumber(cell[i][j]);
//            u.push_back(cell[i][j]);
        }
    }   
/*
    sort(u.begin(), u.end());
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            int x = cell[i][j];
            int y = 0;
            for (int p = 19; p >= 0; p-= 1) {
                if (y + (1 << p) < (int)u.size()) {
                    if (u[y + (1 << p)] <= x) {
                        y += (1 << p);
                    }
                }
            }
            x = y;
        //    x = lower_bound(u.begin(), u.end(), x) - u.begin();
            _cell[i][j] = Shit(x);
        }
    }   
*/
    while (q--) {
        int a, b, c, d, h, w;
        read(a);
        read(b);
        read(c);
        read(d);
        read(h);
        read(w);
        // readNumber(a);
        // readNumber(b);
        // readNumber(c);
        // readNumber(d);
        // readNumber(h);
        // readNumber(w);
        for (int i = 0; i < h; i += 1) {
            int l1 = i + a;
            int l2 = i + c;
            memcpy(_buffer, cell[l1] + b, w << 2);
            memcpy(cell[l1] + b, cell[l2] + d, w << 2);
            memcpy(cell[l2] + d, _buffer, w << 2);
            /*
            memcpy(_buffer, _cell[l1] + b, w * 3);
            memcpy(_cell[l1] + b, _cell[l2] + d, w * 3);
            memcpy(_cell[l2] + d, _buffer, w * 3);
            */
        }
    }

    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
           // int x = _cell[i][j].get();
           // cout << u[x] << ' ';
            cout << cell[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
