#include <iostream>
#include <string>
#include <stdexcept>
#include "zarplata.h"

using namespace std;

// === Функція для перевірки телефону ===
string inputPhone() {
    string phone;
    cout << "Введіть номер телефону (у форматі 380XXXXXXXXX): ";
    cin >> phone;

    if (phone.size() != 12)
        throw invalid_argument("Помилка: номер телефону повинен містити рівно 12 цифр (380 + 9 цифр).");

    for (char c : phone) {
        if (!isdigit(c))
            throw invalid_argument("Помилка: номер телефону може містити тільки цифри.");
    }

    if (phone.substr(0, 3) != "380")
        throw invalid_argument("Помилка: номер телефону повинен починатися з '380'.");

    return phone;
}

double inputSalary() {
    double salary;
    while (true) {
        cout << "Введіть зарплату: ";
        cin >> salary;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cerr << "Помилка: зарплата повинна бути числом!\n";
        }
        else if (salary < 0) {
            cerr << "Помилка: зарплата не може бути від’ємною!\n";
        }
        else {
            return salary;
        }
    }
}

void addEmployeeInteractive(Payroll& payroll) {
    string surname, name, patronymic, position, phone;
    double salary;

    cout << "Введіть прізвище: ";
    cin >> surname;
    cout << "Введіть ім'я: ";
    cin >> name;
    cout << "Введіть по батькові: ";
    cin >> patronymic;
    cout << "Введіть посаду: ";
    cin >> position;

    while (true) {
        try {
            phone = inputPhone();
            break;
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
        }
    }

    salary = inputSalary();

    try {
        Employee emp(surname, name, patronymic, phone, position, salary);
        payroll.addEmployee(emp);
        cout << "Співробітника додано успішно!\n";
    }
    catch (const exception& e) {
        cerr << "Помилка: " << e.what() << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Ukr");
    Payroll payroll;

    int choice;
    do {
        cout << "\n=== МЕНЮ ===\n";
        cout << "1. Додати співробітника\n";
        cout << "2. Звільнити співробітника (по прізвищу)\n";
        cout << "3. Вивести всіх співробітників\n";
        cout << "4. Знайти за діапазоном зарплати\n";
        cout << "5. Знайти за прізвищем\n";
        cout << "6. Знайти за посадою\n";
        cout << "7. Додати премію співробітнику\n";
        cout << "0. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        try {
            if (choice == 1) {
                addEmployeeInteractive(payroll);
            }
            else if (choice == 2) {
                string surname;
                cout << "Введіть прізвище співробітника для звільнення: ";
                cin >> surname;
                if (payroll.removeBySurname(surname)) {
                    cout << "Співробітника звільнено.\n";
                }
                else {
                    cout << "Не знайдено такого співробітника.\n";
                }
            }
            else if (choice == 3) {
                payroll.printAll();
            }
            else if (choice == 4) {
                double minS, maxS;
                cout << "Введіть мінімальну зарплату: ";
                cin >> minS;
                cout << "Введіть максимальну зарплату: ";
                cin >> maxS;
                payroll.find(minS, maxS);
            }
            else if (choice == 5) {
                string surname;
                cout << "Введіть прізвище: ";
                cin >> surname;
                payroll.find(surname);
            }
            else if (choice == 6) {
                string position;
                cout << "Введіть посаду: ";
                cin >> position;
                payroll.find(position, true);
            }
            else if (choice == 7) {
                string surname;
                double bonus;
                cout << "Введіть прізвище співробітника: ";
                cin >> surname;
                cout << "Введіть суму премії: ";
                cin >> bonus;

                if (payroll.addBonusBySurname(surname, bonus)) {
                    cout << "Премія додана!\n";
                }
                else {
                    cout << "Співробітника з таким прізвищем не знайдено.\n";
                }
            }
            else if (choice == 0) {
                cout << "Вихід...\n";
            }
            else {
                cout << "Невірний вибір!\n";
            }
        }
        catch (const exception& e) {
            cerr << "Помилка: " << e.what() << endl;
        }

    } while (choice != 0);

    return 0;
}
