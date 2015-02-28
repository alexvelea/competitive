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

class SquaredSubsets {
public:
	vector<long long> Rez;
	long long countSubsets( int n, vector <int> X, vector <int> Y )  {
    	int l=n, i;
		n=X.size();
		vector<int> TX, TY;

		TX.clear();
		TY.clear();
		for( i=0; i<n; ++i )
			X[i]*=2;
		for( i=0; i<n; ++i )
			Y[i]*=2;
		l*=2;
		FORIT( it, X ){
			TX.push_back( *it );
			TX.push_back( *it-l-1 );
		}
		FORIT( it,Y ){
			TY.push_back( *it );
			TY.push_back( *it-l-1 );
		}
		sort( TX.begin(), TX.end() );
		sort( TY.begin(), TY.end() );
		TX.resize( unique( TX.begin(), TX.end() ) - TX.begin() );
		TY.resize( unique( TY.begin(), TY.end() ) - TY.begin() );
		for( int c1=0; c1<TX.size(); c1++ )
			for( int c2=0; c2<TY.size(); ++c2 ){
				int x=TX[c1];
				int y=TY[c2];
				long long H=0;
				for( i=0; i<n; ++i ){
					if( (X[i] >= x) && (X[i] <= x+l) && (Y[i] >= y) && (Y[i] <= y+l) ){
						H |= 1LL<<i;
					}
				}
				if( H ) 
					Rez.push_back( H );
			}
		sort( Rez.begin(), Rez.end() );
		Rez.resize( unique( Rez.begin(), Rez.end() ) - Rez.begin() );
		return Rez.size();
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
	
	int verify_case(int casenum, const long long &expected, const long long &received, clock_t elapsed) { 
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
			int n                     = 5;
			int x[]                   = {-5,0,5};
			int y[]                   = {0,0,0};
			long long expected__      = 5;

			clock_t start__           = clock();
			long long received__      = SquaredSubsets().countSubsets(n, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 10;
			int x[]                   = {-5,0,5};
			int y[]                   = {0,0,0};
			long long expected__      = 5;

			clock_t start__           = clock();
			long long received__      = SquaredSubsets().countSubsets(n, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 100000000;
			int x[]                   = {-1,-1,-1,0,1,1,1};
			int y[]                   = {-1,0,1,1,-1,0,1};
			long long expected__      = 21;

			clock_t start__           = clock();
			long long received__      = SquaredSubsets().countSubsets(n, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 5;
			int x[]                   = {5,3,6,2,1,6,4,4,7,-1,-4,-7,2,-2,0};
			int y[]                   = {0,-1,8,-5,2,5,-8,8,-6,4,3,2,7,3,5};
			long long expected__      = 66;

			clock_t start__           = clock();
			long long received__      = SquaredSubsets().countSubsets(n, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 1;
			int x[]                   = {-1,0};
			int y[]                   = {0,0};
			long long expected__      = 3;

			clock_t start__           = clock();
			long long received__      = SquaredSubsets().countSubsets(n, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			int n                     = 100000000;
			int x[]                   = {-100000000, -99000000, -98000000, -97000000, -96000000, -95000000, -94000000, -93000000, -92000000, -91000000, -90000000, -89000000, -88000000, -87000000, -86000000, -85000000, -84000000, -83000000, -82000000, -81000000, -80000000, -79000000, -78000000, -77000000, -76000000, -75000000, -74000000, -73000000, -72000000, -71000000, -70000000, -69000000, -68000000, -67000000, -66000000, -65000000, -64000000, -63000000, -62000000, -61000000, -60000000, -59000000, -58000000, -57000000, -56000000, -55000000, -54000000, -53000000, -52000000, -51000000};
			int y[]                   = {-100000000, -99000000, -98000000, -97000000, -96000000, -95000000, -94000000, -93000000, -92000000, -91000000, -90000000, -89000000, -88000000, -87000000, -86000000, -85000000, -84000000, -83000000, -82000000, -81000000, -80000000, -79000000, -78000000, -77000000, -76000000, -75000000, -74000000, -73000000, -72000000, -71000000, -70000000, -69000000, -68000000, -67000000, -66000000, -65000000, -64000000, -63000000, -62000000, -61000000, -60000000, -59000000, -58000000, -57000000, -56000000, -55000000, -54000000, -53000000, -52000000, -51000000};
			long long expected__      = 1275;

			clock_t start__           = clock();
			long long received__      = SquaredSubsets().countSubsets(n, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			int n                     = ;
			int x[]                   = ;
			int y[]                   = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = SquaredSubsets().countSubsets(n, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int n                     = ;
			int x[]                   = ;
			int y[]                   = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = SquaredSubsets().countSubsets(n, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
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
