#include <cmath>
#include <stdexcept>
#include "calculator.h"
#include "./ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator)
{
    ui->setupUi(this);
    connect(ui->buttonAdd, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(ui->buttonSubtract, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(ui->buttonMultiply, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(ui->buttonDivide, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(ui->buttonSin, &QPushButton::clicked, this, &Calculator::trigonometricOperationClicked);
    connect(ui->buttonCos, &QPushButton::clicked, this, &Calculator::trigonometricOperationClicked);
    connect(ui->buttonTan, &QPushButton::clicked, this, &Calculator::trigonometricOperationClicked);
    connect(ui->buttonCot, &QPushButton::clicked, this, &Calculator::trigonometricOperationClicked);
    connect(ui->buttonArcsin, &QPushButton::clicked, this, &Calculator::trigonometricOperationClicked);
    connect(ui->buttonArccos, &QPushButton::clicked, this, &Calculator::trigonometricOperationClicked);
    connect(ui->buttonArctan, &QPushButton::clicked, this, &Calculator::trigonometricOperationClicked);
}

Calculator::~Calculator()
{
    delete ui;
}

double Calculator::performOperation(double num1, double num2, const string &operation)
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
            throw invalid_argument("Деление на ноль.");
        }
        return num1 / num2;
    }
    throw invalid_argument("Неизвестная операция.");
}

double Calculator::validateTrigonometricInput(double value, const string &function)
{
    if (function == "ARCSIN" || function == "ARCCOS" || function == "ARCTAN")
    {
        if (value < -1 || value > 1)
        {
            throw invalid_argument("Ввод вне диапазона для arcsin/arccos/arctan.");
        }
    }
    return value;
}

double Calculator::convertToRadians(double value)
{
    return value * M_PI / 180.0;
}

double Calculator::convertToDegrees(double value)
{
    return value * 180.0 / M_PI;
}

bool Calculator::useRadians()
{
    return ui->radioButtonRadians->isChecked();
}

double Calculator::handleSpecialAngles(double value, const string &function)
{
    if (useRadians())
    {
        value = convertToDegrees(value);
    }

    if (fmod(value, 360.0) == 0.0)
    {
        if (function == "SIN") return 0.0;
        if (function == "COS") return 1.0;
        if (function == "TAN") return 0.0;
        if (function == "COT") throw invalid_argument("Котангенс не определен.");
    }
    else if (fmod(value, 90.0) == 0.0 && fmod(value, 180.0) != 0.0)
    {
        if (function == "SIN") return 1.0;
        if (function == "COS") return 0.0;
        if (function == "TAN") throw invalid_argument("Тангенс не определен.");
        if (function == "COT") return 0.0;
    }
    else if (fmod(value, 180.0) == 0.0)
    {
        if (function == "SIN") return 0.0;
        if (function == "COS") return -1.0;
        if (function == "TAN") return 0.0;
        if (function == "COT") throw invalid_argument("Котангенс не определен.");
    }
    else if (fmod(value, 270.0) == 0.0)
    {
        if (function == "SIN") return -1.0;
        if (function == "COS") return 0.0;
        if (function == "TAN") throw invalid_argument("Тангенс не определен.");
        if (function == "COT") return 0.0;
    }

    return nan("");
}

void Calculator::operationClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    string operation = clickedButton->text().toStdString();
    double num1 = ui->firstNumberInput->text().toDouble();
    double num2 = ui->secondNumberInput->text().toDouble();
    try
    {
        double result = performOperation(num1, num2, operation);

        if (std::isnan(result))
        {
            ui->plainTextEdit->setText("Не число (NaN).");
        }
        else if (std::isinf(result))
        {
            ui->plainTextEdit->setText("Бесконечность.");
        }
        else
        {
            ui->plainTextEdit->setText(QString::number(result));
        }
    }
    catch (const invalid_argument &e)
    {
        ui->plainTextEdit->setText(e.what());
    }
}

void Calculator::trigonometricOperationClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    string function = clickedButton->text().toStdString();
    double value = ui->firstNumberInput->text().toDouble();
    try
    {
        double specialValue = handleSpecialAngles(value, function);
        if (!std::isnan(specialValue))
        {
            ui->plainTextEdit->setText(QString::number(specialValue));
            return;
        }

        if (!useRadians() && function != "ARCSIN" && function != "ARCCOS" && function != "ARCTAN")
        {
            value = convertToRadians(value);
        }

        if (function == "SIN")
            value = sin(value);
        else if (function == "COS")
            value = cos(value);
        else if (function == "TAN")
        {
            if (fmod(value, M_PI / 2) == 0 && fmod(value, M_PI) != 0)
            {
                throw invalid_argument("Тангенс не определен.");
            }
            value = tan(value);
        }
        else if (function == "COT")
        {
            if (fmod(value, M_PI) == 0)
            {
                throw invalid_argument("Котангенс не определен.");
            }
            value = 1 / tan(value);
        }
        else if (function == "ARCSIN")
            value = asin(validateTrigonometricInput(value, function));
        else if (function == "ARCCOS")
            value = acos(validateTrigonometricInput(value, function));
        else if (function == "ARCTAN")
            value = atan(validateTrigonometricInput(value, function));
        else
            throw invalid_argument("Неизвестная тригонометрическая функция.");

        if (!useRadians() && (function == "ARCSIN" || function == "ARCCOS" || function == "ARCTAN"))
        {
            value = convertToDegrees(value);
        }

        if (std::isnan(value))
        {
            ui->plainTextEdit->setText("Не число (NaN).");
        }
        else if (std::isinf(value))
        {
            ui->plainTextEdit->setText("Бесконечность.");
        }
        else
        {
            ui->plainTextEdit->setText(QString::number(value));
        }
    }
    catch (const invalid_argument &e)
    {
        ui->plainTextEdit->setText(e.what());
    }
}
