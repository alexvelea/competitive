// 6:25
#include <fstream>
#include <iostream>
using namespace std;

ifstream in("schi.in");
ofstream out("schi.out");

struct TreapNode{
	int key, priority;
	int under;
	TreapNode *left, *right;
	TreapNode() {
		left = right = NULL;
		key = priority = under = 0;
	}
	TreapNode(int, int);
} *root, *treap_nil;

TreapNode :: TreapNode(int _key, int _priority) {
	key = _key;
	priority = _priority;
	under = 0;

	left = right = treap_nil;
}

void left_up(TreapNode* &nod) {
	TreapNode *l = nod->left;
	nod->left = l->right;
	l->right = nod;
	l->under = nod->under;
	nod->under -= 1 + l->left->under;
	nod = l;
}

void right_up(TreapNode* &nod) {
	TreapNode *r = nod->right;
	nod->right = r->left;
	r->left = nod;
	r->under = nod->under;
	nod->under -= 1 + r->right->under;
	nod = r;
}

void balance(TreapNode* &nod) {
	if (nod->priority < nod->left->priority and nod->left->priority > nod->right->priority)
		left_up(nod);
	else
		if (nod->priority < nod->right->priority)
			right_up(nod);
}

void treap_add(TreapNode* &nod, int key, int priority, int under) {
	if (nod == treap_nil) {
    	nod = new TreapNode(key, priority);
	} else {
		if (under <= nod->left->under)
			treap_add(nod->left, key, priority, under);
		else
			treap_add(nod->right, key, priority, under - 1 - nod->left->under);
	}
	nod->under++;
	balance(nod);
}

void DEBUG(TreapNode* &nod) {
	if (nod == treap_nil)
		return;
	DEBUG(nod->left);
	out << nod->key << '\n';
	DEBUG(nod->right);
}

int main() {
	treap_nil = new TreapNode();
	root = treap_nil;

	int n;
	in >> n;
	for (int i = 1; i <= n; ++i) {
		int el;
		in >> el;
		treap_add(root, i, rand() + 1, el - 1);
	}
	DEBUG(root);
	return 0;
}
