#include "HashCode.hpp"
#include "Time.hpp"
#include <string>

typedef long long int64;
using namespace std;

struct Photo {
    string id;
    int type; // 1 = H, 2 = W
    vector<int> tags;
  
    bool HasTag(int t) {
        for (auto& itr : tags) {
            if (itr == t) {
                return true;
            }
        }
        return false;
    }

    int GetCost(const Photo& rhs) const {
        int num_common = 0;
        int a = 0, b = 0;
        while (a < (int)tags.size() and b < (int)rhs.tags.size()) {
            if (tags[a] == rhs.tags[b]) {
                a += 1;
                b += 1;
                num_common += 1;
            } else if (tags[a] < rhs.tags[b]) {
                a += 1;
            } else {
                b += 1;
            }
        }

        return min(num_common, int(min(tags.size(), rhs.tags.size())) - num_common);
    }

    pair<int,int> CostStats(const Photo& rhs) const {
        int num_common = 0;
        int a = 0, b = 0;
        while (a < (int)tags.size() and b < (int)rhs.tags.size()) {
            if (tags[a] == rhs.tags[b]) {
                a += 1;
                b += 1;
                num_common += 1;
            } else if (tags[a] < rhs.tags[b]) {
                a += 1;
            } else {
                b += 1;
            }
        }
        return {num_common, int(min(tags.size(), rhs.tags.size()))};
    }

    void ApplyTagPermutation(const vector<int>& perm) {
        for (auto& itr : tags) {
            itr = perm[itr];
        }

        sort(tags.begin(), tags.end());
    }

    Photo MergePhoto(const Photo& rhs) const {
        assert(type == 2 and rhs.type == 2);
        Photo res;
        res.type = 1;
        res.id = id + " " + rhs.id;
        res.tags = tags;
        for (auto& itr : rhs.tags) {
            res.tags.push_back(itr);
        }

        sort(res.tags.begin(), res.tags.end());
        res.tags.resize(unique(res.tags.begin(), res.tags.end()) - res.tags.begin());
        return res;
    }


};

struct Input {
    int max_tag;
    vector<Photo> all_photos;

    vector<Photo> horizontal;
    vector<Photo> vertical;

    Input(std::ifstream in) {
        int num_photos; in >> num_photos;
        Debug(num_photos);
        for (int i = 0; i < num_photos; i += 1) {
            Photo p;
            p.id = to_string(i);
            char c; in >> c;
            p.type = 1 + (c == 'V');
            int num_tags; in >> num_tags;
            while (num_tags--) {
                int tag; in >> tag;
                max_tag = max(max_tag, tag);
                p.tags.push_back(tag);
            }

            sort(p.tags.begin(), p.tags.end());
            
            if (p.type == 1) {
                horizontal.push_back(p);
            } else {
                vertical.push_back(p);
            }
        }
    }

    void MergeVertical(const vector<Photo>& rhs) {
        auto ans = horizontal;
        for (auto& itr : rhs) {
            ans.push_back(itr);
        }

        all_photos = ans;
        Debug(all_photos.size());
    }

    void MergeVerticalRandom() {
        Debug(vertical.size(), horizontal.size());
        random_shuffle(vertical.begin(), vertical.end());
        vector<Photo> ans;
        for (int i = 0; i + 1 < (int)vertical.size(); i += 2) {
            ans.push_back(vertical[i].MergePhoto(vertical[i + 1]));
        }

        Debug(ans.size());
        MergeVertical(ans);
    }

    void MergeVerticalSmart() {
        auto smart = vertical;
        random_shuffle(smart.begin(), smart.end());
        auto Cost = [&](int index) {
            if (index == -1 or index + 1 == (int)smart.size()) {
                return 0;
            }

            return smart[index].GetCost(smart[index + 1]);
        };

        auto Swaperino = [&](int a, int b) {
            int cost = 0;

            for (int i = 0; i < 2; i += 1) {
                cost -= Cost(a - i);
                cost -= Cost(b - i);
            }

            swap(smart[a], smart[b]);

            for (int i = 0; i < 2; i += 1) {
                cost += Cost(a - i);
                cost += Cost(b - i);
            }

            if (cost <= 0) {
                swap(smart[a], smart[b]);
            }
        };

        map<int, int> cnt;
        for (auto& itr : smart) {
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

        //        for (int i = 0; i < 1e6; i += 1) {
        for (int i = 0; i < 1e7; i += 1) {
            Swaperino(rand() % (int)smart.size(), rand() % (int)smart.size());
            if (i % int(1e5) == 0) {
                //                Debug(t.secElapsed(), output.Cost());
                //                t.start();
                //                Dump(output); // face treaba
                //                Debug(t.secElapsed());
                //                t.start();
                //                cerr << "+\n";
            }
        }
        vector<Photo> ans;
        for (int i = 0; i + 1 < (int)smart.size(); i += 2) {
            ans.push_back(smart[i].MergePhoto(smart[i + 1]));
        }
        MergeVertical(ans);
        Debug("Done merging verticals");
    }

    Input() { }
} input;


struct Output : BaseOutput {
    vector<Photo> photo_order;

    Output() { }
    Output(vector<Photo> p) : photo_order(p) { }

