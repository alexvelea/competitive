#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

#define ll long long

ifstream in("heavy.in");
ofstream out("heavy.out");

ll el[305];

ll     gcd( ll a, ll b ) {
    ll     t;
    
    if ( a < 0 )
        a = -a;
    
    if ( ! b )
        return a;
    
    if ( b < 0 )
        b = -b;
    
    if ( ! a )
        return b;
    
    t = 0;
    
    while ( ! ( ( a | b ) & 1 ) ) {
        a >>= 1;
        b >>= 1;
        ++t;
    }
    
    while ( ! ( a & 1 ) )
        a >>= 1;
    
    while ( ! ( b & 1 ) )
        b >>= 1;
    
    while ( a != b ) {
        if ( a > b ) {
            a -= b;
            
            do {
                a >>= 1;
            } while ( ! ( a & 1 ) );
        }
        
        else {
            b -= a;
            
            do {
                b >>= 1;
            } while ( ! ( b & 1 ) );
        }
    }
    
    return a << t;
}

/*
ll gcd( ll a, ll b ) {
	if (b == 0)
		return a;
	if (a == 0)
		return b;
	while (b != 0) {
		a %= b;
		swap(a, b);
	}
	return a;
}*/

ll solve(ll a, ll d) {
	ll di = gcd(a, d);
	ll rez = 1;
	ll x = gcd(di, d);
	while (x != 1) {
		rez *= x;
		d /= x;
		di = x;
		x = gcd(di, d);
	}
	return rez;
}

int main() {
	int t;
	in >> t;
	while (t--) {
		int n;
		in >> n;
		for (int i = 1; i <= n; ++i)
			in >> el[i];
 		for (int dr = n; dr; --dr)
			for (int st = dr - 1; st; --st) {
				ll a = el[st];
				ll b = el[dr];
				ll d = gcd(a, b);
				d = gcd(a, b);
				if (d == 1)
					continue;
				ll d1 = solve(a / d, d);
				el[dr] /= d1;
				el[st] /= (d / d1);
			}
		for (int i = 1; i <= n; ++i)
			out << el[i] << ' ';
		out << '\n';
	}
}
