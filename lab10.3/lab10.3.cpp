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
    cout << "| №  | Прізвище | Ініціали | АП | ООП | Математика | Англійська мова | Історія |"
        << endl;
    cout << "================================================================================"
        << endl;
}

void PrintFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        throw runtime_error("Неможливо відкрити файл!");
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
        throw runtime_error("Неможливо відкрити файл для запису!");
    }

    Students s;
    cout << "Введіть прізвище студента: "; cin >> s.surname;
    cout << "Введіть ініціали студента: "; cin >> s.initials;
    cout << "Введіть оцінку з АП: "; cin >> s.ap;
    cout << "Введіть оцінку з ООП: "; cin >> s.oop;
    cout << "Введіть оцінку з Математики: "; cin >> s.math;
    cout << "Введіть оцінку з Англійської мови: "; cin >> s.english;
    cout << "Введіть оцінку з Історії: "; cin >> s.history;
    fout << s.surname << " " << s.initials << " " << s.ap << " " << s.oop << " "
        << s.math << " " << s.english << " " << s.history << endl;

    fout.close();
}

void ListOnly5FromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        throw runtime_error("Неможливо відкрити файл!");
    }

    cout << "Список студентів, які склали іспити тільки на «5»:" << endl;
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
        throw runtime_error("Неможливо відкрити файл!");
    }

    cout << "Список студентів, що мають «3»:" << endl;

    Students s;
    bool found = false;
    while (fin >> s.surname >> s.initials >> s.ap >> s.oop >> s.math >> s.english >> s.history) {
        if (s.ap == 3 || s.oop == 3 || s.math == 3 || s.english == 3 || s.history == 3) {
            cout << s.surname << ", ";
            found = true;
        }
    }

    if (!found) {
        cout << "Немає студентів з оцінкою «3».\n";
    }
    else {
        cout << endl;
    }

    fin.close();
}

void ListHave2FromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        throw runtime_error("Неможливо відкрити файл!");
    }

    ofstream fout("temp.txt");
    if (!fout) {
        throw runtime_error("Неможливо відкрити тимчасовий файл!");
    }

    cout << "Список студентів, що мають «2» (але не більше двох двійок):" << endl;

    Students s;
    while (fin >> s.surname >> s.initials >> s.ap >> s.oop >> s.math >> s.english >> s.history) {
        int count = 0;

        if (s.ap == 2) count++;
        if (s.oop == 2) count++;
        if (s.math == 2) count++;
        if (s.english == 2) count++;
        if (s.history == 2) count++;

        if (count > 2) {
            cout << "Студент " << s.surname << " вилучений з файлу через більше ніж 2 двійки." << endl;
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
        throw runtime_error("Неможливо відкрити файл для читання!");
    }

    ofstream fout("temp.txt");
    if (!fout) {
        throw runtime_error("Неможливо відкрити тимчасовий файл!");
    }

    int k;
    cout << "Номер студента, дані якого треба редагувати: ";
    cin >> k;

    Students s;
    int index = 1;
    bool found = false;
    while (fin >> s.surname >> s.initials >> s.ap >> s.oop >> s.math >> s.english >> s.history) {
        if (index++ == k) {
            found = true;
            cout << "Введіть нові дані студента:\n";
            cout << "Прізвище: "; cin >> s.surname;
            cout << "Ініціали: "; cin >> s.initials;
            cout << "Оцінка з АП: "; cin >> s.ap;
            cout << "Оцінка з ООП: "; cin >> s.oop;
            cout << "Оцінка з Математики: "; cin >> s.math;
            cout << "Оцінка з Англійської мови: "; cin >> s.english;
            cout << "Оцінка з Історії: "; cin >> s.history;
        }
        fout << s.surname << " " << s.initials << " " << s.ap << " " << s.oop << " "
            << s.math << " " << s.english << " " << s.history << endl;
    }

    fin.close();
    fout.close();

    if (!found) {
        cout << "Студента з таким номером не існує!" << endl;
    }
    else {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
}


void DeleteStudentFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        throw runtime_error("Неможливо відкрити файл для читання!");
    }

    ofstream fout("temp.txt");
    if (!fout) {
        throw runtime_error("Неможливо відкрити тимчасовий файл!");
    }

    int k;
    cout << "Номер студента, якого треба вилучити: "; cin >> k;

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
        cout << "Студента з таким номером не існує!" << endl;
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
    cout << "Введіть ім'я файлу: ";
    cin >> filename;

    int menu;
    do {
        cout << "\nВиберіть дію:\n"
            << " [1] - Вивести таблицю всіх студентів\n"
            << " [2] - Додати студента\n"
            << " [3] - Список студентів, що склали іспити тільки на '5'\n"
            << " [4] - Вилучити студента\n"
            << " [5] - Список студентів, що мають '3'\n"
            << " [6] - Список студентів, що мають '2'\n"
            << " [7] - Редагувати дані студента\n"
            << " [0] - Вихід з програми\n"
            << " Введіть значення команди: ";
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
                cout << "Невірна команда. Спробуйте ще раз.\n";
            }
        }
        catch (const exception& e) {
            cout << "Помилка: " << e.what() << endl;
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

    Assert::IsFalse(found, L"Студент Brown A. не мав бути у файлі!");


    return 0;
    
}


