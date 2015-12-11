void read() {
	string aux, rez;
	while (in >> aux) {
		rez += aux;
		rez += '#';
	}
	in.close();
	return rez;
}

int main() {
	for (int t = 0; t < 100; ++t) {
		out.open("file.in");
		/* dsadasdsa */
		out.close();

		system("./brut.cpp");
		system("./main.cpp");

		in.open("file.out");
		a = read();

		in.open("file2.out");
		b = read();

		if (a != b)
			cerr << "Wrong!";
	}
}

