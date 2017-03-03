#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n, m, _time;

int& Mod(int& a) {
    if (a >= m) {
        return a %= m;
    } else if (a < m) {
        return Mod(a += m);
    } else {
        return a;
    }
}


#define F first
#define S second
#define pb push_back
#define mp make_pair
#define forn(i, n) for(int i = 0 ; (i) < (n) ; ++i)
#define eprintf(...) fprintf(stderr, __VA_ARGS__),fflush(stderr)
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),a.end()
#define pw(x) (1LL<<(x))

using namespace std;

typedef long long ll;
typedef double dbl;
typedef vector<int> vi;
typedef pair<int, int> pi;

const int inf = 1.01e9;
const dbl eps = 1e-9;

/* --- main part --- */

namespace fft
{
    const int maxBase = 19;
    const int maxN = 1 << maxBase;

    struct num
    {
        dbl x, y;
        num(){}
        num(dbl xx, dbl yy): x(xx), y(yy) {}
        num(dbl alp): x(cos(alp)), y(sin(alp)) {}
    };

    inline num operator + (num a, num b) { return num(a.x + b.x, a.y + b.y); }
    inline num operator - (num a, num b) { return num(a.x - b.x, a.y - b.y); }
    inline num operator * (num a, num b) { return num(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
    inline num conj(num a) { return num(a.x, -a.y); }

    const dbl PI = acos(-1);

    num root[maxN];
    int rev[maxN];
    bool rootsPrepared = false;

    void prepRoots()
    {
        if (rootsPrepared) return;
        rootsPrepared = true;
        root[1] = num(1, 0);
        for (int k = 1; k < maxBase; ++k)
        {
            num x(2 * PI / pw(k + 1));
            for (int i = pw(k - 1); i < pw(k); ++i)
            {
                root[2 * i] = root[i];
                root[2 * i + 1] = root[i] * x;
            }
        } 
    }    

    int base, N;

    int lastRevN = -1;
    void prepRev()
    {
        if (lastRevN == N) return;
        lastRevN = N;
        forn(i, N) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (base - 1));
    }

    void fft(num *a, num *f)
    {
        forn(i, N) f[i] = a[rev[i]];
        for (int k = 1; k < N; k <<= 1) for (int i = 0; i < N; i += 2 * k) forn(j, k)
        {
            num z = f[i + j + k] * root[j + k];
            f[i + j + k] = f[i + j] - z;
            f[i + j] = f[i + j] + z;
        }
    }

    num a[maxN], b[maxN], f[maxN], g[maxN];
    ll A[maxN], B[maxN], C[maxN];

    void _multMod(int mod)
    {
        forn(i, N)
        {
            int x = A[i] % mod;
            a[i] = num(x & (pw(15) - 1), x >> 15);
        }
        forn(i, N)
        {
            int x = B[i] % mod;
            b[i] = num(x & (pw(15) - 1), x >> 15);
        }
        fft(a, f);
        fft(b, g);

        forn(i, N)
        {
            int j = (N - i) & (N - 1);
            num a1 = (f[i] + conj(f[j])) * num(0.5, 0);
            num a2 = (f[i] - conj(f[j])) * num(0, -0.5);
            num b1 = (g[i] + conj(g[j])) * num(0.5 / N, 0);
            num b2 = (g[i] - conj(g[j])) * num(0, -0.5 / N);
            a[j] = a1 * b1 + a2 * b2 * num(0, 1);
            b[j] = a1 * b2 + a2 * b1;
        }
        
        fft(a, f);
        fft(b, g);

        forn(i, N)
        {
            ll aa = f[i].x + 0.5;
            ll bb = g[i].x + 0.5;
            ll cc = f[i].y + 0.5;
            C[i] = (aa + bb % mod * pw(15) + cc % mod * pw(30)) % mod;
        }
    }

    void prepAB(int n1, int n2)
    {
        base = 1;
        N = 2;
        while (N < n1 + n2) base++, N <<= 1;
        assert(base <= maxBase);

        for (int i = n1; i < N; ++i) A[i] = 0;
        for (int i = n2; i < N; ++i) B[i] = 0;

        prepRoots();
        prepRev();
    }

    void mult(int n1, int n2)
    {
        prepAB(n1, n2);
        forn(i, N) a[i] = num(A[i], B[i]);
        fft(a, f);
        forn(i, N)
        {
            int j = (N - i)  & (N - 1);
            a[i] = (f[j] * f[j] - conj(f[i] * f[i])) * num(0, -0.25 / N);
        }
        fft(a, f);
        forn(i, N) C[i] = (ll)round(f[i].x);
    }


    void multMod(int n1, int n2, int mod)
    {
        prepAB(n1, n2);
        _multMod(mod);
    }

    int D[maxN];

    void multLL(int n1, int n2)
    {
        prepAB(n1, n2);

        int mod1 = 1.5e9;
        int mod2 = mod1 + 1;

        _multMod(mod1);

        forn(i, N) D[i] = C[i];

        _multMod(mod2);

        forn(i, N)
        {
            C[i] = D[i] + (C[i] - D[i] + (ll)mod2) * (ll)mod1 % mod2 * mod1;
        }
    }
    // HOW TO USE ::
    // -- set correct maxBase
    // -- use mult(n1, n2), multMod(n1, n2, mod) and multLL(n1, n2)
    // -- input  : A[], B[]
    // -- output : C[]
}

struct Poli {
    vector<int> elements;
    Poli(int num_elements) : elements(num_elements, 0) { }
    Poli operator* (const Poli& rhs) {
        Poli p(size() + rhs.size() - 1);
        for (int i = 0; i < size(); i += 1) {
            for (int j = 0; j < rhs.size(); j += 1) {
                p.elements[i + j] += elements[i] * rhs.elements[j];
                Mod(p.elements[i + j]);
            }
        }

        return p;
    }

