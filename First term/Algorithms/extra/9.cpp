#include <stack>
#include <fstream>
#include <iostream> 

using namespace std;

int main() {
	stack<char> stack;
    ifstream inputFile("input.txt");
    
    if (inputFile.is_open()) {
        while (inputFile) {
            stack.push(inputFile.get());
        }
    }
    stack.pop();

	while (!stack.empty()) {
		cout << char(stack.top());
		stack.pop();
    }

    return 0;
}
