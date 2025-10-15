#ifndef ZARPLATA_H
#define ZARPLATA_H

#include <string>    
#include <stdexcept>   
#include <iostream>    
#include <sstream>    
#include <cctype>    

using namespace std;

// Допоміжна функція
inline string toLower(const string& s) {
    string r;
    for (char c : s) r.push_back((char)tolower((unsigned char)c));
    return r;
}

class Employee {
private:
    string surname;
    string name;
    string patronymic;
    string phone;
    string position;
    double salary;

public:
    Employee() : surname(), name(), patronymic(), phone(), position(), salary(0.0) {}

    Employee(const string& s, const string& n, const string& p,
        const string& ph, const string& pos, double sal)
        : surname(s), name(n), patronymic(p), phone(ph), position(pos) {
        setSalary(sal);
    }

    string getSurname() const { return surname; }
    string getName() const { return name; }
    string getPatronymic() const { return patronymic; }
    string getPhone() const { return phone; }
    string getPosition() const { return position; }
    double getSalary() const { return salary; }

    void setSurname(const string& s) { surname = s; }
    void setName(const string& s) { name = s; }
    void setPatronymic(const string& s) { patronymic = s; }
    void setPhone(const string& s) {
        if (s.empty()) throw invalid_argument("Phone cannot be empty");
        phone = s;
    }
    void setPosition(const string& s) { position = s; }

    void setSalary(double s) {
        if (s < 0.0) throw invalid_argument("Invalid salary: must be >= 0");
        salary = s;
    }

    // Премія
    Employee& operator+=(double bonus) {
        if (bonus < 0.0) throw invalid_argument("Bonus must be non-negative");
        salary += bonus;
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Employee& e) {
        os << e.surname << " " << e.name << " " << e.patronymic
            << " | Тел: " << e.phone
            << " | Посада: " << e.position
            << " | Зарплата: " << e.salary;
        return os;
    }

    string fullName() const {
        return surname + " " + name + " " + patronymic;
    }
};

class Payroll {
private:
    Employee* employees;
    int size;
    int capacity;

    void resize() {
        int newCap = capacity * 2;
        Employee* newArr = new Employee[newCap];
        for (int i = 0; i < size; i++) {
            newArr[i] = employees[i];
        }
        delete[] employees;
        employees = newArr;
        capacity = newCap;
    }

public:
    Payroll() : size(0), capacity(2) {
        employees = new Employee[capacity];
    }

    Payroll(const Payroll& other) {
        size = other.size;
        capacity = other.capacity;
        employees = new Employee[capacity];
        for (int i = 0; i < size; i++) {
            employees[i] = other.employees[i];
        }
    }

    Payroll& operator=(const Payroll& other) {
        if (this != &other) {
            delete[] employees;
            size = other.size;
            capacity = other.capacity;
            employees = new Employee[capacity];
            for (int i = 0; i < size; i++) {
                employees[i] = other.employees[i];
            }
        }
        return *this;
    }

    ~Payroll() {
        delete[] employees;
    }

    void addEmployee(const Employee& e) {
        for (int i = 0; i < size; i++) {
            if (toLower(employees[i].fullName()) == toLower(e.fullName())) {
                throw runtime_error("Employee already exists: " + e.fullName());
            }
            if (employees[i].getPhone() == e.getPhone()) {
                throw runtime_error("Phone already exists: " + e.getPhone());
            }
        }
        if (size == capacity) resize();
        employees[size++] = e;
    }

    bool removeBySurname(const string& surname) {
        for (int i = 0; i < size; i++) {
            if (toLower(employees[i].getSurname()) == toLower(surname)) {
                for (int j = i; j < size - 1; j++) {
                    employees[j] = employees[j + 1];
                }
                size--;
                return true;
            }
        }
        return false;
    }

    void find(const string& surname) const {
        for (int i = 0; i < size; i++) {
            if (toLower(employees[i].getSurname()) == toLower(surname)) {
                cout << employees[i] << endl;
            }
        }
    }

    void find(const string& position, bool byPosition) const {
        for (int i = 0; i < size; i++) {
            if (toLower(employees[i].getPosition()) == toLower(position)) {
                cout << employees[i] << endl;
            }
        }
    }

    void find(double minS, double maxS) const {
        if (minS > maxS) throw invalid_argument("minSalary > maxSalary");
        for (int i = 0; i < size; i++) {
            if (employees[i].getSalary() >= minS && employees[i].getSalary() <= maxS) {
                cout << employees[i] << endl;
            }
        }
    }

    void printAll() const {
        cout << "=== Список співробітників ===\n";
        for (int i = 0; i < size; i++) {
            cout << employees[i] << endl;
        }
        cout << "=============================\n";
    }

    // Додати премію по прізвищу
    bool addBonusBySurname(const string& surname, double bonus) {
        if (bonus < 0.0) throw invalid_argument("Bonus must be non-negative");
        for (int i = 0; i < size; ++i) {
            if (toLower(employees[i].getSurname()) == toLower(surname)) {
                employees[i] += bonus;
                return true;
            }
        }
        return false;
    }

    // Оператори
    Payroll& operator+=(const Employee& e) {
        addEmployee(e);
        return *this;
    }

    Payroll& operator-=(const string& surname) {
        if (!removeBySurname(surname)) {
            throw runtime_error("Employee not found: " + surname);
        }
        return *this;
    }

    friend Payroll operator+(Payroll p, const Employee& e) { p += e; return p; }
    friend Payroll operator-(Payroll p, const string& surname) { p -= surname; return p; }
};

#endif // ZARPLATA_H
