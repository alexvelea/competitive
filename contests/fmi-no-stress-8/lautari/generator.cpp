#include <tumbletest>
#include <generator_utils>

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

string random(int n) {
    int l = xRandLog(1, n);
    int r = xRandLog(l, n);
    string result = StrCat(n, ' ', l, ' ', r, '\n');
    for (int i = 0; i < n; i += 1) {
        result += StrCat(rand() % (2 * r), ' ');
    }
    return result;
}

int main() {
    addTest(random(10));
    RunTumbletest();
    TestSources(200, "brut.cpp");
    return 0;
}
