//Problem a @ 26-09-2015
#include <cassert>
#include <cstring>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

const int kMaxN = 1e6;

#define int64 long long

char txt[kMaxN];
int n;
int itr = 0;

ifstream fin("bibtex.in");
ofstream fout("bibtex.out");

vector<string> split(string a) {
    int itr = 0;
    vector<string> rez;
    while (itr < int(a.size())) {
        while (not ('A' <= a[itr] and a[itr] <= 'z')) {
            ++itr;
        }

        string aux = "";
        while (('A' <= a[itr] and a[itr] <= 'z')) {
            aux += a[itr];
            ++itr;
        }

        rez.push_back(aux);
    }
    return rez;
}

bool fuck(vector<string> &a, vector<string> &b) {
    for (int i = 0; i < int(min(a.size(), b.size())); ++i) {
        if (a[i] != b[i]) {
            return a[i] < b[i];
        }
    }
    return a.size() < b.size();
}



struct Element {            
    map<string, string> el;
    vector<string> compEl;
    string text;
    int id;

    void debug() {
        for (auto itr : el) {
            cerr << itr.first << '\t' << itr.second << '\n';
        }
        cerr << "\n\n\n";
    }

    void addCompAuthor(vector<string> author) {
        for (auto itr : author) {
            compEl.push_back(itr);
        }
        for (int i = int(author.size()); i <= 11; ++i) {
            compEl.push_back("");
        }
    }


    string getAuthor() {
        vector<string> words = split(el["author"]);
        words.push_back("and");

        vector<vector<string> > authors;
        vector<string> currentAuthor;

        for (auto itr : words) {
            if (itr == "and") {
                authors.push_back(currentAuthor);
                currentAuthor.clear();
            } else {
                currentAuthor.push_back(itr);
            }
        }

        vector<string> shortAuthors;
        for (auto &itr : authors) {
            itr.push_back("");
            for (int i = int(itr.size()) - 2; i >= 0; --i) {
                itr[i + 1] = itr[i];
            }
            itr[0] = itr[itr.size() - 1];
            itr.pop_back();
        }
        sort(authors.begin(), authors.end(), fuck);

        for (auto itr : authors) {
            addCompAuthor(itr);    
        }
        
        for (int i = int(authors.size()); i <= 50; ++i) {
            vector<string> aux;
            addCompAuthor(aux);
        }

        for (auto itr : authors) {
            string rez = "";
            rez += itr[0];
            for (int i = 1; i < int(itr.size()); ++i) {
                rez += " ";
                rez += (itr[i][0]);
                rez += ".";
            }
            shortAuthors.push_back(rez);
        }

        string rez = "";
        sort(shortAuthors.begin(), shortAuthors.end());
        for (int itr = 0; itr < int(shortAuthors.size()); ++itr) {
            if (itr != 0) {
                rez += ", ";
            }
            rez += shortAuthors[itr];
        }
        return rez;
    }

    string getPage() {
        string page = el["page"];
        if (page == "") {
            return "";
        }

        bool found_ = false;
        for (auto itr : page) {
            if (itr == '-') {
                found_ = true;
            }
        }

        string rez = "";
        if (found_) {
            rez = "pp. " + page;
        } else {
            rez = "p. " + page;
        }

        return rez;
    }

    string getBook() {
        string rez = "";
        el["author"] = getAuthor();
        el["page"] = getPage();

        rez = el["author"] + ' ' + el["title"];
        if (el["volume"] != "") {
            rez += ", Vol. " + el["volume"];
        }
        rez += " -- " + el["publisher"];
        rez += ", " + el["year"];
        return rez;
    }

    string getArticle() {
        string rez = "";
        el["author"] = getAuthor();
        el["page"] = getPage();
        rez += el["author"] + ' ' + el["title"] + " // " + el["journal"];

        if (el["volume"] != "") {
            rez += ", " + el["volume"];
        }
        if (el["number"] != "") {
            rez += " (" + el["number"] + ")";
        }

        rez += " -- " + el["year"];

        if (el["page"] != "") {
            rez += " -- " + el["page"];
        }
        return rez;
    }

    void getString() {
        compEl.clear();
        string rez;
        if (el["type"] == "book") {
            rez = getBook();
        } else {
            rez =getArticle();
        }

        compEl.push_back(el["title"]);
        string r = el["volume"];
        while (r.size() < 30) {
            r = "0" + r;
        }
        compEl.push_back(r);
        compEl.push_back(el["type"]);
    
        text = rez;
        id = rand();
    }
};

bool fuck2(Element &a, Element &b) {
    assert((a.compEl.size()) == (b.compEl.size()));
    assert(a.id != b.id);
    for (int i = 0; i < a.compEl.size(); ++i) {
        if (a.compEl[i] != b.compEl[i]) {
            return a.compEl[i] < b.compEl[i];
        }
    }
//    assert(0);
    return false;
}
 

void getLetterOrEnd() {
    while (not (('A' <= txt[itr] and txt[itr] <= 'z') or (txt[itr] == '}'))) {
        ++itr;
    }
}

void getValue(Element &now, string valueType) {
    while (txt[itr] != '\"') {
        ++itr;
    } ++itr;
    string rez = "";
    while (txt[itr] != '\"') {
        rez += txt[itr];
        ++itr;
    } ++itr;
    now.el[valueType] = rez;
}

Element getElement(string elType) {
    while (txt[itr] != '{') {
        ++itr;    
    }

    Element now;
    now.el["type"] = elType;

    while (1) {
        getLetterOrEnd();
        char c = txt[itr];
        if (c == '}') {
            ++itr;
//            now.debug();
            return now;
        }

        if (c == 'a') {
            getValue(now, "author");
        } else if (c == 't') {
            getValue(now, "title");
        } else if (c == 'j') {
            getValue(now, "journal");
        } else if (c == 'p' and txt[itr + 1] == 'u') {
            getValue(now, "publisher");
        } else if (c == 'y') {
            getValue(now, "year");
        } else if (c == 'v') {
            getValue(now, "volume");
        } else if (c == 'n') {
            getValue(now, "number");
        } else if (c == 'p' and txt[itr + 1] == 'a') {
            getValue(now, "page");
        } else {
            assert(0);
        }
    }
}

int main() {
    fin.read(txt, kMaxN); 
    n = strlen(txt);
    vector<Element> el;
	while (itr < n) {
        while (txt[itr] != '@' and itr < n) {
            ++itr;
        } ++itr;

        if (itr >= n) {
            break;
        }

        if (txt[itr] == 'b') {
            el.push_back(getElement("book"));
        } else {
            el.push_back(getElement("article"));
        }
    }
    for (auto &itr : el) {
        itr.getString();
    }

    sort(el.begin(), el.end(), fuck2);
    for (auto itr : el) {
        for (auto a : itr.compEl) {
            cerr << a << '|';
        }
        cerr << '\n';
    }
    
    int ind = 1;
    for (auto itr : el) {
        fout << "[" << ind << "] " << itr.text << '\n';
        ++ind;
    }
    return 0;
}
