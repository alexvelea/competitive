#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <map>

#include <ctime>
#include <cstdlib>
using namespace std;

#define int64 long long

ifstream fin("algsort.in");
ofstream fout("algsort.out");

const int kMaxN = 5e5 + 5;
const int64 inf = 1LL * 0x3f3f3f3f * 0x3f3f3f3f;

int64 heap[kMaxN];

void push_heap(int nod) {
	if (nod != 1 and heap[nod / 2] > heap[nod]) {
		swap(heap[nod / 2], heap[nod]);
		push_heap(nod / 2);
	}
}

void pop_heap(int nod) {
	if (2 * nod + 1 >= kMaxN) {
		heap[nod] = +inf;
		return ;
	}
	if (heap[2 * nod] < heap[2 * nod + 1]) {
		heap[nod] = heap[2 * nod];
		pop_heap(2 * nod);
	} else {
		heap[nod] = heap[2 * nod + 1];
		pop_heap(2 * nod + 1);
	}
}

int main() {
	int n; fin >> n;
	for (int i = 0; i < kMaxN; i += 1) {
		heap[i] = +inf;
	}
	for (int i = 1; i <= n; i += 1) {
		int64 x; fin >> x;
		heap[i] = x;
		push_heap(i);
	}

	for (int i = 1; i <= n; i += 1) {
		fout << heap[1] << ' ';
		pop_heap(1);
	}
	return 0;
}