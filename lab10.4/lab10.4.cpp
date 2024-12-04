 #include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>
/*
C:\Users\User\Desktop\t.txt
*/
using namespace std;

string findShortestWord(const string& line) {
    istringstream stream(line);
    string word;
    string shortestWord;
    size_t minLength = -1; 

    while (stream >> word) {
        if (word.length() < minLength) {
            shortestWord = word;
            minLength = word.length();
        }
    }
    return shortestWord;
}

int countWordsInLine(const string& line) {
    istringstream stream(line);
    string word;
    int wordCount = 0;

    while (stream >> word) {
        wordCount++;
    }
    return wordCount;
}

// Функція для обробки файлу
void processFile(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName);
    if (!inputFile) {
        cout << "Помилка при відкритті файлу для читання!" << endl;
        return;
    }

    ofstream outputFile(outputFileName);
    if (!outputFile) {
        cout << "Помилка при відкритті файлу для запису!" << endl;
        return;
    }

    string line;
    int totalWordCount = 0;

    while (getline(inputFile, line)) {
        string shortestWord = findShortestWord(line);
        outputFile << shortestWord << endl;
        totalWordCount += countWordsInLine(line);
    }

    outputFile << "Загальна кількість слів: " << totalWordCount << endl;

    inputFile.close();
    outputFile.close();
}

void displayMenu() {
    cout << "\nВиберіть дію:\n"
        << " [1] - Обробити файл\n"
        << " [0] - Вихід з програми\n"
        << " Введіть значення команди: ";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string inputFileName, outputFileName;
    int menu;

    cout << "Введіть ім'я вхідного файлу: ";
    cin >> inputFileName;
    cout << "Введіть ім'я вихідного файлу: ";
    cin >> outputFileName;

    do {
        displayMenu();
        cin >> menu;

        try {
            switch (menu) {
            case 1:
                processFile(inputFileName, outputFileName);
                cout << "Обробка файлу завершена.\n";
                break;
            case 0:
                cout << "Вихід з програми.\n";
                break;
            default:
                cout << "Невірна команда. Спробуйте ще раз.\n";
            }
        }
        catch (const exception& e) {
            cout << "Помилка: " << e.what() << endl;
        }

    } while (menu != 0);

    return 0;
}
