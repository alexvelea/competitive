#include <fstream>
#include <iostream>
#include <thread>
using namespace std;

const int kMaxN = 1e7 + 5, kThreadLimit = 8;

int el[kMaxN];
int first = 0;

void quickSort(int st, int dr) {
    if (st >= dr) {
        return ;
    }

    int mid = rand() % (dr - st + 1) + st;
    int e = el[mid];
    int l = st - 1;
    for (int i = st; i <= dr; ++i) {
        if (el[i] <= e) {
            swap(el[i], el[++l]);
        }
    }
    if (first < kThreadLimit) {
        first++;
        cerr << "PENIS!\n";
        thread T1(quickSort, st, l);
        quickSort(l + 1, dr);
        T1.join();
    } else {
        quickSort(st, l);
        quickSort(l + 1, dr);
    }
}

int main() {
    ifstream fin("data.txt");
    int n; fin >> n;
    for (int i = 1; i <= n; ++i) {
        fin >> el[i];
    }
//    sort(el + 1, el + n + 1);
    quickSort(1, n);
//    sort(el + 1, el + n + 1);
/*    for (int i = 1; i <= n; ++i) {
        cerr << el[i] << '\n';
    }*/
    return 0;
}
