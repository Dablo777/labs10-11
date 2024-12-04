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

// ������� ��� ������� �����
void processFile(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName);
    if (!inputFile) {
        cout << "������� ��� ������� ����� ��� �������!" << endl;
        return;
    }

    ofstream outputFile(outputFileName);
    if (!outputFile) {
        cout << "������� ��� ������� ����� ��� ������!" << endl;
        return;
    }

    string line;
    int totalWordCount = 0;

    while (getline(inputFile, line)) {
        string shortestWord = findShortestWord(line);
        outputFile << shortestWord << endl;
        totalWordCount += countWordsInLine(line);
    }

    outputFile << "�������� ������� ���: " << totalWordCount << endl;

    inputFile.close();
    outputFile.close();
}

void displayMenu() {
    cout << "\n������� ��:\n"
        << " [1] - �������� ����\n"
        << " [0] - ����� � ��������\n"
        << " ������ �������� �������: ";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string inputFileName, outputFileName;
    int menu;

    cout << "������ ��'� �������� �����: ";
    cin >> inputFileName;
    cout << "������ ��'� ��������� �����: ";
    cin >> outputFileName;

    do {
        displayMenu();
        cin >> menu;

        try {
            switch (menu) {
            case 1:
                processFile(inputFileName, outputFileName);
                cout << "������� ����� ���������.\n";
                break;
            case 0:
                cout << "����� � ��������.\n";
                break;
            default:
                cout << "������ �������. ��������� �� ���.\n";
            }
        }
        catch (const exception& e) {
            cout << "�������: " << e.what() << endl;
        }

    } while (menu != 0);

    return 0;
}
