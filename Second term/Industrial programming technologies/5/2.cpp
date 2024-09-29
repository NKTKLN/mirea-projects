#include <memory>
#include <numeric>
#include <iostream>

using namespace std;

int main() {
    int size;
    cin >> size;

    unique_ptr<double[]> arr(new double[size]);
    for(int index = 0; index < size; index++)
        arr[index] = index + 1;
    
    double sum = accumulate(arr.get(), arr.get()+size, 0.0);
    cout << sum << endl;

    return 0;
}
