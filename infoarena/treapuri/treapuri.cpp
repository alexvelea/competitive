#include <fstream>
#include <iostream>
using namespace std;

ifstream in("schi.in");
ofstream out("schi.out");

struct TreapNode {
	int key, priority;
	TreapNode *left, *right;
	int under;
//	TreapNode(int _key, int _priority, int _ind);
	TreapNode(int, int);
	TreapNode() {
    	key = priority = under = 0;
		left = right = NULL;
	}
} *treap_nil, *root;

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
	if (nod->left->priority > nod->priority and nod->left->priority > nod->right->priority)
		left_up(nod);
	else
		if (nod->right->priority > nod->priority)
			right_up(nod);
}

void treap_add(TreapNode* &nod, int key, int priority, int _under) {	
	if (nod == treap_nil) {
		nod = new TreapNode(key, priority);
	} else {
		if (nod->left->under + 1 > _under)
			treap_add(nod->left, key, priority, _under);
		else
			treap_add(nod->right, key, priority, _under - nod->left->under - 1);
	}                
    nod->under++;
	balance(nod);
}

void DEBUG(TreapNode* &nod, int ind) {
	if (nod == treap_nil)
		return ;
	DEBUG(nod->left, ind + 1);
//	for (int i = 0; i < ind; ++i)
//		cerr << "#";
//	cerr << nod->key << '\t' << nod->under << '\n';;
	out << nod->key << '\n';
	DEBUG(nod->right, ind + 1);
}

int main() {
    treap_nil = new TreapNode();
	root = treap_nil;

	int n;
	in >> n;
	for (int i = 1; i <= n; ++i) {
		int el;
		in >> el;
		--el;
 		treap_add(root, i, rand() + 1, el);
//		DEBUG(root, 0);
//		cerr << "\n\n";
	}
	DEBUG(root, 0);
	return 0;
}
