#include <ctime>
#include <cstdlib>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define int64 long long

ifstream in("rotatii.in");
ofstream out("rotatii.out");

const int inf = 0x3f3f3f3f;

struct TreapNode {
 	int key, priority;
	TreapNode *left, *right;
	int under, sum, min;

	TreapNode() {
		key = priority = 0;
		left = right = NULL;
		under = sum = 0;
		min = inf;
	}
	TreapNode(int, int);
} *root, *treap_nil;

TreapNode :: TreapNode(int _key, int _priority) {
	min = sum = 0;
	key = _key;
	priority = _priority;
	left = right = treap_nil;
	under = 0;
}

void DEBUG(TreapNode* &nod, int ind) {
	if (nod == treap_nil)
		return;
	DEBUG(nod->left, ind + 1);
	for (int i = 1; i <= ind; ++i)
		cerr << "#";
	cerr << nod->key << '\t' << nod->sum << '\t' << nod->under << '\n';
	DEBUG(nod->right, ind + 1);
}
 

void get_min(TreapNode* &nod) {
	if (nod == treap_nil)
		return ;
	nod->min = min(nod->key + nod->left->sum, nod->left->min);
	nod->min = min(nod->min, nod->right->min + nod->key + nod->left->sum);
}        

void left_up(TreapNode* &nod) {
	TreapNode *l = nod->left;
	nod->left = l->right;
	l->right = nod;
	l->sum = nod->sum;
	nod->sum -= l->key + l->left->sum;
	l->under = nod->under;
	nod->under -= 1 + l->left->under;
	nod = l;

	get_min(nod->left);
	get_min(nod->right);
	get_min(nod);
}

void right_up(TreapNode* &nod) {
	TreapNode *r = nod->right;
	nod->right = r->left;
	r->left = nod;
	r->sum = nod->sum;
	nod->sum -= r->key + r->right->sum;
	r->under = nod->under;
	nod->under -= 1 + r->right->under;
	nod = r;

	get_min(nod->left);
	get_min(nod->right);
	get_min(nod);
}

void balance(TreapNode* &nod) {
	if (nod->priority < nod->left->priority and nod->left->priority > nod->right->priority)
		left_up(nod);
	else
		if (nod->priority < nod->right->priority)
			right_up(nod);
}



void treap_insert(TreapNode* &nod, int key, int priority, int under) {
	if (nod == treap_nil) {
		nod = new TreapNode(key, priority);
	} else {
		if (nod->left->under >= under)
			treap_insert(nod->left, key, priority, under);
		else
			treap_insert(nod->right, key, priority, under - 1 - nod->left->under);
	}
	nod->under++;
	nod->sum += key;
	balance(nod);
	get_min(nod);
}

void treap_delete(TreapNode* &nod, int under) {
	if (nod->left->under + 1 > under) {
		treap_delete(nod->left, under);
	} else if (nod->left->under + 1 < under) {
		treap_delete(nod->right, under - 1 - nod->left->under);
	} else if (nod->left->under + 1 == under) {
		if (nod->left == treap_nil and nod->right == treap_nil) {
			delete nod;
			nod = treap_nil;
			return ;
		} else {
			if (nod->left->priority > nod->right->priority) {
				left_up(nod);
				treap_delete(nod->right, under - 1 - nod->left->under);
			} else {
				right_up(nod);
				treap_delete(nod->left, under);
			}
		}
	}
	if (nod == treap_nil)
 		return ;
	nod->sum = nod->left->sum + nod->right->sum + nod->key;
	nod->under--;
	get_min(nod);
}

int treap_query(TreapNode* &nod) {
 	int a = nod->left->min;
	int b = nod->right->min + nod->key + nod->left->sum;
	int c = nod->key + nod->left->sum;
	int m = min(min(a, b), c);
	if (c == m)
		return 1 + nod->left->under;
	if (a == m)
		return treap_query(nod->left);
	return treap_query(nod->right) + 1 + nod->left->under;
}


int main() {
	srand(time(NULL));
 	treap_nil = new TreapNode();
	root = treap_nil;
	int n, m;
	in >> n >> m;
	for (int i = 1; i <= n; ++i) {
    	int el;
		in >> el;
		treap_insert(root, el, rand() + 1, i - 1);
	}
	int inside = n;
 	while (m--) {
//		DEBUG(root, 0);
//		cerr << "\n\n";
		int t;
		in >> t;
		if (t == 0) {
			int x, y;
			in >> x >> y;
			treap_insert(root, y, rand() + 1, x);
			inside++;
		}
		if (t == 1) {
			int x;
			in >> x;
			treap_delete(root, x);
			inside--;
		}
		if (t == 2) {
//			DEBUG(root, 0);
//	  		cerr << "\n\n";
 			if (root->sum < 0) {
				out << "-1\n";
				continue;
			}
			int rez = treap_query(root);
			out << rez << '\n';
		}
	}
    return 0;
}
