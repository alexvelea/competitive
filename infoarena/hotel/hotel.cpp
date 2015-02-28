#include <iostream>
#include <fstream>
using namespace std;

ifstream in ("hotel.in");
ofstream out ("hotel.out");

const int max_n = 133000;

struct aib_node {
	int mid, right, left;
	aib_node () {
		mid = right = left = 0;
	}
	aib_node (int x) {
		set (x);
	}
	void set (int x) {
		mid = right = left = x;
	}
} aib[2*max_n];

void get_max (int &a, int b) {
	if (a < b)
		a = b;
}

void split (int nod, int st, int dr) {
	int s = dr - st + 1;
 	if (st == dr)
		return ;
	if (aib[nod].mid == s || aib[nod].mid == 0)
		;
	else
		return;
	int multi = (aib[nod].mid>0);
	int mid = (dr + st) / 2;
	aib[2 * nod].set ((mid - st + 1) * multi);
	aib[2 * nod + 1].set ((dr - (mid + 1) + 1) * multi);
	return ;
}


void update (int nod, int st, int dr, int a, int b, int multi) {
	if (a <= st && dr <= b) {
		aib[nod].set(multi * (dr - st + 1));
		return ;
	}
	split (nod, st, dr);
	int mid = (st + dr) / 2;
 	if (a <= mid)
		update (2 * nod, st, mid, a, b, multi);
	if (mid < b)
		update (2 * nod + 1, mid + 1, dr, a, b, multi);
 	aib_node l = aib[2 * nod], r = aib[2 * nod + 1];
	aib[nod].mid = max (l.mid, r.mid);
	aib[nod].left = l.left;
	aib[nod].right = r.right;
	if (r.mid == dr - (mid + 1) + 1)
		aib[nod].right = l.right + dr - mid;
	if (l.mid == mid - st + 1)
		aib[nod].left = r.left + mid - st + 1;
	get_max (aib[nod].mid, aib[nod].left);
	get_max (aib[nod].mid, aib[nod].right);
	get_max (aib[nod].mid, l.right + r.left);
}

//void init (int nod, int st, int dr) {
//	aib[nod].set (dr-st+1);
//	if (st == dr)
//		return ;
//	int mid = (dr+st)/2;
//	init (2*nod, st, mid);
//	init (2*nod+1, mid+1, dr);
//}

int main() {
	int n, q;
	in >> n >> q;
//	init (1, 1, n);
	aib[1].set(n);
	while (q--) {
		int t;
		in >> t;
		if (t == 3) {
			out << aib[1].mid << "\n";
			continue;
		}
		int a, b, multi = 1;
		in >> a >> b;
		b += a-1;
		if (t == 1)
			multi = 0;
		update (1, 1, n, a, b, multi);
//		debug (1,1,n);
//		cerr << "\n\n";
	}
	return 0;
}
