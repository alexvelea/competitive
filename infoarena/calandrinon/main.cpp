#include <fstream>
#include <queue>
using namespace std;

const int sigma = 26;

ifstream fin("calandrinon.in");
ofstream fout("calandrinon.out");

queue<int> element_position[sigma];
int last_position[sigma];
bool visited[sigma];

int main() {
    int n; fin >> n;
    string txt; fin >> txt;

    for (int i = 0; i < sigma; i += 1) {
        last_position[i] = -1;
    }

    for (int i = 0; i < int(txt.size()); i += 1) {
        element_position[txt[i] - 'a'].push(i);
        last_position[txt[i] - 'a'] = i;
    }

    int remaining = sigma;
    for (int i = 0; i < sigma; i += 1) {
        if (last_position[i] == -1) {
            remaining -= 1;
            visited[i] = true;
        }
    }

    int start_position = -1;
    string result_string;

    for (; remaining; remaining -= 1) {
        for (int i = 0; i < sigma; i += 1) {
            while (element_position[i].size() and element_position[i].front() <= start_position) {
                element_position[i].pop();
            }
        }

        for (int target = 0; target < sigma; target += 1) {
            if (visited[target]) {
                continue;
            }
            int remaining_after = 0;
            for (int other = 0; other < sigma; other += 1) {
                if (visited[other]) {
                    continue;
                }

                if (last_position[other] >= element_position[target].front()) {
                    remaining_after += 1;
                }
            }

            if (remaining_after == remaining) {
                result_string += char('a' + target);
                visited[target] = true;
                start_position = element_position[target].front();
                break;
            }
        }
    }

    fout << result_string << '\n';
}

