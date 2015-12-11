//Problem d from mingcoding2015Round3
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

int card[4], currentCard, type;
bool iStarted = false;

void myMove();

void computerMove() {
	cin >> type;
	if (type <= 4) {
		return;
	}
	myMove();
}

int cnt714 = 0;

void show(int nr) {
	if (iStarted == true) {
		if (nr == 0) {
			for (int i = 0; i < 4; ++i) {
				if (card[i] != 7 and card[i] != 14) {
					nr = card[i];
					break;
				}
			}
		}
	
		if (nr == 0) {
			for (int i = 0; i < 4; ++i) {
				if (card[i] == 14) {
					nr = card[i];
					break;
				}
			}
		}

	 	if (nr == 0) {
			for (int i = 0; i < 4; ++i) {
				if (card[i] == 7) {
					nr = card[i];
					break;
				}
			}
		}   
	}

	cout << nr << '\n';
	cout.flush();
	for (int i = 0; i < 4; ++i)
		if (card[i] == nr and nr != 0) {
			card[i] = -1;
			break;
		}
}

void myMove() {
	if (currentCard == 14) {
		if (iStarted == true or cnt714 >= 2) {
			for (int i = 0; i < 4; ++i) {
				if (card[i] == 14) {
					show(14);
					computerMove();
					return ;
				}
			}
			for (int i = 0; i < 4; ++i) {
				if (card[i] == 7) {
					show(7);
					computerMove();
					return ;
				}
			}
			show(0);
			return ;
		} else {
			show(0);
			return ;
		}
	} else {
		if (currentCard == 7) {
			if (iStarted) {
				for (int i = 0; i < 4; ++i) {
					if (card[i] == 7) {
						show(7);
						computerMove();
						return ;
					}
				}

			show(0);
			return ;
			}
		}

		for (int i = 0; i < 4; ++i) {
			if (currentCard == card[i]) {
				show(currentCard);
				computerMove();
				return ;
			}
		}
		show(0);
		cout.flush();
		return ;
	}
}

void computerStarts() {
	iStarted = false;
	cnt714 = 0;
	cin >> currentCard;
	if (currentCard == 14) {
		for (int i = 0; i < 4; ++i) {
			if (card[i] == 7 or card[i] == 14) {
				++cnt714;
			}
		}
	}
	myMove();
}

void iStart() {
	iStarted = true;
	int cnt7 = 0, cnt14 = 0;
	for (int i = 0; i < 4; ++i) {
		if (card[i] == 7)
			++cnt7;
		if (card[i] == 14)
			++cnt14;
	}

	for (int i = 0; i < 4; ++i)
		assert(card[i] != 0);

	if (cnt14 and cnt7 + cnt14 >= 3) {
		show(14);
		currentCard = 14;
	} else {
		random_shuffle(card + 0, card + 4);
		int itr = 0;
		while (card[itr] != 14) {
			++itr;
		}
		show(card[itr]);
		currentCard = card[itr];
	}
	computerMove();
}

int main() {
	ios::sync_with_stdio(false);
for (int i = 0; i < 1000; ++i) {
	for (int j = 0; j < 4; ++j)
		cin >> card[j];
		computerStarts();
		while (1) {
			if (type == 4) {
				int a, b; cin >> a >> b;
			} else {
				int n; cin >> n;
				for (int i = 0; i < n; ++i) {
					int aux; cin >> aux;
					int itr = 0;
					while (card[itr] != -1) {
						++itr;
					}
					card[itr] = aux;
				}
				if (type == 3) {
					iStart();
				} else {
					computerStarts();
				}
			}
		}
	}
	return 0;
}
