#include <iostream>
#include <unordered_map>
#include <fstream>
using namespace std;

ifstream fin("random.in");
ofstream fout("random.out");

int main() {
	unordered_map<int, string> people = {
	    {1982 ,   "Robert Tarjan"},
	    {1986 ,   "Leslie Valiant"},
	    {1990 ,   "Alexander Razborov"},
	    {1994 ,   "Avi Wigderson"},
	    {1998 ,   "Peter Shor"},
	    {2002 ,   "Madhu Sudan"},
	    {2006 ,   "Jon Kleinberg"},
	    {2010 ,   "Daniel Spielman"},
	    {2014 ,   "Subhash Khot"} 
	};

	int n; fin >> n;
	fout << people[n] << '\n';
	return 0;
}

