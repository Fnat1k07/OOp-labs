#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

class Sportsman {
protected:
    string name;
    int age;
    string sport;
    int medals;

public:
    Sportsman() : name("Невідомо"), age(0), sport("Невідомо"), medals(0) {}

    virtual ~Sportsman() {
        name.clear();
        sport.clear();
        age = 0;
        medals = 0;
    }

    virtual void inputData() {
        cout << "Введіть ім'я спортсмена: ";
        getline(cin, name);

        while (true) {
            cout << "Введіть вік: ";
            cin >> age;
            if (cin.fail() || age <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << " Помилка! Введіть число > 0.\n";
            }
            else break;
        }

        cin.ignore();

        cout << "Введіть вид спорту: ";
        getline(cin, sport);

        while (true) {
            cout << "Введіть кількість медалей: ";
            cin >> medals;
            if (cin.fail() || medals < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << " Помилка! Введіть невід’ємне число.\n";
            }
            else break;
        }
        cin.ignore();
    }

    virtual void showInfo() const {
        cout << "=== СПОРТСМЕН ===\n";
        cout << "Ім'я: " << name << endl;
        cout << "Вік: " << age << endl;
        cout << "Вид спорту: " << sport << endl;
        cout << "Кількість медалей: " << medals << endl;
    }

    virtual void writeToFile(ofstream& out) const {
        out << "СПОРТСМЕН: " << name << ", " << age << " р., "
            << sport << ", медалей: " << medals << endl;
    }
};

class Teacher : public Sportsman {
protected:
    string discipline;
    int experience;
    double rating;

public:
    Teacher() : Sportsman(), discipline("Невідомо"), experience(0), rating(0.0) {}

    ~Teacher() override {
        discipline.clear();
        experience = 0;
        rating = 0;
    }

    void inputData() override {
        Sportsman::inputData();

        cout << "Введіть дисципліну: ";
        getline(cin, discipline);

        while (true) {
            cout << "Введіть стаж (років): ";
            cin >> experience;
            if (cin.fail() || experience < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << " Помилка! Введіть число.\n";
            }
            else break;
        }

        while (true) {
            cout << "Введіть рейтинг (0-5): ";
            cin >> rating;
            if (cin.fail() || rating < 0 || rating > 5) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Помилка! Введіть число в межах 0–5.\n";
            }
            else break;
        }

        cin.ignore();
    }

    void showInfo() const override {
        cout << "=== ВИКЛАДАЧ ===\n";
        Sportsman::showInfo();
        cout << "Дисципліна: " << discipline << endl;
        cout << "Стаж: " << experience << " років\n";
        cout << "Рейтинг: " << rating << endl;
    }

    void writeToFile(ofstream& out) const override {
        out << "ВИКЛАДАЧ: " << name << ", " << age << " р., "
            << sport << ", медалей: " << medals
            << ", дисципліна: " << discipline
            << ", стаж: " << experience
            << ", рейтинг: " << rating << endl;
    }
};

class Coach : public Teacher {
private:
    int trainees;
    string bestTeam;

public:
    Coach() : Teacher(), trainees(0), bestTeam("Невідомо") {}

    ~Coach() override { 
        bestTeam.clear();
        trainees = 0;
    }


    void inputData() override {
        Teacher::inputData();

        while (true) {
            cout << "Введіть кількість вихованців: ";
            cin >> trainees;
            if (cin.fail() || trainees < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << " Помилка! Введіть число.\n";
            }
            else break;
        }
        cin.ignore();

        cout << "Введіть найкращу команду: ";
        getline(cin, bestTeam);
    }

    void showInfo() const override {
        cout << "=== ТРЕНЕР ===\n";
        Teacher::showInfo();
        cout << "Кількість вихованців: " << trainees << endl;
        cout << "Найкраща команда: " << bestTeam << endl;
    }

    void writeToFile(ofstream& out) const override {
        out << "ТРЕНЕР: " << name << ", " << age << " р., "
            << sport << ", медалей: " << medals
            << ", дисципліна: " << discipline
            << ", стаж: " << experience
            << ", рейтинг: " << rating
            << ", вихованців: " << trainees
            << ", найкраща команда: " << bestTeam << endl;
    }
};

int main() {
    setlocale(LC_ALL, "ukr");

    ofstream fout("sportsmen.txt", ios::app);
    if (!fout.is_open()) {
        cerr << "Не вдалося відкрити файл!" << endl;
        return 1;
    }

    int choice;
    while (true) {
        cout << "\n============================\n";
        cout << "   МЕНЮ\n";
        cout << "1. Додати спортсмена\n";
        cout << "2. Додати викладача\n";
        cout << "3. Додати тренера\n";
        cout << "4. Вийти\n";
        cout << "============================\n";
        cout << "Ваш вибір: ";
        cin >> choice;
        cin.ignore();

        if (choice == 4) {
            cout << "Програму завершено.\n";
            break;
        }

        Sportsman* ptr = nullptr;

        switch (choice) {
        case 1:
            ptr = new Sportsman();
            break;
        case 2:
            ptr = new Teacher();
            break;
        case 3:
            ptr = new Coach();
            break;
        default:
            cout << "Невірний вибір!\n";
            continue;
        }

       
        cout << "\nВведення інформації:\n";
        ptr->inputData();

        cout << "\nВи ввели:\n";
        ptr->showInfo();

        ptr->writeToFile(fout);
        fout.flush();

        delete ptr;
        cout << "\n Дані успішно збережено у файл 'sportsmen.txt'\n";
    }

    fout.close();
    return 0;
}
