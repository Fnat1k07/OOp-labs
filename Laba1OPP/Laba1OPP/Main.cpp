#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// b(x,y,z)
double vurazB(double x, double y, double z) {
    double diya1 = 1 - x / 1.0 + (y * y) / 6.0 + pow(z, 3) / 120.0;
    double diya2 = pow(sin(x - z), 2) / (pow(fabs(y), 1.23) + z);
    return diya1 + diya2;
}

// a(x,y,z,b)
double vurazA(double x, double y, double z, double b) {
    double diya3 = 2 * cos(pow(fabs(x * x - b / 6.0), 1.0 / 3.0));
    double diya4 = 1 + x * b + pow(sin(pow(y, 3)), 2);
    double diya5 = pow(log(fabs((x + 1) / z)), 3);
    return diya3 / diya4 + diya5;
}

int main() {
    setlocale(LC_ALL, "ukr");
    
    double x = 0.48 * 12;
    double y = 0.47 * 12;
    double z = -1.32 * 12;

    cout << "Завдання 1:\n";
    double b = vurazB(x, y, z);
    double a1 = vurazA(x, y, z, b);
    cout << "a = " << a1 << "\n";
    cout << "b = " << b << "\n\n";

    
    double xp = -1.0, xk = 1.0, dx = 0.2;

    cout << fixed << setprecision(4);
    cout << "   x\t\t   a(x,y,z,b)\t\t   b(x,y,z)\n";
    cout << "---------------------------------------------\n";

    for (double x = xp; x < xk; x += dx) {
        if (fabs(x) < 1e-9) x = 0.0;
        double b = vurazB(x, y, z);
        double a = vurazA(x, y, z, b);
        cout << x << "\t" << a << "\t" << b << endl;
    }


    return 0;
}
