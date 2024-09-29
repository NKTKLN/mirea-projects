#include <string>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "calculator.h"
#include "./ui_calculator.h"

using namespace std;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator)
{
    ui->setupUi(this);

    connect(ui->buttonAdd, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(ui->buttonSubtract, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(ui->buttonMultiply, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(ui->buttonDivide, &QPushButton::clicked, this, &Calculator::operationClicked);
}

Calculator::~Calculator()
{
    delete ui;
}

long double Calculator::convertToDecimal(const string &number, int base)
{
    long double result = 0;
    size_t pointPos = number.find('.');
    bool isNegative = (number[0] == '-');

    string integerPart = (isNegative) ? number.substr(1, pointPos - 1) : number.substr(0, pointPos);

    for (char digit : integerPart)
    {
        if (digit == '-')
            continue;
        int value = isdigit(digit) ? digit - '0' : tolower(digit) - 'a' + 10;
        if (value >= base)
        {
            throw invalid_argument("Invalid character for this number system.");
        }
        result = result * base + value;
    }

    if (pointPos != string::npos)
    {
        string fractionalPart = number.substr(pointPos + 1);
        long double fractionValue = 0;
        long double divisor = 1;
        for (char digit : fractionalPart)
        {
            int value = isdigit(digit) ? digit - '0' : tolower(digit) - 'a' + 10;
            if (value >= base)
            {
                throw invalid_argument("Invalid character for this number system.");
            }
            divisor *= base;
            fractionValue += value / divisor;
        }
        result += fractionValue;
    }

    return isNegative ? -result : result;
}

string Calculator::convertFromDecimal(long double number, int base)
{
    if (number == 0)
        return "0";

    bool isNegative = (number < 0);
    number = abs(number);

    long long integerPart = static_cast<long long>(number);
    string result;
    while (integerPart > 0)
    {
        int remainder = integerPart % base;
        result += (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'a');
        integerPart /= base;
    }

    if (result.empty())
        result = "0";

    reverse(result.begin(), result.end());

    long double fractionalPart = number - static_cast<long long>(number);
    if (fractionalPart > 0)
    {
        result += '.';
        for (int i = 0; i < 10 && fractionalPart > 0; ++i)
        {
            fractionalPart *= base;
            int fracInteger = static_cast<int>(fractionalPart);
            result += (fracInteger < 10) ? (fracInteger + '0') : (fracInteger - 10 + 'a');
            fractionalPart -= fracInteger;
        }
    }

    return isNegative ? "-" + result : result;
}

long double Calculator::performOperation(long double num1, long double num2, const string &operation)
{
    if (operation == "+")
        return num1 + num2;
    if (operation == "-")
        return num1 - num2;
    if (operation == "*")
        return num1 * num2;
    if (operation == "/")
    {
        if (num2 == 0)
        {
            throw invalid_argument("Division by zero.");
        }
        return num1 / num2;
    }
    throw invalid_argument("Unknown operation.");
}

void Calculator::operationClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    string operation = clickedButton->text().toStdString();

    string num1 = ui->firstNumberInput->text().toStdString();
    string num2 = ui->secondNumberInput->text().toStdString();
    int base1 = ui->firstNumberSystem->value();
    int base2 = ui->secondNumberSystem->value();
    int resultBase = ui->outNumberSystem->value();

    try
    {
        long double decimalNum1 = convertToDecimal(num1, base1);
        long double decimalNum2 = convertToDecimal(num2, base2);
        long double result = performOperation(decimalNum1, decimalNum2, operation);

        string resultStr = convertFromDecimal(result, resultBase);

        ui->plainTextEdit->setText(QString::fromStdString(resultStr));
    }
    catch (const invalid_argument &e)
    {
        ui->plainTextEdit->setText(e.what());
    }
}
