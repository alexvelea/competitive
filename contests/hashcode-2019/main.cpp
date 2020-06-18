#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#include <unistd.h> // getpid

#include "include/HashCode.hpp"
#include "include/DefaultCode.hpp"

using namespace std;

int main(int argc, char** argv) {
    srand(time(0) + getpid());
    InitHashCode(argc, argv);

    input = Input(GetInputStream());
    input.MergeVerticalRandom();
//    input.MergeVerticalSmart();

    {
        map<int, int> cnt;
        for (auto& itr : input.all_photos) {
            for (auto t : itr.tags) {
                cnt[t] += 1;
            }
        }

        vector<pair<int, int>> q;
        for (auto& itr : cnt) {
            q.push_back(itr);
        }

        vector<int> where(input.max_tag + 1);

        sort(q.begin(), q.end(), [](auto a, auto b) { return a.second > b.second; });

        for (int i = 0; i < (int)q.size(); i += 1) {
            where[q[i].first] = i + 1;
        }

        for (auto& itr : input.all_photos) {
            itr.ApplyTagPermutation(where);
        }
    }

    if (true) {
        auto q = input.all_photos;
        sort(q.begin(), q.end(), [](auto a, auto b) { return a.tags < b.tags; });

        Debug(input.all_photos.size(), q.size(), Output(q).Cost());
        input.all_photos = q;
    }

    if (false) {
        auto q = InitialOrderBasedOnPairsOfTags(input.all_photos, 16675);

        Debug(input.all_photos.size(), q.size(), Output(q).Cost());
        input.all_photos = q;
    }

    map<pair<int, int>, int> cnt;

    for (int i = 1; i <= input.max_tag; i += 1) {
        for (int j = i + 1; j <= 36; j += 1) {
            int num = 0;
            for (auto& itr : input.all_photos) {
                if (itr.HasTag(i) and itr.HasTag(j)) {
                    num += 1;
                }
            }

            cnt[{i, j}] = num;
            Debug(i, j, num);
        }
    }

    {
    vector<pair<pair<int, int>, int>> cnt2(cnt.begin(), cnt.end());
    sort(cnt2.begin(), cnt2.end(), [](auto a, auto b) {
        return a.second > b.second;
    });

    for (int i = 0; i < 100; i += 1) {
        Debug(cnt2[i].first.first, cnt2[i].first.second, cnt2[i].second);
    }

    }

    return 0;

    vector<int> v = {0, 0, 0, 0};
    for (auto& itr : input.all_photos) {
        v[itr.HasTag(1) + 2 * itr.HasTag(2)] += 1;
    }

    Debug(v);

    return 0;


    {
        map<int, int> cnt;
        for (auto& itr : input.all_photos) {
            for (auto t : itr.tags) {
                cnt[t] += 1;
            }
        }

        vector<pair<int, int>> q;
        for (auto& itr : cnt) {
            q.push_back(itr);
        }

        sort(q.begin(), q.end(), [](auto a, auto b) { return a.second > b.second; });
        for (int i = 0; i < 100; i += 1) {
            auto& itr = q[i];
            //    for (auto& itr : q) {
            cerr << itr.first << ' ' << itr.second << '\n';
        }
    }

    {
        map<pair<int, int>, int> cnt;
        map<int, int> cnt2;
        for (int i = 0; i + 1 < (int)input.all_photos.size(); i += 1) {
            auto a = input.all_photos[i].CostStats(input.all_photos[i + 1]);
            cnt2[a.first - a.second] += 1;
            cnt[a] += 1;
        }

        Debug(cnt2);
    }
    GoodRandomSwaps(input.all_photos);
}
