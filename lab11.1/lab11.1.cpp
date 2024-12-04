#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

void CreateBIN(char* fname) {
    ofstream fout(fname, ios::binary);
    char ch;
    string s;
    do {
        cin.get();
        cin.sync();
        cout << "Type string: "; getline(cin, s);
        for (unsigned i = 0; i < s.length(); i++)
            fout.write((char*)&s[i], sizeof(s[i]));
        cout << "Continue? (y/n): "; cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << endl;
}

void PrintBIN(char* fname) {
    ifstream fin(fname, ios::binary);
    char c;
    while (fin.read((char*)&c, sizeof(c)))
        cout << c;
    cout << endl;
}

void ProcessBIN(char* fname, char* gname) {
    ifstream f(fname, ios::binary);
    ofstream g(gname, ios::binary);
    char c;
    while (f.read((char*)&c, sizeof(c))) {
        if ((c == '³' || c == 'í' || c == 'ô' || c == 'î' || c == 'ð'
            || c == 'ì' || c == 'à' || c == 'ò' || c == 'è' || c == 'ê')) {
            g.write((char*)&c, sizeof(c));
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char fname[100];
    cout << "Type name of file 1: "; cin >> fname;
    CreateBIN(fname);
    char gname[100];
    cout << "Type name of file 2: "; cin >> gname;
    ProcessBIN(fname, gname);
    PrintBIN(gname);
    return 0;
}
