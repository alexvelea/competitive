#include <iostream>
#include <set>
using namespace std;
int main() {
    set<int> s = {1, 5, 10, 15};
    auto itr = s.lower_bound(5);
    cout << *itr << '\n';
    return 0;
}
