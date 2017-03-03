#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <set>
using namespace std;

const int inf = 0x3f3f3f3f;
const int kMaxN = 1e5+5, kBucketSize = 300, kMaxNumBuckets = kMaxN / kBucketSize + 5;

vector<pair<int, int>> queries_inside_bucket[kMaxNumBuckets][kBucketSize];
vector<tuple<int, int, int>> long_queries[kMaxNumBuckets];

int n;
int el[kMaxN];

int Bucket(int a) {
    return a / kBucketSize;
}

bool visited[kMaxN];
vector<int> answer;

double inside = 0;

void SolveLong(int bl) {
    auto& queries = long_queries[bl];
    if (queries.size() == 0) {
        return;
    }

    sort(queries.begin(), queries.end());

    int left = bl * kBucketSize;

    int mn_dist = +inf;
    set<int> inside_values;

    int index = 0;

    vector<vector<int>> elements_before;
    vector<int> mn_dist_inside(kBucketSize + 1, inf);
    vector<int> last_el(kBucketSize + 1, left - 1);

    for (int i = 0; i <= kBucketSize; i += 1) {
        vector<int> e;
        for (int j = 0; j < i; j += 1) {
            e.push_back(left - j - 1);
        }
        sort(e.begin(), e.end());
        for (int j = 0; j + 1 < i; j += 1) {
            mn_dist_inside[i] = min(mn_dist_inside[i], e[j + 1] - e[j]);
        }
        elements_before.push_back(e);
    }

    for (int i = left; i < n and index < (int)queries.size(); i += 1) {
        // solve bucket
        while (index < (int)queries.size() and get<0>(queries[index]) == i) {
            time_t now = clock();
            int current_left = - get<1>(queries[index]);
            int query_index = get<2>(queries[index]);

            int bucket = left - current_left;
            int& last = last_el[bucket];

            auto Add = [&](int val) {
                
            };

            while (last < i) {
                Add(el[last]);
            }

            answer[query_index] = min(current, mn_dist_inside[bucket]);

            inside += 1.0 * (clock() - now) / CLOCKS_PER_SEC;

            index += 1;
        }
        
    }
}

void SolveSmall(int b) {
    int left = b * kBucketSize;
    int right = min((b + 1) * kBucketSize, n);
    for (int start = 0; start + left < right; start += 1) {
        vector<int> elements;
        int mn_dist = +inf;
        int index = 0;
        auto& queries = queries_inside_bucket[b][start];
        for (int finish = start; finish + left < right and index < (int)queries.size(); finish += 1) {
            // add finish el
            for (auto itr : elements) {
                mn_dist = min(mn_dist, abs(itr - el[left + finish]));
            }
            elements.push_back(el[left + finish]);

            while (index < (int)queries.size() and queries[index].first == finish + left) {
                answer[queries[index].second] = mn_dist;
                index += 1;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i += 1) {
        cin >> el[i];
    }

    int q; cin >> q;
    answer = vector<int>(q, -1);
    for (int i = 0; i < q; i += 1) {
        int a, b; cin >> a >> b;
        a -= 1;
        b -= 1;
        int ba = Bucket(a);
        int bb = Bucket(b);

        if (ba == bb) {
            queries_inside_bucket[ba][a % kBucketSize].push_back({b, i});
        } else {
            long_queries[ba + 1].push_back(make_tuple(b, -a, i));
        }
    }

    for (int i = 0; i < kMaxNumBuckets; i += 1) {
        for (int j = 0; j < kBucketSize; j += 1) {
            sort(queries_inside_bucket[i][j].begin(), queries_inside_bucket[i][j].end());
        }
    }


    for (int i = 1; i < kMaxNumBuckets; i += 1) {
        SolveLong(i);
    }
    

    for (int i = 0; (i - 1) * kMaxNumBuckets < n; i += 1) {
        SolveSmall(i);
    }

    cerr << inside << '\n';

    for (auto itr: answer) {
        cout << itr << '\n';
    }
    return 0;
}
