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

class PalindromicSubstringsDiv1 {
public:
    double expectedPalindromes( vector <string> S1, vector <string> S2 )  {
		string rez;
		FORIT(it, S1)
			rez += *it;
		FORIT(it, S2)
			rez += *it;
		int n = int(rez.size());
		double exp = 0;
		for (int i = 0; i < n; ++i) {
			// center in i
			double chs = 1.0;
			for (int d = 0; i - d >= 0 and i + d < n; ++d) {
				if (rez[i - d] == rez[i + d]) {
					if (rez[i - d] == '?' and d != 0)
						chs /= 26.0;
				} else {
					if (rez[i - d] == '?' or rez[i + d] == '?')
						chs /= 26.0;
					else
						break;
				}
                exp += chs;
			}

			chs = 1.0;
 			for (int d = 0; i - d >= 0 and i + d + 1< n; ++d) {
				if (rez[i - d] == rez[i + d + 1]) {
					if (rez[i - d] == '?')
						chs /= 26.0;
				} else { 
					if (rez[i - d] == '?' or rez[i + d + 1] == '?')
						chs /= 26.0;
					else
						break;
				}
                exp += chs;
			}   		
		}
		return exp;
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
	
	static const double MAX_DOUBLE_ERROR = 1e-9; static bool topcoder_fequ(double expected, double result) { if (isnan(expected)) { return isnan(result); } else if (isinf(expected)) { if (expected > 0) { return result > 0 && isinf(result); } else { return result < 0 && isinf(result); } } else if (isnan(result) || isinf(result)) { return false; } else if (fabs(result - expected) < MAX_DOUBLE_ERROR) { return true; } else { double mmin = min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); double mmax = max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); return result > mmin && result < mmax; } }
	double moj_relative_error(double expected, double result) { if (isnan(expected) || isinf(expected) || isnan(result) || isinf(result) || expected == 0) return 0; return fabs(result-expected) / fabs(expected); }
	
	int verify_case(int casenum, const double &expected, const double &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (topcoder_fequ(expected, received)) {
			verdict = "PASSED";
			double rerr = moj_relative_error(expected, received); 
			if (rerr > 0) {
				sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			string S1[]               = {"a","a",""};
			string S2[]               = {"a"};
			double expected__         = 6.0;

			clock_t start__           = clock();
			double received__         = PalindromicSubstringsDiv1().expectedPalindromes(vector <string>(S1, S1 + (sizeof S1 / sizeof S1[0])), vector <string>(S2, S2 + (sizeof S2 / sizeof S2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string S1[]               = {"z??"};
			string S2[]               = {};
			double expected__         = 3.115384615384615;

			clock_t start__           = clock();
			double received__         = PalindromicSubstringsDiv1().expectedPalindromes(vector <string>(S1, S1 + (sizeof S1 / sizeof S1[0])), vector <string>(S2, S2 + (sizeof S2 / sizeof S2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string S1[]               = {"ab","c"};
			string S2[]               = {"??","a?"};
			double expected__         = 7.315088757396449;

			clock_t start__           = clock();
			double received__         = PalindromicSubstringsDiv1().expectedPalindromes(vector <string>(S1, S1 + (sizeof S1 / sizeof S1[0])), vector <string>(S2, S2 + (sizeof S2 / sizeof S2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string S1[]               = {};
			string S2[]               = {"?"};
			double expected__         = 1.0;

			clock_t start__           = clock();
			double received__         = PalindromicSubstringsDiv1().expectedPalindromes(vector <string>(S1, S1 + (sizeof S1 / sizeof S1[0])), vector <string>(S2, S2 + (sizeof S2 / sizeof S2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string S1[]               = {"ab?def","?"};
			string S2[]               = {"f??a"};
			double expected__         = 12.545971779699588;

			clock_t start__           = clock();
			double received__         = PalindromicSubstringsDiv1().expectedPalindromes(vector <string>(S1, S1 + (sizeof S1 / sizeof S1[0])), vector <string>(S2, S2 + (sizeof S2 / sizeof S2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string S1[]               = ;
			string S2[]               = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = PalindromicSubstringsDiv1().expectedPalindromes(vector <string>(S1, S1 + (sizeof S1 / sizeof S1[0])), vector <string>(S2, S2 + (sizeof S2 / sizeof S2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string S1[]               = ;
			string S2[]               = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = PalindromicSubstringsDiv1().expectedPalindromes(vector <string>(S1, S1 + (sizeof S1 / sizeof S1[0])), vector <string>(S2, S2 + (sizeof S2 / sizeof S2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string S1[]               = ;
			string S2[]               = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = PalindromicSubstringsDiv1().expectedPalindromes(vector <string>(S1, S1 + (sizeof S1 / sizeof S1[0])), vector <string>(S2, S2 + (sizeof S2 / sizeof S2[0])));
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
