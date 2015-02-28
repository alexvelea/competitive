#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

#define FORIT(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

class LotteryTree {
public:

	int under[105];
	vector<int> vertex[105];
	double rez[105], chx[105];
	bool n_leafe[105];

	void df(int nod) {
		for (int i = 0; i < int(vertex[nod].size()); ++i) {
			n_leafe[i] = true;
        	df(vertex[nod][i]);
			under[i] += 1 + under[vertex[nod][i]];
			father[vertex[nod][i]] = nod;
		}
	}
 	
    void solve(int beg, int nod) {
		rez[beg] += 1.0 * under[nod] / rez[beg];
		if (nod == 0)
			return ;
		solve(beg, father[nod]);
		return ;
	}

    string isFairTree( vector <int> tree, int P )  {
		int n = tree.size() + 1;
		for (int i = 0; i < tree.size(); ++i) {
			vertex[tree[i]].push_back(i + 1);
		}
		df(0);
		for (int i = 1; i <= n; ++i) {
	    	if (n_leafe[i] == false)
				solve(i, father[i]);
		}
    }
};

// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
	using std::string;
	using std::vector;
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
			}
			return;
		}
		
		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}
		
		if (total == 0) {
			std::cerr << "No test cases run." << std::endl;
		} else if (correct < total) {
			std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << std::endl;
		} else {
			std::cerr << "All " << total << " tests passed!" << std::endl;
		}
	}
	
	int verify_case(int casenum, const string &expected, const string &received, std::clock_t elapsed) { 
		std::cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		std::cerr << verdict;
		if (!info.empty()) {
			std::cerr << " (";
			for (size_t i=0; i<info.size(); ++i) {
				if (i > 0) std::cerr << ", ";
				std::cerr << info[i];
			}
			std::cerr << ")";
		}
		std::cerr << std::endl;
		
		if (verdict == "FAILED") {
			std::cerr << "    Expected: \"" << expected << "\"" << std::endl; 
			std::cerr << "    Received: \"" << received << "\"" << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int tree[]                = {0, 0, 0};
			int P                     = 3;
			string expected__         = "YES";

			std::clock_t start__      = std::clock();
			string received__         = LotteryTree().isFairTree(vector <int>(tree, tree + (sizeof tree / sizeof tree[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int tree[]                = {0, 0, 0, 1, 1, 2, 2, 3, 3};
			int P                     = 2;
			string expected__         = "YES";

			std::clock_t start__      = std::clock();
			string received__         = LotteryTree().isFairTree(vector <int>(tree, tree + (sizeof tree / sizeof tree[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int tree[]                = {0, 0, 1, 1, 2, 2, 4, 4, 4};
			int P                     = 3;
			string expected__         = "NO";

			std::clock_t start__      = std::clock();
			string received__         = LotteryTree().isFairTree(vector <int>(tree, tree + (sizeof tree / sizeof tree[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int tree[]                = {0, 0, 1, 1, 1, 3, 3, 3};
			int P                     = 3;
			string expected__         = "NO";

			std::clock_t start__      = std::clock();
			string received__         = LotteryTree().isFairTree(vector <int>(tree, tree + (sizeof tree / sizeof tree[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int tree[]                = {0, 0, 0, 3, 0, 0, 3, 6, 3, 1, 0, 2, 0, 4, 6, 15, 1, 15, 11, 11, 1, 4, 11, 2, 11, 2, 6} ;
			int P                     = 6;
			string expected__         = "YES";

			std::clock_t start__      = std::clock();
			string received__         = LotteryTree().isFairTree(vector <int>(tree, tree + (sizeof tree / sizeof tree[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int tree[]                = {0, 1, 2, 3, 1, 1, 4, 4, 0, 1, 6, 9, 1, 12, 9, 2, 4, 8, 6, 13, 8, 5, 11, 12, 17, 19, 13, 9, 3, 24, 30, 29, 28, 28, 11, 27, 2, 26, 6, 14, 8, 26, 15, 25, 33, 38, 1, 24, 15, 43, 3, 39, 26, 8, 13, 50, 28, 8, 6, 27, 8, 38, 27, 50, 17, 50, 25, 40, 7, 29, 22, 40, 2, 24, 22, 30, 33, 40, 19, 14, 26, 39, 5, 43, 7, 4};
			int P                     = 9;
			string expected__         = "NO";

			std::clock_t start__      = std::clock();
			string received__         = LotteryTree().isFairTree(vector <int>(tree, tree + (sizeof tree / sizeof tree[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int tree[]                = {0, 1, 0, 0, 4, 0, 2, 2, 0, 2, 6, 1, 3, 6, 5, 9, 11, 13, 1, 10, 14, 4, 7, 21, 16, 8, 25, 4, 5, 22, 25, 14, 12, 11, 12, 26, 21, 8, 2, 38, 3, 5, 4, 38, 27, 35, 38, 30, 38, 9, 16, 36, 6, 10, 7, 27, 30, 33, 17, 26, 17, 10, 35, 10, 38, 41, 15, 9, 3, 27, 8, 15, 38, 22, 41, 33, 33, 36, 30, 13, 18, 22, 18};
			int P                     = 12;
			string expected__         = "YES";

			std::clock_t start__      = std::clock();
			string received__         = LotteryTree().isFairTree(vector <int>(tree, tree + (sizeof tree / sizeof tree[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 7: {
			int tree[]                = {0, 0, 2, 3, 4, 3, 2, 1, 8, 6, 8, 8, 2, 7, 14, 2, 8, 1, 11, 11, 12, 16, 12, 19, 20, 13, 7, 12, 26, 11, 18, 19, 18, 20, 4, 9, 1, 1, 6, 16, 1, 35, 27, 24, 37, 30, 36, 41, 32, 36, 8, 2, 6, 14, 41, 1, 35, 6, 30, 16, 12, 2, 35, 25, 50, 13, 1, 24, 8, 32, 26, 50, 9, 19, 9, 20, 26, 27, 6, 12, 25, 9, 37, 37, 9} ;
			int P                     = 7;
			string expected__         = "NO";

			std::clock_t start__      = std::clock();
			string received__         = LotteryTree().isFairTree(vector <int>(tree, tree + (sizeof tree / sizeof tree[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 8: {
			int tree[]                = {0, 0, 1, 0, 2, 3, 0, 0, 8, 5, 7, 5, 2, 12, 12, 14, 14, 13, 8, 2, 1, 7, 18, 16, 8, 24, 18, 2, 24, 3, 11, 5, 24, 4, 34, 6, 31, 13, 38, 19, 4, 3, 22, 3, 11, 12, 21, 34, 41, 8, 19, 4, 13, 29, 33, 8, 14, 50, 18, 45, 16, 50, 44, 50, 38, 5, 43, 31, 29, 7, 6, 45, 38, 4, 19, 41, 50, 21, 44, 41, 43, 22, 33, 6, 8} ;
			int P                     = 12;
			string expected__         = "YES";

			std::clock_t start__      = std::clock();
			string received__         = LotteryTree().isFairTree(vector <int>(tree, tree + (sizeof tree / sizeof tree[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 9: {
			int tree[]                = ;
			int P                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = LotteryTree().isFairTree(vector <int>(tree, tree + (sizeof tree / sizeof tree[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 10: {
			int tree[]                = ;
			int P                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = LotteryTree().isFairTree(vector <int>(tree, tree + (sizeof tree / sizeof tree[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 11: {
			int tree[]                = ;
			int P                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = LotteryTree().isFairTree(vector <int>(tree, tree + (sizeof tree / sizeof tree[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


int main(int argc, char *argv[]) {
  if (argc == 1) {
    for (int test = 0; test < 10; ++test) {
      string command = string(argv[0]) + " ";
      command.push_back('0' + test);
      if (system(command.c_str()))
        cerr << "TEST FAILED!" << endl;
    }
  } else {
    moj_harness::run_test(atoi(argv[1]));
  }
  return 0;
}
// END CUT HERE
