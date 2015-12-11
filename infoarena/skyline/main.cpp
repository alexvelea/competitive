#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

#define int64 long long 

// const int kMaxN = 4e4 + 4;

ifstream fin("skyline.in");
ofstream fout("skyline.out");

vector<pair<int, int> > elements;

template<typename t>
void Reverse(t &array) {
    reverse(array.begin(), array.end());
}

vector<int64> useStack(vector<pair<int, int> > elements) {
    vector<int64> result, sum(elements.size());
    result.reserve(elements.size());
    stack<int> stk;

    int64 actualSum = 0;
    for (int i = 0; i < int(elements.size()); i += 1) {
        actualSum += elements[i].second;
        sum[i] = actualSum;
    }
    for (int i = 0; i < int(elements.size()); i += 1) {
        auto itr = elements[i];
        while (stk.size() and elements[stk.top()].first >= itr.first) {
            stk.pop();
        }
        int64 leftIndex = 0;
        if (stk.size()) {
            leftIndex = sum[stk.top()];
        }

        result.push_back(sum[i] - itr.second - leftIndex);
        stk.push(i);
    }

    return result;
}

int main() {
    int n; fin >> n;
    for (int i = 0; i < n; ++i) {
        int h, length; fin >> h >> length;
        elements.push_back({h, length});
    }
    auto left = useStack(elements);
    Reverse(elements);
    auto right = useStack(elements);
    Reverse(right);
    Reverse(elements);

    int64 result = 0;
    for (int i = 0; i < int(elements.size()); i += 1) {
        result = max(result, elements[i].first * (left[i] + right[i] + elements[i].second));
    }
    fout << result << '\n';
    return 0;
}
