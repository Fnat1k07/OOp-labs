#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

int main() {
    setlocale(LC_ALL, "Ukr");
    srand(time(0));

    double mu, eta;      // імовірності
    int steps = 1000;    // кількість кроків у одній симуляції
    int experiments = 100; // кількість експериментів для усереднення

    cout << "Введіть імовірність додавання (μ, від 0 до 1): ";
    cin >> mu;
    cout << "Введіть імовірність видалення (η, від 0 до 1): ";
    cin >> eta;

    if (mu < 0 || mu > 1 || eta < 0 || eta > 1) {
        cerr << "Помилка: імовірності мають бути у межах [0, 1]" << endl;
        return 1;
    }

    double avgMaxSize = 0.0; // середній максимальний розмір стеку

    for (int exp = 0; exp < experiments; exp++) {
        stack<int> st;
        int maxSize = 0;

        for (int i = 0; i < steps; i++) {
            double r = (double)rand() / RAND_MAX; // випадкове число [0,1)

            if (r < mu) {
                // додаємо елемент
                st.push(rand() % 100);
            }
            else if (r < mu + eta && !st.empty()) {
                // видаляємо елемент
                st.pop();
            }

            if ((int)st.size() > maxSize)
                maxSize = st.size();
        }

        avgMaxSize += maxSize;
    }

    avgMaxSize /= experiments;

    cout << fixed << setprecision(2);
    cout << "\nСередній максимально необхідний розмір стека: " << avgMaxSize << endl;

    return 0;
}
