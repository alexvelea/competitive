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

class TheQuestionsAndAnswersDivTwo {
public:
    int find( vector <string> questions )  {
		int rez=0,i,j,ok;
		for( i=0; i<questions.size(); ++i ){
			ok=1;
			for( j=0; j<i; ++j )
				if( questions[i]==questions[j] )
					ok=0;
			rez+=ok;
		}
		return (1<<rez);
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
			string questions[]        = {"How_are_you_doing?", "How_do_you_like_our_country?", "How_are_you_doing?"};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = TheQuestionsAndAnswersDivTwo().find(vector <string>(questions, questions + (sizeof questions / sizeof questions[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string questions[]        = {"Whazzup?"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = TheQuestionsAndAnswersDivTwo().find(vector <string>(questions, questions + (sizeof questions / sizeof questions[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string questions[]        = {"Are_you_ready?", "Are_you_ready?", "Are_you_ready?", "Are_you_ready?"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = TheQuestionsAndAnswersDivTwo().find(vector <string>(questions, questions + (sizeof questions / sizeof questions[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string questions[]        = {"Do_you_like_my_story?", "Do_you_like_my_story", "DO_YOU_LIKE_MY_STORY?", "Do__you__like__my__story?"};
			int expected__            = 16;

			clock_t start__           = clock();
			int received__            = TheQuestionsAndAnswersDivTwo().find(vector <string>(questions, questions + (sizeof questions / sizeof questions[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string questions[]        = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheQuestionsAndAnswersDivTwo().find(vector <string>(questions, questions + (sizeof questions / sizeof questions[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string questions[]        = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheQuestionsAndAnswersDivTwo().find(vector <string>(questions, questions + (sizeof questions / sizeof questions[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string questions[]        = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheQuestionsAndAnswersDivTwo().find(vector <string>(questions, questions + (sizeof questions / sizeof questions[0])));
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
