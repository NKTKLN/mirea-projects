#include <cmath>
#include "calculator.h"
#include "./ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
    , currentValue(0)
    , storedValue(0)
    , doubleDepth(0)
{
    ui->setupUi(this);

    connect(ui->button0, &QPushButton::clicked, this, &Calculator::digitClicked);
    connect(ui->button1, &QPushButton::clicked, this, &Calculator::digitClicked);
    connect(ui->button2, &QPushButton::clicked, this, &Calculator::digitClicked);
    connect(ui->button3, &QPushButton::clicked, this, &Calculator::digitClicked);
    connect(ui->button4, &QPushButton::clicked, this, &Calculator::digitClicked);
    connect(ui->button5, &QPushButton::clicked, this, &Calculator::digitClicked);
    connect(ui->button6, &QPushButton::clicked, this, &Calculator::digitClicked);
    connect(ui->button7, &QPushButton::clicked, this, &Calculator::digitClicked);
    connect(ui->button8, &QPushButton::clicked, this, &Calculator::digitClicked);
    connect(ui->button9, &QPushButton::clicked, this, &Calculator::digitClicked);
    connect(ui->buttonDot, &QPushButton::clicked, this, &Calculator::dotClicked);

    connect(ui->buttonAdd, &QPushButton::clicked, this, &Calculator::addClicked);
    connect(ui->buttonSubtract, &QPushButton::clicked, this, &Calculator::subtractClicked);
    connect(ui->buttonMultiply, &QPushButton::clicked, this, &Calculator::multiplyClicked);
    connect(ui->buttonDivide, &QPushButton::clicked, this, &Calculator::divideClicked);
    connect(ui->buttonEquals, &QPushButton::clicked, this, &Calculator::equalsClicked);
    connect(ui->buttonClear, &QPushButton::clicked, this, &Calculator::clearClicked);
    connect(ui->buttonChangeSign, &QPushButton::clicked, this, &Calculator::changeSignClicked);
    connect(ui->buttonPow, &QPushButton::clicked, this, &Calculator::powClicked);
}

Calculator::~Calculator()
{
    delete ui;
}


void Calculator::printDisplay()
{
    if (pendingOperator == "") {
        ui->display->setText(QString::number(currentValue));
    } else {
        QString out;

        if (storedValue < 0) {
            out += "(" + QString::number(storedValue) + ")";
        } else {
            out += QString::number(storedValue);
        }

        out += pendingOperator;

        if (currentValue < 0) {
            out += "(" + QString::number(currentValue) + ")";
        } else {
            out += QString::number(currentValue);
        }

        ui->display->setText(out);
    }
}

void Calculator::digitClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (currentValue < 0) digitValue *= -1;
    if (doubleDepth != 0) {
        currentValue += digitValue * std::pow(0.1, doubleDepth);
        doubleDepth++;
    } else {
        currentValue = currentValue * 10 + digitValue;
    }
    printDisplay();
}

void Calculator::dotClicked() {
    doubleDepth = 1;
    ui->display->setText(QString::number(currentValue));
}

void Calculator::addClicked()
{
    storedValue = currentValue;
    currentValue = 0;
    doubleDepth = 0;
    pendingOperator = "+";
    printDisplay();
}

void Calculator::subtractClicked()
{
    storedValue = currentValue;
    currentValue = 0;
    doubleDepth = 0;
    pendingOperator = "-";
    printDisplay();
}

void Calculator::multiplyClicked()
{
    storedValue = currentValue;
    currentValue = 0;
    doubleDepth = 0;
    pendingOperator = "*";
    printDisplay();
}

void Calculator::divideClicked()
{
    storedValue = currentValue;
    currentValue = 0;
    doubleDepth = 0;
    pendingOperator = "/";
    printDisplay();
}

void Calculator::powClicked()
{
    storedValue = currentValue;
    currentValue = 0;
    doubleDepth = 0;
    pendingOperator = "^";
    printDisplay();
}

void Calculator::equalsClicked()
{
    if (pendingOperator == "+") {
        currentValue = storedValue + currentValue;
    } else if (pendingOperator == "-") {
        currentValue = storedValue - currentValue;
    } else if (pendingOperator == "*") {
        currentValue = storedValue * currentValue;
    } else if (pendingOperator == "/") {
        if (currentValue != 0) {
            currentValue = storedValue / currentValue;
        } else {
            ui->display->setText("Error");
            return;
        }
    } else if (pendingOperator == "^") {
        if (currentValue != 0) {
            currentValue = std::pow(storedValue, currentValue);
        } else {
            ui->display->setText("Error");
            return;
        }
    }

    pendingOperator = "";
    printDisplay();
}

void Calculator::clearClicked()
{
    currentValue = 0;
    storedValue = 0;
    pendingOperator = "";
    printDisplay();
}

void Calculator::changeSignClicked()
{
    currentValue *= -1;
    printDisplay();
}
