#include <tumbletest>
#include <generator_utils>

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

string random(int n, int k) {
    string a(n, ' ');
    for (int i = 0; i < n; i += 1) {
        a[i] = rand() % k + 'a';
    }
    string b= a;
    RandomShuffle(b);
    return a + ' ' + b;
}

int main() {
    for (int i = 8; i <= 9; i += 1) {
        for (int a = 1; a <= i; a += 1) {
            addTest(random(i, a));
        }
    }

    TestSources(200, "brut.cpp");
    return 0;
}
