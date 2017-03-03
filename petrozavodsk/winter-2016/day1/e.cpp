#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

enum EventType {
    kBomb,
    kLiftOff
};

struct Event {
    int type, time, pos, radius, result, id;

    bool operator<(const Event& rhs) const {
        if (time == rhs.time) {
            return type < rhs.type;
        }
        return time < rhs.time;
    }
};

int Time = 0;
int num_segments;

struct Segment {
    int left, right;
    int last_update, id, valid;

    Segment() = default;
    Segment(int left, int right, bool k=false) : left(left), right(right), last_update(Time), id(k ? ++num_segments : 0), valid(k) { }

    bool operator<(const Segment& rhs) const {
        return left - last_update < rhs.left - rhs.last_update;
    }

    int Left() const {
        return left -  Time + last_update;
    }

    int Right() const {
        return right + Time - last_update;
    }

    void Update() {
        left -= Time - last_update;
        right += Time - last_update;
    }

    vector<Segment> Split(Segment s, bool k=true) const {
        if (s.left <= Left() and Right() <= s.right) {
            return {};
        }

        vector<Segment> ss;
        if (Left() < s.left) {
            ss.push_back(Segment(Left(), min(s.left - 1, Right()), k));
        }

        if (Right() > s.right) {
            ss.push_back(Segment(max(Left(), s.right + 1), Right(), k));
        }

        return ss;
    }
};

vector<Segment> all_segments({Segment(0, 0)});

struct Merges {
    int time, id[2];
    bool operator<(const Merges& rhs) const {
        return time > rhs.time;
    }
};

void Solve(vector<Event>& events) {
    Time = 0;
    
    set<Segment> s;
    priority_queue<Merges> pq;

    auto Debug = [&]() {
        cout << "~~~~~\n";
        for (auto itr : s) {
            cout << "[" << itr.Left() << "\t" << itr.Right() << "\t" << itr.id << "]\n";
        }
        cout << '\n';
    };
 
    auto AddSeg = [&](Segment seg) {
        auto itr = s.insert(seg).first;
        if (itr != s.begin()) {
            auto prev = itr;
            prev--;
            pq.push({Time + (itr->Left() - prev->Right()) / 2, {prev->id, itr->id}});
        }

        auto next = itr;
        next++;
        if (next != s.end()) {
            pq.push({Time + (next->Left() - itr->Right()) / 2, {itr->id, next->id}});
        }
       
    };
    auto AddSegment = [&](int left, int right) {
        Segment seg = Segment(left, right, true);
        all_segments.push_back(seg);
        AddSeg(seg);
    };

    auto AddSegments = [&](const vector<Segment>& ss) {
        for (auto seg : ss) {
            all_segments.push_back(seg);
            AddSeg(seg);
        }
    };

    AddSegment(0, 0);

    auto EraseSeg = [&](int id) {
        auto itr = s.find(all_segments[id]);
        auto next = itr; next++;
        if (itr != s.begin() && next != s.end()) {
            auto prev = itr; prev--;
            pq.push({Time + (next->Left() - prev->Right()) / 2, {prev->id, next->id}});
        }
        all_segments[id].valid = false;
        s.erase(itr);
    };

    for (auto& now : events) {
        Debug();
        Time = now.time;

        if (!s.size()) {
            break;
        }

        // merge shits
        while (pq.size() and pq.top().time <= now.time) {
            // merge this shit
            Merges m = pq.top();
            pq.pop();
            int a = m.id[0];      
            int b = m.id[1];      
            if ((not all_segments[a].valid) or 
                (not all_segments[b].valid)) {
                continue;
            }

            EraseSeg(a);
            EraseSeg(b);
            
            all_segments[a].Update();
            all_segments[b].Update();
            
            int left = all_segments[a].left;
            int right = all_segments[b].right;

            AddSegment(left, right);
        }

        if (now.type == kLiftOff) {
            int x = now.pos;
            now.result = false;
            
            if ((x & 1) != (Time & 1)) {
            } else {
                Segment seg(x, 0);
                auto itr = s.upper_bound(seg);
                if (itr == s.begin()) {
                    continue;
                }
                itr--;
                auto& shit = *itr;
                if (shit.Left() <= x and x <= shit.Right()) {
                    now.result = true;
                }
            }

            continue;
        }


        while (s.size()) {
            int left = now.pos - now.radius;
            int right = now.pos + now.radius;
            Segment seg(left, 0);
            auto itr = s.upper_bound(seg);
            if (itr == s.begin()) {
            } else {
                itr--;
                if (itr->Right() >= left) {
                } else {
                    itr++;
                }
            }
            auto next = itr;
            next++;
            if (next != s.end()) {
                if (left <= next->Left() and next->Right() <= right) {
                    s.erase(next);
                    continue;
                }

                if (next->Left() > right) {
                } else if (left <= next->Left() and next->Right() > right){
                    auto pnext = Segment(*next);
                    auto now_splits = itr->Split(Segment(left, right));
                    auto next_splits = pnext.Split(Segment(left, right));
                    EraseSeg(itr->id);
                    EraseSeg(pnext.id);

                    AddSegments(now_splits);
                    AddSegments(next_splits);
                    break;
                }
            }

            // split this shit into max 2 shits
            auto now_splits = itr->Split(Segment(left, right));
            EraseSeg(itr->id);
            AddSegments(now_splits);
            break;
        }
    }
}

int main() {
    int t; cin >> t;
    while (t--) {
        vector<Event> events;

        int num_bombs; cin >> num_bombs;
        for (int i = 0; i < num_bombs; i += 1) {
            int t, x, r; cin >> t >> x >> r;
            r -= 1;
            events.push_back({kBomb, t, x, r, 0, i});
        }

        int q; cin >> q;
        for (int i = 0; i < q; i += 1) {
            int t, x; cin >> t >> x;
            events.push_back({kLiftOff, t, x, 0, 0, i});
        }

        sort(events.begin(), events.end());
        Solve(events);

        sort(events.begin(), events.end(), [&](const Event& a, const Event& b) { return a.id < b.id; });

        for (auto itr : events) {
            if (itr.type != kLiftOff) {
                continue;
            }

            if (itr.result) {
                cout << "@";
            } else {
                cout << "*";
            }
        }
        cout << '\n';
    }
}

