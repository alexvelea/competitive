#include <iostream>
#include <fstream>
#include <termios.h>
#include <unistd.h>
using namespace std;


int getch() {
        int buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 4) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

ofstream fout("data.txt");

int main() {
	for (int n = 3; n <= 6; ++n) {
		for (int i = 1; i < n; ++i) 
			for (int j = i; j <= 20; ++j) {
				if (((i * j) % n) == 0) {
                 for (int a = 1; a <= i; ++a, cerr << '\n')
					for (int b = 1; b <= j; ++b) 
						cerr << '#';
					cerr << "\n\n\n\n\n";   				
 					int x = getch();
					if (x == 32) {
						fout << "{{" << i << ", {" << j << ", " << n << "}}, true},\n";
					}
				}
			}
	}
}
