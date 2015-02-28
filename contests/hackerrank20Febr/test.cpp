#include <iostream>
#include <vector>
using namespace std;

struct t {
	t *next;
	t() {
		next = NULL;
	}
} *root;

vector<t*> v;

int main() {
	root = new(t);
	root->next = new(t);
	cerr << root << '\n';
	v.push_back(root);
 	cerr << v[0] << '\n';
	v.push_back(root->next);
	cerr << root->next << '\n';
	cerr << v[1] << '\n';
}
