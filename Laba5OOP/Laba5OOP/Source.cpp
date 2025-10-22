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
            throw runtime_error("Не вдалося створити/відкрити файл: " + filename);
        }
        ofs.close();
        isOpen = true;
        cout << "Файл \"" << filename << "\" готовий до роботи (створено/відкрито).\n";
    }

    void writeData(const string& data, bool append) override {
        if (!isOpen)
            throw runtime_error("Файл не відкрито. Викличте openFile() спочатку.");

        ofstream ofs;
        if (append) ofs.open(filename, ios::out | ios::app);
        else ofs.open(filename, ios::out | ios::trunc);

        if (!ofs.is_open())
            throw runtime_error("Не вдалося відкрити файл для запису: " + filename);

        ofs << data << "\n";
        ofs.close();
        cout << "Дані записано у файл (" << (append ? "додано" : "перезаписано") << ").\n";
    }

    void readData() override {
        if (!isOpen)
            throw runtime_error("Файл не відкрито. Викличте openFile() спочатку.");

        ifstream ifs(filename);
        if (!ifs.is_open())
            throw runtime_error("Не вдалося відкрити файл для читання: " + filename);

        cout << "\n=== Вміст файлу \"" << filename << "\" ===\n";
        string line;
        while (getline(ifs, line)) {
            cout << line << "\n";
        }
        cout << "============================\n";
        ifs.close();
    }

    void closeFile() override {
        isOpen = false;
        cout << "Файл \"" << filename << "\" закритий (логічно).\n";
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
        cout << "\n=== МЕНЮ ===\n";
        cout << "1. Відкрити/створити файл\n";
        cout << "2. Записати текст у файл (перезапис)\n";
        cout << "3. Додати текст у файл \n";
        cout << "4. Прочитати вміст файлу\n";
        cout << "5. Закрити файл\n";
        cout << "0. Вийти\n";
        cout << "Виберіть опцію: ";

        int choice;
        if (!(cin >> choice)) {
            cout << "Невірний ввід. Спробуйте ще раз.\n";
            clearInputLine();
            continue;
        }
        clearInputLine();

        try {
            if (choice == 0) {
                cout << "Вихід...\n";
                break;
            }
            else if (choice == 1) {
                cout << "Введіть ім'я файлу: ";
                string fname;
                getline(cin, fname);
                if (fname.empty()) {
                    cout << "Ім'я файлу не може бути порожнім.\n";
                    continue;
                }
                handler.openFile(fname);
                hasOpened = true;
            }
            else if (choice == 2) {
                if (!hasOpened) { cout << "Спочатку відкрийте файл.\n"; continue; }
                cout << "Введіть текст для запису (ця операція перезапише вміст файлу).\n";
                string text;
                getline(cin, text);
                handler.writeData(text, false);
            }
            else if (choice == 3) {
                if (!hasOpened) { cout << "Спочатку відкрийте файл (опція 1).\n"; continue; }
                cout << "Введіть текст для додавання у файл.\n";
                string text;
                getline(cin, text);
                handler.writeData(text, true);
            }
            else if (choice == 4) {
                if (!hasOpened) { cout << "Спочатку відкрийте файл.\n"; continue; }
                handler.readData();
            }
            else if (choice == 5) {
                if (!hasOpened) { cout << "Файл не відкрито.\n"; continue; }
                handler.closeFile();
                hasOpened = false;
            }
            else {
                cout << "Невідома опція. Спробуйте ще раз.\n";
            }
        }
        catch (const exception& ex) {
            cerr << "Помилка: " << ex.what() << "\n";
        }
    }

    return 0;
}
