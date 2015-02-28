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

class ParkAmusement {
public:

	vector<int> Vertex[55],Back[55],Ord;
	int Nr[55], Viz[55];
	double Rez[55][55];

	void df( int nod ){
    	Viz[nod]=3;
		Ord.push_back(nod);
		FORIT( it, Back[nod] ){
			Nr[*it]++;
			if( Nr[*it]==Vertex[*it].size() && !Viz[*it] )
				df(*it);
		}
	}

    double getProbability( vector <string> landings, int startLanding, int K )  {
    	int n=landings.size(),i,j,k;
		double rez=0;
		for( i=0; i<n; ++i )
			for( k=0; k<=K; ++k )
				Rez[i][k]=0.0;
		for( i=0; i<n; ++i ){
			if( landings[i][i]!='0' ){
				if( landings[i][i]=='E' )
					Rez[i][0]=1.0;
				continue;
			}
			for( j=0; j<n; ++j ){
				if( landings[i][j]=='1' ){
					Vertex[i].push_back(j);
			    	Back[j].push_back(i);
				}
			}
		}
		for( i=0; i<55; ++i )
			Nr[i]=Viz[i]=0;     
		for( i=0; i<n; ++i )
			if( !Viz[i] && Nr[i]==Vertex[i].size() )
				df(i);
		int nod;
		for( i=0; i<n; ++i ){
			nod=Ord[i];
			FORIT( it, Vertex[nod] ){
				for( k=1; k<=K; ++k )
					Rez[nod][k]+=1.0/Vertex[nod].size()*Rez[*it][k-1];
			}
		}
		for( i=0; i<n; ++i ){
			rez+=Rez[i][K];
		}
		if( Rez[startLanding][K] != 0.0 )
			return Rez[startLanding][K]/rez;
		else
			return 0.0;
    }
};

// BEGIN CUT HERE
namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = 3, bool quiet = false) {
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
			string landings[]         = {"E000",
 "1000",
 "1000",
 "1000"};
			int startLanding          = 1;
			int K                     = 1;
			double expected__         = 0.3333333333333333;

			clock_t start__           = clock();
			double received__         = ParkAmusement().getProbability(vector <string>(landings, landings + (sizeof landings / sizeof landings[0])), startLanding, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string landings[]         = {"E000",
 "1000",
 "1001",
 "000P"};
			int startLanding          = 1;
			int K                     = 1;
			double expected__         = 0.6666666666666666;

			clock_t start__           = clock();
			double received__         = ParkAmusement().getProbability(vector <string>(landings, landings + (sizeof landings / sizeof landings[0])), startLanding, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string landings[]         = {"01000100",
 "00111000",
 "00001010",
 "000E0000",
 "0000E000",
 "00000P00",
 "000000P0",
 "01000000"};
			int startLanding          = 1;
			int K                     = 2;
			double expected__         = 0.14285714285714288;

			clock_t start__           = clock();
			double received__         = ParkAmusement().getProbability(vector <string>(landings, landings + (sizeof landings / sizeof landings[0])), startLanding, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string landings[]         = {"0100",
 "0010",
 "0001",
 "000E"};
			int startLanding          = 0;
			int K                     = 2;
			double expected__         = 0.0;

			clock_t start__           = clock();
			double received__         = ParkAmusement().getProbability(vector <string>(landings, landings + (sizeof landings / sizeof landings[0])), startLanding, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string landings[]         = {"E00",
 "0E0",
 "010"};
			int startLanding          = 0;
			int K                     = 1;
			double expected__         = 0.0;

			clock_t start__           = clock();
			double received__         = ParkAmusement().getProbability(vector <string>(landings, landings + (sizeof landings / sizeof landings[0])), startLanding, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string landings[]         = ;
			int startLanding          = ;
			int K                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = ParkAmusement().getProbability(vector <string>(landings, landings + (sizeof landings / sizeof landings[0])), startLanding, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string landings[]         = ;
			int startLanding          = ;
			int K                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = ParkAmusement().getProbability(vector <string>(landings, landings + (sizeof landings / sizeof landings[0])), startLanding, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string landings[]         = ;
			int startLanding          = ;
			int K                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = ParkAmusement().getProbability(vector <string>(landings, landings + (sizeof landings / sizeof landings[0])), startLanding, K);
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
