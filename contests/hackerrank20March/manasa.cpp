#include <iostream>
using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
		string txt;
    	cin >> txt;
		bool ok = false;

		if (txt.size() == 1) {
			if (txt == "8" or txt == "0")
				ok = true;
		}

		if (txt.size() == 2) {
			int sum;

			sum = (txt[0] - '0') * 10 + (txt[1] - '0');
			if (sum % 8 == 0)
				ok = true;

			swap(txt[0], txt[1]);

 			sum = (txt[0] - '0') * 10 + (txt[1] - '0');
			if (sum % 8 == 0)
				ok = true;   		
		}

		if (txt.size() > 2) {
			for (int i = 0; i < int(txt.size()); ++i)
				for (int j = 0; j < int(txt.size()); ++j)
					for (int l = 0; l < int(txt.size()); ++l) {
						if (i == j or j == l or l == i)
							continue;
						int sum = 100 * (txt[i] - '0') +
							10 * (txt[j] - '0') +
							(txt[l] - '0');
						if (sum % 8 == 0)
							ok = true;
					}
		}

		cout << ((ok) ? ("YES") : ("NO")) << '\n';
	}
}
