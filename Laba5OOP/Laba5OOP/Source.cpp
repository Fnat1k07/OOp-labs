#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <stdexcept>

using namespace std;

class FileHandler {
public:
    virtual void openFile(const string& filename) = 0; 
    virtual void writeData(const string& data, bool append) = 0; 
    virtual void readData() = 0;                        
    virtual void closeFile() = 0;                       
    virtual ~FileHandler() {}
};

class TextFileHandler : public FileHandler {
private:
    string filename;
    bool isOpen = false;

public:
    void openFile(const string& fname) override {
        filename = fname;
        ofstream ofs(filename, ios::app);
        if (!ofs.is_open()) {
            throw runtime_error("�� ������� ��������/������� ����: " + filename);
        }
        ofs.close();
        isOpen = true;
        cout << "���� \"" << filename << "\" ������� �� ������ (��������/�������).\n";
    }

    void writeData(const string& data, bool append) override {
        if (!isOpen)
            throw runtime_error("���� �� �������. �������� openFile() ��������.");

        ofstream ofs;
        if (append) ofs.open(filename, ios::out | ios::app);
        else ofs.open(filename, ios::out | ios::trunc);

        if (!ofs.is_open())
            throw runtime_error("�� ������� ������� ���� ��� ������: " + filename);

        ofs << data << "\n";
        ofs.close();
        cout << "��� �������� � ���� (" << (append ? "������" : "������������") << ").\n";
    }

    void readData() override {
        if (!isOpen)
            throw runtime_error("���� �� �������. �������� openFile() ��������.");

        ifstream ifs(filename);
        if (!ifs.is_open())
            throw runtime_error("�� ������� ������� ���� ��� �������: " + filename);

        cout << "\n=== ���� ����� \"" << filename << "\" ===\n";
        string line;
        while (getline(ifs, line)) {
            cout << line << "\n";
        }
        cout << "============================\n";
        ifs.close();
    }

    void closeFile() override {
        isOpen = false;
        cout << "���� \"" << filename << "\" �������� (������).\n";
    }

    ~TextFileHandler() {
    }
};

void clearInputLine() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string readLinePrompt(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

int main() {
    setlocale(LC_ALL, "Ukr");
    TextFileHandler handler;
    bool hasOpened = false;

    while (true) {
        cout << "\n=== ���� ===\n";
        cout << "1. ³������/�������� ����\n";
        cout << "2. �������� ����� � ���� (���������)\n";
        cout << "3. ������ ����� � ���� \n";
        cout << "4. ��������� ���� �����\n";
        cout << "5. ������� ����\n";
        cout << "0. �����\n";
        cout << "������� �����: ";

        int choice;
        if (!(cin >> choice)) {
            cout << "������� ���. ��������� �� ���.\n";
            clearInputLine();
            continue;
        }
        clearInputLine();

        try {
            if (choice == 0) {
                cout << "�����...\n";
                break;
            }
            else if (choice == 1) {
                cout << "������ ��'� �����: ";
                string fname;
                getline(cin, fname);
                if (fname.empty()) {
                    cout << "��'� ����� �� ���� ���� �������.\n";
                    continue;
                }
                handler.openFile(fname);
                hasOpened = true;
            }
            else if (choice == 2) {
                if (!hasOpened) { cout << "�������� �������� ����.\n"; continue; }
                cout << "������ ����� ��� ������ (�� �������� ���������� ���� �����).\n";
                string text;
                getline(cin, text);
                handler.writeData(text, false);
            }
            else if (choice == 3) {
                if (!hasOpened) { cout << "�������� �������� ���� (����� 1).\n"; continue; }
                cout << "������ ����� ��� ��������� � ����.\n";
                string text;
                getline(cin, text);
                handler.writeData(text, true);
            }
            else if (choice == 4) {
                if (!hasOpened) { cout << "�������� �������� ����.\n"; continue; }
                handler.readData();
            }
            else if (choice == 5) {
                if (!hasOpened) { cout << "���� �� �������.\n"; continue; }
                handler.closeFile();
                hasOpened = false;
            }
            else {
                cout << "������� �����. ��������� �� ���.\n";
            }
        }
        catch (const exception& ex) {
            cerr << "�������: " << ex.what() << "\n";
        }
    }

    return 0;
}
