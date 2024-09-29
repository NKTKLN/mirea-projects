#include <memory>
#include <string>
#include <iostream>

using namespace std;

class MyExpression {
public:
    virtual int Calculate() const = 0;
    virtual string InLine() const = 0;
    virtual ~MyExpression() {}
};

using MyExpressionPtr = shared_ptr<MyExpression>;
 
class MyConstClass : public MyExpression {
public:
    int value;

    MyConstClass(int value);
    int Calculate() const override;
    string InLine() const override;
};

class MySumClass : public MyExpression {
public:
    MyExpressionPtr leftValue;
    MyExpressionPtr rightValue;

    MySumClass(MyExpressionPtr _leftValue, MyExpressionPtr _rightValue);
    int Calculate() const override;
    string InLine() const override;
};

class MyProductClass : public MyExpression {
public:
    MyExpressionPtr leftValue;
    MyExpressionPtr rightValue;

    MyProductClass(MyExpressionPtr _leftValue, MyExpressionPtr _rightValue);
    int Calculate() const override;
    string InLine() const override;
};



MyConstClass::MyConstClass(int _value) : value(_value) {}

int MyConstClass::Calculate() const { return value; }

string MyConstClass::InLine() const { return to_string(value); }

MySumClass::MySumClass(MyExpressionPtr _leftValue, MyExpressionPtr _rightValue) : 
    leftValue(move(_leftValue)), rightValue(move(_rightValue)) {}

int MySumClass::Calculate() const { return leftValue->Calculate() + rightValue->Calculate(); }

string MySumClass::InLine() const { return leftValue->InLine() + " + " + rightValue->InLine(); }

MyProductClass::MyProductClass(MyExpressionPtr _leftValue, MyExpressionPtr _rightValue) :
    leftValue(move(_leftValue)), rightValue(move(_rightValue)) {}

int MyProductClass::Calculate() const { return leftValue->Calculate() * rightValue->Calculate(); }

string MyProductClass::InLine() const {
    string right = rightValue->InLine();
    if (dynamic_cast<MySumClass*>(rightValue.get())) {
        right = "(" + rightValue->InLine() + ")";
    }

    return leftValue->InLine() + " * " + right; 
}

MyExpressionPtr MyConst(int value) {
    return make_shared<MyConstClass>(value);
}

MyExpressionPtr MyProduct(MyExpressionPtr left, MyExpressionPtr right) {
    return make_shared<MyProductClass>(move(left), move(right));
}

MyExpressionPtr MySum(MyExpressionPtr left, MyExpressionPtr right) {
    return make_shared<MySumClass>(move(left), move(right));
}

int main() {
    MyExpressionPtr myEx1 = MySum(MyProduct(MyConst(3), MyConst(4)), MyConst(5));
    cout << myEx1->InLine() << "\n";  // 3 * 4 + 5
    cout << myEx1->Calculate() << "\n";  // 17
 
    MyExpressionPtr myEx2 = MyProduct(MyConst(6), myEx1);
    cout << myEx2->InLine() << "\n";  // 6 * (3 * 4 + 5)
    cout << myEx2->Calculate() << "\n";  // 102
}
