#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdexcept>
#include <Windows.h>

using namespace std;

struct Students {
    string surname;
    string initials;
    int ap;
    int oop;
    int math;
    int english;
    int history;
};

void PrintHeader() {
    cout << "================================================================================"
        << endl;
    cout << "| �  | ������� | ������� | �� | ��� | ���������� | ��������� ���� | ������ |"
        << endl;
    cout << "================================================================================"
        << endl;
}

void PrintFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        throw runtime_error("��������� ������� ����!");
    }

    PrintHeader();

    Students s;
    int index = 1;
    while (fin >> s.surname >> s.initials >> s.ap >> s.oop >> s.math >> s.english >> s.history) {
        cout << "| " << setw(2) << right << index++ << " ";
        cout
            << "| " << setw(9) << right << s.surname
            << "| " << setw(9) << right << s.initials
            << "| " << setw(3) << right << s.ap
            << "| " << setw(4) << right << s.oop
            << "| " << setw(11) << right << s.math
            << "| " << setw(16) << right << s.english
            << "| " << setw(8) << right << s.history << "|" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
    }

    fin.close();
}

void AddStudentToFile(const string& filename) {
    ofstream fout(filename, ios::app);
    if (!fout) {
        throw runtime_error("��������� ������� ���� ��� ������!");
    }

    Students s;
    cout << "������ ������� ��������: "; cin >> s.surname;
    cout << "������ ������� ��������: "; cin >> s.initials;
    cout << "������ ������ � ��: "; cin >> s.ap;
    cout << "������ ������ � ���: "; cin >> s.oop;
    cout << "������ ������ � ����������: "; cin >> s.math;
    cout << "������ ������ � ��������� ����: "; cin >> s.english;
    cout << "������ ������ � �����: "; cin >> s.history;
    fout << s.surname << " " << s.initials << " " << s.ap << " " << s.oop << " "
        << s.math << " " << s.english << " " << s.history << endl;

    fout.close();
}

void ListOnly5FromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        throw runtime_error("��������� ������� ����!");
    }

    cout << "������ ��������, �� ������ ������ ����� �� �5�:" << endl;
    Students s;
    while (fin >> s.surname >> s.initials >> s.ap >> s.oop >> s.math >> s.english >> s.history) {
        if (s.ap == 5 && s.oop == 5 && s.math == 5 && s.english == 5 && s.history == 5) {
            cout << s.surname << ", ";
        }
    }
    cout << endl;

    fin.close();
}

void ListHave3FromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        throw runtime_error("��������� ������� ����!");
    }

    cout << "������ ��������, �� ����� �3�:" << endl;

    Students s;
    bool found = false;
    while (fin >> s.surname >> s.initials >> s.ap >> s.oop >> s.math >> s.english >> s.history) {
        if (s.ap == 3 || s.oop == 3 || s.math == 3 || s.english == 3 || s.history == 3) {
            cout << s.surname << ", ";
            found = true;
        }
    }

    if (!found) {
        cout << "���� �������� � ������� �3�.\n";
    }
    else {
        cout << endl;
    }

    fin.close();
}

void ListHave2FromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        throw runtime_error("��������� ������� ����!");
    }

    ofstream fout("temp.txt");
    if (!fout) {
        throw runtime_error("��������� ������� ���������� ����!");
    }

    cout << "������ ��������, �� ����� �2� (��� �� ����� ���� �����):" << endl;

    Students s;
    while (fin >> s.surname >> s.initials >> s.ap >> s.oop >> s.math >> s.english >> s.history) {
        int count = 0;

        if (s.ap == 2) count++;
        if (s.oop == 2) count++;
        if (s.math == 2) count++;
        if (s.english == 2) count++;
        if (s.history == 2) count++;

        if (count > 2) {
            cout << "������� " << s.surname << " ��������� � ����� ����� ����� �� 2 �����." << endl;
        }
        else {
            if (count > 0) {
                cout << s.surname << ", ";
            }
            fout << s.surname << " " << s.initials << " " << s.ap << " " << s.oop << " "
                << s.math << " " << s.english << " " << s.history << endl;
        }
    }
    cout << endl;

    fin.close();
    fout.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}


void EditStudentInFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        throw runtime_error("��������� ������� ���� ��� �������!");
    }

    ofstream fout("temp.txt");
    if (!fout) {
        throw runtime_error("��������� ������� ���������� ����!");
    }

    int k;
    cout << "����� ��������, ��� ����� ����� ����������: ";
    cin >> k;

    Students s;
    int index = 1;
    bool found = false;
    while (fin >> s.surname >> s.initials >> s.ap >> s.oop >> s.math >> s.english >> s.history) {
        if (index++ == k) {
            found = true;
            cout << "������ ��� ��� ��������:\n";
            cout << "�������: "; cin >> s.surname;
            cout << "�������: "; cin >> s.initials;
            cout << "������ � ��: "; cin >> s.ap;
            cout << "������ � ���: "; cin >> s.oop;
            cout << "������ � ����������: "; cin >> s.math;
            cout << "������ � ��������� ����: "; cin >> s.english;
            cout << "������ � �����: "; cin >> s.history;
        }
        fout << s.surname << " " << s.initials << " " << s.ap << " " << s.oop << " "
            << s.math << " " << s.english << " " << s.history << endl;
    }

    fin.close();
    fout.close();

    if (!found) {
        cout << "�������� � ����� ������� �� ����!" << endl;
    }
    else {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
}


void DeleteStudentFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        throw runtime_error("��������� ������� ���� ��� �������!");
    }

    ofstream fout("temp.txt");
    if (!fout) {
        throw runtime_error("��������� ������� ���������� ����!");
    }

    int k;
    cout << "����� ��������, ����� ����� ��������: "; cin >> k;

    Students s;
    int index = 1;
    bool found = false;
    while (fin >> s.surname >> s.initials >> s.ap >> s.oop >> s.math >> s.english >> s.history) {
        if (index++ != k) {
            fout << s.surname << " " << s.initials << " " << s.ap << " " << s.oop << " "
                << s.math << " " << s.english << " " << s.history << endl;
        }
        else {
            found = true;
        }
    }

    fin.close();
    fout.close();

    if (!found) {
        cout << "�������� � ����� ������� �� ����!" << endl;
    }
    else {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string filename;
    cout << "������ ��'� �����: ";
    cin >> filename;

    int menu;
    do {
        cout << "\n������� ��:\n"
            << " [1] - ������� ������� ��� ��������\n"
            << " [2] - ������ ��������\n"
            << " [3] - ������ ��������, �� ������ ������ ����� �� '5'\n"
            << " [4] - �������� ��������\n"
            << " [5] - ������ ��������, �� ����� '3'\n"
            << " [6] - ������ ��������, �� ����� '2'\n"
            << " [7] - ���������� ��� ��������\n"
            << " [0] - ����� � ��������\n"
            << " ������ �������� �������: ";
        cin >> menu;

        try {
            switch (menu) {
            case 1:
                PrintFromFile(filename);
                break;
            case 2:
                AddStudentToFile(filename);
                break;
            case 3:
                ListOnly5FromFile(filename);
                break;
            case 4:
                DeleteStudentFromFile(filename);
                break;
            case 5:
                ListHave3FromFile(filename);
                break;
            case 6:
                ListHave2FromFile(filename);
                break;
            case 7:
                EditStudentInFile(filename);
                break;
            case 0:
                break;
            default:
                cout << "������ �������. ��������� �� ���.\n";
            }
        }
        catch (const exception& e) {
            cout << "�������: " << e.what() << endl;
        }

    } while (menu != 0);

    std::string filename = "test_students.txt";
    std::ofstream fout(filename);
    fout << "Smith J.D. 5 4 3 2 2\n";
    fout << "Doe J. 2 2 5 5 5\n";
    fout << "Brown A. 2 2 2 4 5\n";
    fout.close();

    ListHave2FromFile(filename);

    std::ifstream fin(filename);
    std::string line;
    bool found = false;
    while (getline(fin, line)) {
        if (line == "Brown A. 2 2 2 4 5") {
            found = true;
            break;
        }
    }
    fin.close();

    Assert::IsFalse(found, L"������� Brown A. �� ��� ���� � ����!");


    return 0;
    
}


