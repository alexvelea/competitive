//Problem d @ 26-09-2015
#include <cassert>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int64 long long

string toString(int64 a) {
    string t = "";
    do {
        t += char('0' + a % 10);
        a /= 10;
    } while(a);
    reverse(t.begin(), t.end());
    return t;
}

int64 comb(int64 a, int64 b) {
    if (b == 0) {
        return 1;
    }
    
    if (b == 1) {
        return a;
    }

    if (b == 2) {
        return 1LL * (a) * (a - 1) / 2;
    }

    assert(0);
}

int64 getWildcard(string txt) {
    vector<int> remaining(10, 2);
    int nrW = 0;
    bool firstZ = true;
    for (auto itr : txt) {
        if (itr == '?') {
            nrW++;
        } else {
            if (itr - '0' == 0) {
                if (not firstZ) {
                    remaining[0]--;
                }
            } else {
                firstZ = false;
                remaining[itr - '0']--;
            }
        }
    }
    
    for (auto itr : remaining) {
        if (itr < 0) {
            return 0;
        }
    }


    vector<int64> lastD(nrW + 1, 0), nextD(nrW + 1, 0);
    lastD[0] = 1;
    for (int cif = (firstZ) ? (1) : (0); cif < 10; ++cif) {
//        cerr << cif;
        for (int nrC = 0; nrC <= remaining[cif]; ++nrC) {
            for (int nrCifI = 0; nrC + nrCifI <= nrW; ++nrCifI) {
                nextD[nrC + nrCifI] += 1LL * comb(nrC + nrCifI, nrC) * lastD[nrCifI];
            }
        }

        for (int i = 0; i <= nrW; ++i) {
            lastD[i] = nextD[i];
            nextD[i] = 0;
        }
    }

    //################## for 0 is shit
    for (int cif = 0; (firstZ) and cif < 1; ++cif) {
//        cerr << "@@@@@@@@\n";
        for (int nrC = 1; nrC <= remaining[cif]; ++nrC) {
            for (int nrCifI = 1; nrC + nrCifI <= nrW; ++nrCifI) {
                nextD[nrC + nrCifI] += 1LL * comb(nrC + nrCifI - 1, nrC) * lastD[nrCifI];
            }
        }

        for (int i = 0; i <= nrW; ++i) {
            lastD[i] += nextD[i];
            nextD[i] = 0;
        }
    }   
//    cerr << '\n';

    int64 rez = lastD[nrW];
    if (firstZ == true) {
        rez = 0;
        for (auto itr : lastD) {
            rez += itr;
        }
    }

    if (nrW == 0) {
        rez = 1;
    }

//    cerr << "#############\n\t" << txt << '\n' << rez << "\n\n";
    return rez;
}

int64 bt(int poz, string text, string now) {
//    cerr << poz << '\t' << text << '\t' << now << '\n';
    if (poz == int(text.size())) {
        return getWildcard(now);
    } else {
        int64 rez = 0;
        for (int i = 0; i < 10; ++i) {
            if (i + '0' < text[poz]) {
                now[poz] = i + '0';
                rez += getWildcard(now);
            }

            if (i + '0' == text[poz]) {
                now[poz] = i + '0';
                rez += bt(poz + 1, text, now);

                return rez;
            }
        }
    }
    assert(0);
    return -1;
}

string getW(string a) {
    string t = "";
    for (auto itr : a) {
        itr = 0;
        t += '?';
    }
    return t;
}

int main() {
	ios::sync_with_stdio(false);
    ifstream fin("exchange.in");
    ofstream fout("exchange.out");
    int64 a, b; fin >> a >> b; a--;
    string A = "", B = "";

    A = toString(a);
    B = toString(b);

    string AA = getW(A), BB = getW(B);

    int64 ra = bt(0, A, AA);
    int64 rb = bt(0, B, BB);
    
/*    for (int last = 0, i = 100; i <= 200; ++i) {
        cerr << i << '\t' << bt(0, toString(i), getW(toString(i))) - last << '\n';
        last = bt(0, toString(i), getW(toString(i)));
    }
    cerr << ra << '\t' << rb << '\n'; */
    fout << rb - ra << '\n';
	return 0;
}