    Poli operator+ (const Poli& rhs) {
        for (int i = 0; i < size(); i += 1) {
            fft::A[i] = elements[i];
        }
        for (int i = 0; i < rhs.size(); i += 1) {
            fft::B[i] = rhs.elements[i];
        }

        Poli p(size() + rhs.size() - 1);
        fft::multMod(size(), rhs.size(), m);
        for (int i = 0; i < rhs.size() + size() - 1; i += 1) {
            p.elements[i] = fft::C[i];
        }

        return p;
    }

    int size() const { return elements.size(); }

    void Trim() {
        for (int i = n; i < size(); i += 1) {
            Mod(elements[i % n] += elements[i]);
        }
        elements.resize(min(size(), n));
        for (int i = 0; i < size(); i += 1) {
            Mod(elements[i % n]);
        }
    }

    void Debug() {
        cerr << "~~~~~~~\n";
        for (auto itr : elements) {
            cerr << itr << '\t';
        }
        cerr << '\n';
    }
};

Poli Pow(Poli p, int _time) {
    p.Trim();
    Poli result(1);
    result.elements[0] = 1;
    while (_time) {
        if (_time & 1) {
            result = result + p;
            result.Trim();
        }
        p = p + p;
        p.Trim();
        _time /= 2;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m >> _time;

        Poli p(2);
        p.elements[0] = -1;
        p.elements[1] = +2;
        auto exp = Pow(p, _time);
 
        Poli values(2 * n);
        for (int i = 0; i < n; i += 1) {
            cin >> values.elements[i];
            values.elements[i] -= 1;
            values.elements[i + n] = values.elements[i];
        }

        reverse(exp.elements.begin(), exp.elements.end());
        
        int bonus = exp.size() - 1;
        
        exp.Trim();
        values = values + exp;
        
        for (int i = bonus; i < bonus + n; i += 1) {
            cout << 1 + values.elements[i] << ' ';
        }
        cout << '\n';
    }
}

