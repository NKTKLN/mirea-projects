#include <ctime>
#include <cmath>
#include <iostream>

using namespace std;

int main() {
    // srand(time(0));
    int n = rand() % 50;
    int *arr = new int[n];

    cout << "[ ";
    for (int index = 0; index < n; ++index) {
        arr[index] = rand() % 100;
        cout << arr[index] << " ";
    }
    cout << "] (" << n << ")" << endl;

    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;

    for (int index = 0; index < n; ++index) {
        if (arr[index] % 2 != 0) ++a;
        if (int(sqrt(arr[index])) == sqrt(arr[index]) && int(sqrt(arr[index])) % 2 == 0) ++b;
        if (arr[index] % 3 == 0 && arr[index] % 5 != 0) ++c;
        if ((2 ^ index) < arr[index] && arr[index] < tgamma(index + 1)) ++d;
        if (index + 1 < n && index - 1 >= 0 && arr[index] < (arr[index - 1] + arr[index + 1]) / 2) ++e;
        if (index % 2 == 1 && arr[index] % 2 != 0) ++f;
    }

    cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << endl;

    delete[] arr;
    return 0;
}
