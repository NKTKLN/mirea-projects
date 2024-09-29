#include <memory>
#include <iostream>

using namespace std;

int main() {
    double num;
    cin >> num;
    
    unique_ptr<double> ptr = make_unique<double>(num);
    cout << *ptr << endl;
    
    return 0;
}
