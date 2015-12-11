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

#define FORIT(it, v) for (auto it = (v).begin(); it != (v).end(); ++it)

class CombinationLockDiv1 {
public:

	void get_min(int &a, int b) {
		if (a > b)
			a = b;
	}

    int minimumMoves( vector <string> P, vector <string> Q )  {
 		string A, B;   
		FORIT(it, P)
			A += *it;
		FORIT(it, Q)
			B += *it;

		int n = A.size();
		const int base = 50 * 55, inf = 0x3f3f3f3f;

		int moves[22 * base];
 		#define moves (moves + 10 * base)
		int up = 0, down = 0;
		for (int i = -10 * base; i <= 10 * base; ++i)
			moves[i] = inf;
		moves[0] = 0;
		for (int t = 0; t < n; ++t) {
			down -= 10;
			up += 10;
			for (int i = down; i < 0; ++i)
				get_min(moves[i + 1], moves[i]);
 			for (int i = up; i > 0; --i)
				get_min(moves[i - 1], moves[i]);   			
			for (int i = 0; i >= down; --i)
				get_min(moves[i], moves[i + 1] + 1);
			for (int i = 0; i <= up; ++i)
				get_min(moves[i], moves[i - 1] + 1);

			for (int i = down; i <= up; ++i) {
				if (((i + 1000000 + A[t] - '0') % 10) != (B[t] - '0'))
					moves[i] = inf;
			}
		}
		int mn = inf;
		for (int i = down; i <= up; ++i)
			get_min(mn, moves[i]);
		return mn;
    }
};

// BEGIN CUT HERE
namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
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
			cerr << "No test cases run." << endl;
		} else if (correct < total) {
			cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
		} else {
			cerr << "All " << total << " tests passed!" << endl;
		}
	}
	
	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		cerr << verdict;
		if (!info.empty()) {
			cerr << " (";
			for (int i=0; i<(int)info.size(); ++i) {
				if (i > 0) cerr << ", ";
				cerr << info[i];
			}
			cerr << ")";
		}
		cerr << endl;
		
		if (verdict == "FAILED") {
			cerr << "    Expected: " << expected << endl; 
			cerr << "    Received: " << received << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string P[]                = {"123"};
			string Q[]                = {"112"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string P[]                = {"1"};
			string Q[]                = {"7"};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string P[]                = {"6","07"};
			string Q[]                = {"","60","7"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string P[]                = {"1234"};
			string Q[]                = {"4567"};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string P[]                = {"020"};
			string Q[]                = {"909"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string P[]                = {"4423232218340"};
			string Q[]                = {"6290421476245"};
			int expected__            = 18;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string P[]                = ;
			string Q[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string P[]                = ;
			string Q[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string P[]                = ;
			string Q[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
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
