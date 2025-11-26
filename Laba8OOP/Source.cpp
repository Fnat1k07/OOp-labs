#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <windows.h>

using namespace std;

void printRow(const vector<int>& row) {
    for (auto x : row) cout << x << " ";
    cout << endl;
}

int longestRunInRow(const vector<int>& row) {
    if (row.empty()) return 0;
    int maxRun = 1;
    int curRun = 1;
    for (size_t i = 1; i < row.size(); ++i) {
        if (row[i] == row[i - 1]) {
            ++curRun;
        }
        else {
            if (curRun > maxRun) maxRun = curRun;
            curRun = 1;
        }
    }
    if (curRun > maxRun) maxRun = curRun;
    return maxRun;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n, m;
    cout << "Введiть кiлькiсть рядкiв матрицi (n): ";
    if (!(cin >> n) || n <= 0) {
        cerr << "Невірний розмiр n" << endl;
        return 1;
    }
    cout << "Введiть кiлькiсть стовпчикiв матрицi (m): ";
    if (!(cin >> m) || m <= 0) {
        cerr << "Невірний розмiр m" << endl;
        return 1;
    }

    vector<vector<int>> matrix(n, vector<int>(m));

    cout << "\nВведiть елементи матрицi (пo рядках):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << "\nМатриця:\n";
    for_each(matrix.begin(), matrix.end(), printRow);

    int globalMaxRun = 0;
    int rowWithGlobalMax = -1;
    for (int i = 0; i < n; ++i) {
        int run = longestRunInRow(matrix[i]);
        if (run > globalMaxRun) {
            globalMaxRun = run;
            rowWithGlobalMax = i;
        }
    }

    if (rowWithGlobalMax == -1) {
        cout << "\nНе знайдено рядків або матриця порожня.\n";
    }
    else {
        cout << "\nНайдовша серiя однакових елементiв має довжину: " << globalMaxRun << endl;
        cout << "Рядок з найдовшою серiєю: " << (rowWithGlobalMax + 1) << " (нумерацiя з 1)" << endl;

        cout << "Вмiст цього рядка: ";
        for (auto x : matrix[rowWithGlobalMax]) cout << x << " ";
        cout << endl;
    }

    system("pause");
    return 0;
}