    void AddPhoto(const Photo& p) {
        photo_order.push_back(p);
    }

    double Cost() {
        int64 cost = 0;
        for (int i = 0; i + 1 < (int)photo_order.size(); i += 1) {
            cost += photo_order[i].GetCost(photo_order[i + 1]);            
        }
//        Debug(cost);
        return cost;
    }

    void Dump(ostream& out) {
        out << photo_order.size() << '\n';
        for (auto v : photo_order) {
            out << v.id << '\n';
        }
    }
};

vector<Photo> GoodRandomSwaps(const vector<Photo>& all_photos, int64 num_iterations = 1e18) {
    Output output;
    output.photo_order = all_photos;   
    auto initial_cost = output.Cost();
    Dump(output);

    auto Cost = [&](int index) {
        if (index == -1 or index + 1 == (int)output.photo_order.size()) {
            return 0;
        }

        return output.photo_order[index].GetCost(output.photo_order[index + 1]);
    };

    auto Swaperino = [&](int a, int b) {
        int cost = 0;
        
        for (int i = 0; i < 2; i += 1) {
            cost -= Cost(a - i);
            cost -= Cost(b - i);
        }

        swap(output.photo_order[a], output.photo_order[b]);

        for (int i = 0; i < 2; i += 1) {
            cost += Cost(a - i);
            cost += Cost(b - i);
        }

        if (cost <= 0) {
            swap(output.photo_order[a], output.photo_order[b]);
        }
    };



    Timer t;
    t.start();
    for (int64 i = 0; i < num_iterations; i += 1) {
        Swaperino(rand() % (int)output.photo_order.size(), rand() % (int)output.photo_order.size());
        if (i % int(1e6) == 0) {
            auto final_cost = output.Cost();
            Dump(output); // face treaba
    cerr << "Just finished bucket of tasks\n" 
         << "Increased score by " << final_cost - initial_cost << " (" << initial_cost << " ~ " << final_cost << ")\n";
 
        }
    }
    Dump(output);
    auto final_cost = output.Cost();

    cerr << "Just finished random swaps\n" 
         << "took               " << t.secElapsed() << " seconds\n"
         << "Increased score by " << final_cost - initial_cost << " (" << initial_cost << " ~ " << final_cost << ")\n";
    return output.photo_order;
}


vector<Photo> InitialOrderBasedOnPairsOfTags(const vector<Photo>& all_photos, int threshold) {
    struct Edge {
        int a, b, cost;

        bool operator<(const Edge& rhs) const {
            return make_tuple(-cost, a, b) < make_tuple(-rhs.cost, -rhs.a, -rhs.b);
        };
    };

    map<int, vector<int>> edges;

    for (int i = 0; i < (int)all_photos.size(); i += 1) {
        auto& p = all_photos[i];
        for (auto t : p.tags) {
            edges[t].push_back(i);
        }
    }

    vector<pair<int, int>> good_pairs;

    int64 estimated = 0;
    for (auto& itr : edges) {
        if ((int)itr.second.size() < threshold) { continue; }
        estimated += itr.second.size() * itr.second.size();
    }

    Debug(estimated);

    for (auto& itr : edges) {
        if ((int)itr.second.size() < threshold) { continue; }
        for (auto a : itr.second) {
            for (auto b : itr.second) {
                if (a < b) {
                    good_pairs.push_back({a, b});
                }
            }
        }
    }

    Debug("InitialOrderBasedOnPairsOfTags", good_pairs.size());

    sort(good_pairs.begin(), good_pairs.end());
    good_pairs.resize(unique(good_pairs.begin(), good_pairs.end()) - good_pairs.begin());

    
    vector<Edge> e;

    for (auto& p : good_pairs) {
        e.push_back({p.first, p.second, all_photos[p.first].GetCost(all_photos[p.second])});
    }

    Debug(e.size());
    sort(e.begin(), e.end());

    vector<int> num(all_photos.size());

    map<int, vector<int>> neighbours;
    for (auto& itr : e) {
        if (num[itr.a] == 2 or num[itr.b] == 2) {
            continue;
        }

        neighbours[itr.a].push_back(itr.b);
        neighbours[itr.b].push_back(itr.a);
    }

    vector<Photo> final_order;
    auto viz = vector<int>(all_photos.size(), false);

    int num_viz = 0;

    int last_1 = 0, last_2 = 0;
    while (1) {
        int el = -1;
        for (int i = last_1; i < (int)all_photos.size(); i += 1) {
            if (viz[i] == false and neighbours[i].size() == 1) {
                el = i;
                break;
            }

            last_1 += 1;
        }

        for (int i = last_2; el == -1 and i < (int)all_photos.size(); i += 1) {
            if (viz[i] == false) {
                el = i;
                break;
            }

            last_2 += 1;
        }

        if (el == -1) {
            break;
        }

        auto Add = [&](int el) {
            assert(viz[el] == false);
            num_viz += 1;
            viz[el] = true;
            final_order.push_back(all_photos[el]);
        };

        Add(el);

        while (1) {
            int next = -1;

            for (auto& itr : neighbours[el]) {
                if (viz[itr] == false) {
                    next = itr;
                }
            }

            if (next == -1) {
                break;
            }

            Add(next);
            el = next;
        }
    }

    return final_order;
}
