#include <bitset>
#include <iostream>
using namespace std;

#define NumBits bitset<32>

NumBits reverseXor(NumBits a, int v) {
    bitset<32> rez;
    for (int i = 0; i < v; ++i) {
        rez[31 - i] = a[31 - i];
    }
    for (int pozRez = 31 - v, pozA = 31; pozRez >= 0; --pozRez, --pozA) {
        //rez[pozRez] ^ rez[pozA] = a[pozRez];
        rez[pozRez] = a[pozRez] ^ rez[pozA];
    }
    return rez;
}

NumBits reversePlus(NumBits a, int v) {
    bitset<70> rez;
    for (int i = 0; i < v; ++i) {
        rez[i] = a[i]; 
    }
    int carry = 0;
    for (int pozRez = v, pozA = 0; pozRez < 32; ++pozRez, ++pozA) {
        rez[pozRez] = a[pozRez] ^ rez[pozA] ^ carry;
        carry = (carry + rez[pozRez] + rez[pozA]) >= 2;
    }
    for (int i = 0; i < 32; ++i) {
        a[i] = rez[i];
    }
    return a;
}

NumBits reverse(NumBits a) {
    a = reversePlus(a, 16);
    a = reverseXor(a, 11);
    a = reversePlus(a, 3);
    a = reverseXor(a, 6);
    a = reversePlus(a, 10);
    return a;
}

unsigned int H(unsigned int v) {
    v = v + (v << 10);
    v = v ^ (v >> 6);
    v = v + (v << 3);
    v = v ^ (v >> 11);
    v = v + (v << 16);
    return v;
}

int main() {
    int t; cin >> t;
    while (t--) {
        long long x; cin >> x;
//        unsigned int v = 0b11100101011100110011111111011;
//        cout << v << '\n';
//        x = H(v);
        NumBits number;
        for (int i = 0; i <= 31; ++i) {
            number[i] = x & 1;
            x /= 2;
        }
        number = reverse(number);
        x = 0;
        for (int i = 31; i >= 0; --i) {
            x *= 2LL;
            x += number[i];
        }
        cout << x << '\n';
    }
}
