#include <fstream>
#include <iostream>

using namespace std;

#define int64 long long

ifstream in("rotatii.in");
ofstream out("rotatii.out");

const int kMaxN = 100005, inf = 0x3f3f3f3f;

struct TreapNode {
	int64 sum, min;
	int under, key, priority;
	TreapNode *left, *right;

	TreapNode() {
		left = right = NULL;
		under = key = priority = 0;
		sum = 0;
		min = 1LL * inf * inf;
	}
	TreapNode (int _key, int _priority) {
    	key = sum = min = _key;
		priority = _priority;
		under = 0;
		left = right = NULL;
	}
} *TreapNil = new TreapNode(), *root = TreapNil;

void make_min(TreapNode* &nod) {
	if (nod == TreapNil) {
		nod->min = inf;
		return ;
	}
	nod->min = min(nod->key + nod->left->sum, min(nod->left->min, nod->left->sum + nod->right->min));
}
 
void left_up(TreapNode* &nod) {
	TreapNode *l = nod;
	nod->left = l->right;
 	l->right = nod;
 
 	l->sum = nod->sum;
	l->under = nod->under;
	nod->sum -= l->key + l->left->sum;
	nod->under -= 1 + l->left->under;

	nod = l;
	make_min(nod->left);
	make_min(nod->right);
	make_min(nod);
}

void right_up(TreapNode* &nod) {
	TreapNode *r = nod;
	nod->right = r->left;
	r->left = nod;

	r->sum = nod->sum;
	r->under = nod->under;
	nod->sum -= r->key + r->right->sum;
	nod->under -= 1 + r->right->under;

	nod = r;
	make_min(nod->left);
	make_min(nod->right);
	make_min(nod);
}

void balance(TreapNode* &nod) {
	if (nod->priority < nod->left->priority and nod->left->priority > nod->right->priority)
		left_up(nod);
	else
		if (nod->priority < nod->right->priority)
			right_up(nod);
}


void treap_add(TreapNode* &nod, int _under, int key, int priority) {
	if (nod == TreapNil) {
		nod = new TreapNode(key, priority);
	} else {
		if (nod->left->under <= _under)
			treap_add(nod->left, _under, key, priority);
		else
			treap_add(nod->right, _under - 1 - nod->left->under, key, priority);
	}
	nod->under++;
	make_min(nod);
	balance(nod);
}

int main() {
	int n, m, inside;
	in >> n >> m;
	for (int i = 1; i <= n; ++i) {
		int e;
		in >> e;
		treap_add(root, i - 1, e, rand() + 1);
		++inside;
	}

	while (m--) {
		int t;
		in >> t;
		if (t == 0) {
			int poz, val;
			in >> poz >> val;
			assert(poz <= inside);
			treap_add(root, poz, val, rand() + 1);
			inside++;
		}
		if (t == 1) {
			int poz;
			in >> poz;
			assert(poz <= inside);
 			treap_delete(root, poz);
			inside--;
		}
		if (t == 2) {
		 	int poz;

			if (root->sum < 0) {
				out << "-1\n";
			}

			poz = treap_query(root);
			poz++;
			if (poz == inside + 1)
				poz = 1;
			out << poz << '\n';
		}
	}
}

