#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

typedef long long int64;

#define FORIT(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

class BigO {
public:

	vector<int> edge[55], edgeB[55];
	vector<int> edgeF[55], edgeFB[55];
	bool viz[55];
	int sol[55], nr_c, nr_sol[55], rez[55];

	void df(int nod) {
		viz[nod] = true;
		for (int itr : edge[nod])
			if (not viz[itr])
				df(itr);
	}

	void dfB(int nod) {
		nr_sol[nr_c]++;
		sol[nod] = nr_c;
		for (int itr : edgeB[nod])
			if (viz[itr] and not sol[itr])
				dfB(itr);
	}

	stack<int> st;

	void solve(int nod) {
		viz[nod] = true;
 		for (int itr : edgeF[nod])
			if (not viz[itr])
				solve(itr);
		st.push(nod);
	}

    int minK(vector <string> graph) {
		int n = graph.size();
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (graph[i][j] == 'Y') {
					edge[i].push_back(j);
					edgeB[j].push_back(i);
				}
		for (int i = 0; i < n; ++i)
			sol[i] = 0;
		nr_c = 0;
		for (int i = 0; i < n; ++i) {
	    	for (int j = 0; j < n; ++j)
				viz[j] = false;
			if (sol[i])
				continue;
			++nr_c;
			df(i);
			dfB(i);
		}
		
		for (int i = 0; i < n; ++i) {
	    	int nr = 0;
			for (int j = 0; j < n; ++j)
				if (graph[i][j] == 'Y' and sol[i] == sol[j])
					++nr;
			if (nr > 1)
				return -1;
		}

 		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (graph[i][j] == 'Y') {   	
					if (sol[i] != sol[j]) {
						edgeF[sol[i]].push_back(sol[j]);
						edgeFB[sol[j]].push_back(sol[i]);
					}
				}

        for (int i = 1; i <= nr_c; ++i)
			viz[i] = false;
		for (int i = 1; i <= nr_c; ++i)
			if (not viz[i])
				solve(i);

		int mx = 0;
		while (st.size()) {
			int nod = st.top();
			st.pop();
			for (int itr : edgeFB[nod]) {
				if (rez[nod] < rez[itr])
					rez[nod] = rez[itr];
			}
			if (nr_sol[nod] != 1)
				rez[nod]++;
			if (mx < rez[nod])
				mx = rez[nod];
		}
		return max(mx - 1, 0);
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
	
	int verify_case(int casenum, const int &expected, const int &received, std::clock_t elapsed) { 
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
			std::cerr << "    Expected: " << expected << std::endl; 
			std::cerr << "    Received: " << received << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string graph[]            = {"NYY",
 "YNY",
 "YYN"};
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = BigO().minK(vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string graph[]            = {"NYNNN",
 "NNYNN",
 "NNNYN",
 "NNNNY",
 "NNNNN"};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = BigO().minK(vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string graph[]            = {"NYNNN",
 "YNNNN",
 "NNNYN",
 "NNNNY",
 "NNYNN"};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = BigO().minK(vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string graph[]            = {"NYYYNYYYNNYYYYYYNYNN",
 "NNNNYNYYNNYYYNYYNYYN",
 "NYNNYYYNNNYYYYNYNYNN",
 "NYYNNYYYYNNNYYNNYNYY",
 "NYNYNNNNNNYYYYYNYYYN",
 "YNNNNNNYNNYNNYYYYYYY",
 "NNYYNNNNNYNYNYNNYNYY",
 "NNYNYYNNNNYNYNYYYYNN",
 "NYYNYYNNNYNNYYYNYNYN",
 "YYNNYNNYYNYNNNNNYNNN",
 "YYNYYNNYYYNYYNYNYYYY",
 "YYNNYYNYNYNNNNYNNNNY",
 "NNYYNYYYNNNNNYYYYYNY",
 "YNNNYNNNNYNNNNNYNNNY",
 "YYYYNYYNNYNNNNNYNNNN",
 "NYYYYNYNYYNNYNNNYNNY",
 "YYYYYNNNYYYYNYYYNNYN",
 "NNYNNYNYNYNNNNNNYNYN",
 "YYNYYNNNNNYNNYNYNNNY",
 "YYYYNYNYYNNYNYNYNNNN"};
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = BigO().minK(vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string graph[]            = {"NYNYYYNYYYNYYNYYNYYNYYNYNNYYYYNNNYYNNNYNYYNYNNNYNY",
 "NNNNNNNNNNNNNNNNYNNNYNNNNNYNYNYNNNNNNYNNNNNNNNNNNN",
 "NYNYYYYNYNYYNNYYYYYYYYYYNYYYNYYYYYYNNYYYYYYYNNYYYY",
 "NYNNYYNNNNNNNNNNNYNNNYNYNNYNYNYYNYYNNYYYNNNNNNNYYY",
 "NNNNNNNNNNNNYNNYYNNNYNNNNYNNYNNYNNYNNYNYNNNNNNNYYN",
 "NNNNNNNNNNNNNNNNYNNNYNNNNNNNNNYNNNNNNYNNNNNNNNNNNN",
 "YYNYNNNYNYYYYNYYYYYYYYYYNYYYYYYYNYYNNYNYYYYYNNYNYY",
 "NYNYYNNNYYNNYNNYYYNNYYNYNYYNYYYNNNYNNYYYNNNNNNNYYY",
 "NYNYYYNYNYNNNNNYYYNNNNNNNYYNYYYYNYYNNYYYNNNNNNNYYY",
 "NYNNNYNNNNNNNNNYYNNNYNNNNNYNYNYNNYYNNYNYNNNYNNNNYN",
 "NYNYYYNNYYNYYNYNYYNYYYNYNYYNYYYYNYNNNNYYYYNYNNNYNY",
 "NYNNYYNNNYNNYNNYYYNNYYNNNYYNYYNNNYYNNNNYNNNYNNNYYY",
 "NNNNNNNNNNNNNNNYYNNNYNNNNNNNYNNYNYNNNYYNNNNNNNNYNN",
 "YYYYNYYYYYYYYNYYYYNYYYYYYYYYYYNYYNYYYNYYYYYNNYYNYN",
 "NYNYYNNYYYNYYNNYYYNYNYNYNYYNYYYYNYYNNYYYYYNYNNNNNY",
 "NYNNNNNNNNNNNNNNYNNNYNNNNNYNYNYYNYNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNN",
 "NYNNNYNNNNNNNNNYYNNNNNNNNNNNYNYYNYYNNYNNNNNNNNNYYN",
 "NYNYYYNNYYNYNNYYYYNYYYNYNYYYYNNYNNYNNYNYYYYNNNYYYY",
 "NNNYYYNNNYNYYNNYYYNNYYNNNYYNYYYYNYYNNNYYNYNYNNNYYY",
 "NNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNN",
 "NYNNNYNNNNNNNNNYNNNNNNNNNYYNYYYYNYYNNYNNNNNNNNNYYN",
 "YYNYYYNNYYNYYNYNYYNYNYNYNYYYYYYYNYNNNYYYYYNYNNYYYY",
 "NYNYYYNNNNNNYNNNYYNNYYNNNYYNYYYYNYYNNYYYNNNNNNNYNY",
 "YNNNYYYYYYYYYNYYYYYYYYYNNYYNYNYNYNNYYYYYYYNYNNYYYY",
 "NYNNNYNNNNNNNNNYYNNNYNNNNNYNYNYYNYYNNNNYNNNNNNNYNN",
 "NNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNN",
 "NYNYYYNYYYNYNNNNYYNYYNNYNYYNYYYYNYYNNNNNYYNYNNYYNN",
 "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNN",
 "NYNNNYNNNNNNNNNYYNNNYNNNNNNNNNYYNYYNNNNYNNNNNNNYYY",
 "NNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNYNNNYNNNNNYNNNYNNNNNNNNNNNNNNNNNNN",
 "NYNYYNNYYYNNNNNYYYNYYYNNNYYYYYYYNYYNNYYYYNNYNNNNYY",
 "NNNNNNNNNNNNNNNYYNNNYNNNNNYNYNYYNNNNNYNNNNNNNNNNNN",
 "NYNNNNNNNNNNNNNNYNNNYNNNNNYNNNYYNNNNNNNNNNNNNNNYNN",
 "NYNYYYYYNYYYYNYYYYYYNYYYNNNYYYYYNYYNYNYYYYYYNYYYNY",
 "YYNYYYNYYYNNNNNYNYYYYNYNNNYYYYYYNYYNNYYNYNNYNNYNNY",
 "NNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NYNNNYNNNNNNNNNYYNNNNYNNNNYNYNNYNNNNNYNYNNNNNNNYNN",
 "NYNNNYNNNNNNNNNYYNNNNNNNNYYNYNYNNYYNNNNNNNNNNNNYNN",
 "NYNYYYNYYYNYNNNNNYNNYYNYNNYNNYYYNYYNNYYYNNNNNNNYYY",
 "NYNYYNNNNYNYYNNYYYNYYYNNNYYNYYYNNYYNNYYYNNNYNNNNYY",
 "NYNYNYNYYYNYYNYYNYNYNYYYNNYYYYYYNNNNNYYYNYNYNNYNYY",
 "NYNNNYNNNYNNNNNYYYNNYNNNNNYNYNNNNYYNNYNYNNNNNNNYYN",
 "YYYNNYNYYYNYNNYYYYYNYYNYNYYYYYNYYNYNYYYYYNNYNNYNYN",
 "YYNNYYYYYYYNYNYYNYYYYYYYYYYNYYYNYYYNNYYYYNYYNNYYYY",
 "NYNNYYNYYYNNYNNYYYNYNYNYNYYNNYYNNYNNNYYYNYNYNNNNYY",
 "NNNNNNNNNNNNNNNNYNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNNNNNYNNNNNYNYNYNNNNNNYNNNNNNNNNYNN",
 "NYNNYYNNNNNNNNNYYNNNNNNNNYYNYNNYNYYNNYNYNNNNNNNYNN"};
			int expected__            = 7;

			std::clock_t start__      = std::clock();
			int received__            = BigO().minK(vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string graph[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = BigO().minK(vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string graph[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = BigO().minK(vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string graph[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = BigO().minK(vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
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
