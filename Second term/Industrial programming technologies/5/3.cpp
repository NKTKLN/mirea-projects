#include <vector>
#include <iostream>

using namespace std;

int main() {
    int A, B, C;
    cin >> A >> B >> C;

    vector<long long> bibo(C);
    bibo[0] = A;
    bibo[1] = B;
    for(int index = 2; index < C; index++)
        bibo[index] = bibo[index-1] * bibo[index-2];

    cout << bibo[C-1] << endl;

    return 0;
}
