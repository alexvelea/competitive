//Problem f @ 30-12-2015
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

const int kMod = 1e9 + 7;

#define int64 long long

int h, w;

unordered_map<char, int> char_dir_to_int = {
	{'U', 0},
	{'D', 1}, 
	{'L', 2},
	{'R', 3}
};

vector<int> dx = {-1, +1, 0, 0};
vector<int> dy = {0, 0, -1, +1};

struct Event{
	int where, cost, value;
	Event() {
		where = cost = value = 0;
	} 
};

int64 global_cost = 0;
int64 final_cost = 0;

struct BoundingBox{
	int howMuch[4];
	BoundingBox() {
		for (int i = 0; i < 4; i += 1) {
			howMuch[i] = 0;
		}
	}

	void apply(Event ev) {
		if (not (howMuch[0] + howMuch[1] + 1 <= h and howMuch[2] + howMuch[3] + 1 <= w)) {
			cout << final_cost << '\n';
			exit(0);
		}

		global_cost += ev.cost;
		global_cost %= kMod;

		if (ev.value == 1) {
			if (ev.where == 0 or ev.where == 1) {
				final_cost = final_cost + 1LL * global_cost * max(0, (w - howMuch[2] - howMuch[3]));
				final_cost %= kMod;
			} else {
				final_cost = final_cost + 1LL * global_cost * max(0, (h - howMuch[0] - howMuch[1]));
				final_cost %= kMod;
			}
			howMuch[ev.where] += 1;
		}
		// cerr << global_cost << '\t';
		// for (int i = 0; i < 4; i += 1) {
			// cerr << howMuch[i] << '\t';
		// }
		// cerr << '\n';
	}

	int expand(pair<int, int> point) {
		if (not (-howMuch[0] <= point.first)) {
			return 0;
		}
		if (not (point.first <= howMuch[1])) {
			return 1;
		}
		if (not (-howMuch[2] <= point.second)) {
			return 2;
		}
		if (not (point.second <= howMuch[3])) {
			return 3;
		}
		return -1;
	}
} finalBounding;

int main() {
	ios::sync_with_stdio(false);
	int n; cin >> n >> h >> w;
	vector<int> dir(n, 0);
	for (int i = 0; i < n; i += 1) {
		char c; cin >> c;
		dir[i] = (char_dir_to_int[c]);
	}
	
	pair<int, int> start_point{0, 0};

	for (int i = 0; i < n; i += 1) {
		start_point.first += dx[dir[i]];
		start_point.second += dy[dir[i]];

		int should_expand = finalBounding.expand(start_point);
		Event ev;

		ev.value = (should_expand != -1);
		ev.where = should_expand;
		ev.cost = 1;

		finalBounding.apply(ev);
	}

	int current_cost = 0, last_cost = 0;

	vector<Event> nextEvents;
	for (int i = 0; i < n; i += 1) {
		current_cost += 1;
		start_point.first += dx[dir[i]];
		start_point.second += dy[dir[i]];
		int should_expand = finalBounding.expand(start_point);

		if (should_expand != -1) {
			Event ev;
			ev.value = 1;
			ev.cost = current_cost - last_cost;
			ev.where = should_expand;

			last_cost = current_cost;
			finalBounding.apply(ev);
			nextEvents.push_back(ev);
		}
	}

	if (start_point == make_pair(0, 0)) {
		cout << -1 << '\n';
		return 0;
	}

	if (last_cost != current_cost) {
			Event ev;
			ev.value = 0;
			ev.cost = current_cost - last_cost;
			ev.where = -1;

			last_cost = current_cost;
			finalBounding.apply(ev);
			nextEvents.push_back(ev);
	}

	int current_itr = 0;

	while (1) {
		finalBounding.apply(nextEvents[current_itr]);
		current_itr += 1;
		if (current_itr == int(nextEvents.size())) {
			current_itr = 0;
		}
	}

	return 0;
}
