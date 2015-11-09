#include <fstream>
#include <vector>
using namespace std;



const int kMod = 5e6 + 11;

ifstream fin("hashuri.in");
ofstream fout("hashuri.out");

const int kMaxChar = 1e4;
#define verf ((++BufferChar >= kMaxChar) ? (fin.read(Buffer, kMaxChar), BufferChar = 0) : (1))

int BufferChar = kMaxChar;
char Buffer[kMaxChar];

void cit (int &a) {
    if (BufferChar >= kMaxChar)
        verf;
    bool minus = false;
    for ( ;!((Buffer[BufferChar] >= '0' && Buffer[BufferChar] <= '9') || (Buffer [BufferChar] == '-')); verf)
        ;
    if (Buffer[BufferChar] == '-') {
        verf;
        minus = true;
    }
    for (a = 0; (Buffer[BufferChar] >= '0' && Buffer[BufferChar] <= '9'); a *= 10,a += (Buffer[BufferChar] - '0'), verf)
        ;
    if (minus)
        a *= -1;
    return ;
}

int Hash[kMod];

void mod(int &v) {
    while (v >= kMod) {
        v -= kMod;
    }
}

int search(int val, vector<int> target) {
    val %= kMod;
    for (int j = 1; ; ++j) {
        val += 1 + 2 * (j - 1);
        mod(val);
        int hash = Hash[val];
        for (auto itr : target) {
            if (itr == hash) {
                return val;
            }
        }
    }
}

int main() {
    for (int i = 0; i < kMod; ++i) {
        Hash[i] = -1;
    }
    int n; cit(n);
    while (n--) {
        int t, x, pos; cit(t); cit(x);
        if (t == 1) {
            pos = search(x, {x, -1, -2});
            Hash[pos] = x;
        } else if (t == 2) {
            pos = search(x, {x, -1});
            if (Hash[pos] == x) {
                Hash[pos] = -2;
            }
        } else {
            pos = search(x, {x, -1});
            if (Hash[pos] == x) {
                fout << "1\n";
            } else {
                fout << "0\n";
            }
        }
    }
    return 0;
}
