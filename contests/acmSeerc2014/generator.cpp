/*
	folder de seerc
	cu folder de teste in foldere cu nume problemei
	problemele se numesc pa pb pc pd .. etc
	cu litera mica
	pt linux
	system("./pa"); fara terminatie
	folderele cu input/output sunt cele de pe site
*/

#include <ctime>

#include <iomanip>
#include <fstream>
#include <iostream>
using namespace std;

ifstream in;
ofstream out;

void check(string &a) {
	string b;
	int after = 0;
	for (int i = 0; i < int(a.size()) and after <= 6; ++i) {
 		if (after > 0)
			after++;
		if (a[i] == '.')
			after++;
        b += a[i];
	}
	a = b;
}

string Read(ifstream &in) {
	string rez, aux;
	while (in >> aux) {
		check(aux);
		rez += aux;
		rez += ' ';
	}
	return rez;
}

int main() {
	cerr << "Problem number ";
	char problem_number, b_problem_number;
	cin >> problem_number;
	b_problem_number = problem_number - 'a' + 'A';

	for (int i = 1; i <= 100; ++i) {
		char inPC[] = "A/001.in";
		char outPC[] = "A/001.out";
		
		inPC[0] = b_problem_number;
        inPC[4] = (i % 10) + '0';
		inPC[3] = (i / 10) + '0';

		outPC[0] = b_problem_number;
		outPC[4] = (i % 10) + '0';
		outPC[3] = (i / 10) + '0';

		in.open(inPC);
		string input_text = Read(in);
        in.close();

		if (input_text == "")
			break;
        
 		out.open("input.txt");
		out << input_text << '\n';
		out.close();

		char file[] = "./pa";
		file[3] = problem_number;
		cerr << "#" << i << '\t';
		system(file);
		cerr << '\n';
		
		in.open("output.txt");
		string program_output = Read(in);
		in.close();

		in.open(outPC);
		string corect_output = Read(in);
		in.close();

		if (program_output != corect_output) {
			cerr << "Wrong at test " << i << "\n";
			break;
		}
	}
	return 0;
}
