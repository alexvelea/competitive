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

class FiveHundredEleven {
public:
 		bool max( bool a, bool b ){
			if( a == true || b == true )
				return true;
			return false;
		}
		string theWinner( vector<int> Cards ){		
			string Winner[2]={("Toastman"),("Fox Ciel")};
			int n = Cards.size(), sum=0;
			int i, t, inside;
			bool Rez[512][2], Viz[512];
			bool ok;
			FORIT( it, Cards ){
				sum |= *it;
			}
			if( sum != 511 )
                return Winner[(n&1)];
 			for( i=0; i<512; ++i ){
				Rez[i][0]=Rez[i][1]=Viz[i]=false;
			}
			for( i=0; i<512; ++i ){
				ok=true;
				inside=0;
				FORIT( it, Cards ){
					inside += ( (*it&i) == *it );
					if( ((*it|i) == 511) || ((*it|i) == i ) )
						;
					else
						ok=false;
				}
				if( ok ){
					Viz[i]=1;
					if( inside == 0 )
						;
					else if( inside&1 )
						Rez[i][0] = true;
					else
						Rez[i][1] = true;	
				}
			}
 			Rez[511][0] = Rez[511][1] = 1;
			for( i=510; i>=0; --i ){
				if( !Viz[i] )
					for( t=0; t<2; ++t ){
						ok = false;
						FORIT( it, Cards ){
							if( (*it|i) != i ){
								ok = max( ok, Rez[ i|(*it) ][ t^1 ] ^ 1 );
							}
						}
						Rez[i][t] = ok;
					}
			}
			return Winner[ Rez[0][0] ];
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
	
	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) { 
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
			cerr << "    Expected: \"" << expected << "\"" << endl; 
			cerr << "    Received: \"" << received << "\"" << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int cards[]               = {3, 5, 7, 9, 510};
			string expected__         = "Fox Ciel";

			clock_t start__           = clock();
			string received__         = FiveHundredEleven().theWinner(vector <int>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int cards[]               = {0, 0, 0, 0};
			string expected__         = "Toastman";

			clock_t start__           = clock();
			string received__         = FiveHundredEleven().theWinner(vector <int>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int cards[]               = {511};
			string expected__         = "Toastman";

			clock_t start__           = clock();
			string received__         = FiveHundredEleven().theWinner(vector <int>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int cards[]               = {5, 58, 192, 256};
			string expected__         = "Fox Ciel";

			clock_t start__           = clock();
			string received__         = FiveHundredEleven().theWinner(vector <int>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int cards[]               = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FiveHundredEleven().theWinner(vector <int>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int cards[]               = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FiveHundredEleven().theWinner(vector <int>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int cards[]               = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FiveHundredEleven().theWinner(vector <int>(cards, cards + (sizeof cards / sizeof cards[0])));
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
