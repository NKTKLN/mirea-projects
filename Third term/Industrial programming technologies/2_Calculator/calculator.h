#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void operationClicked();

private:
    Ui::Calculator *ui;

    long double convertToDecimal(const std::string &number, int base);
    std::string convertFromDecimal(long double number, int base);
    long double performOperation(long double num1, long double num2, const std::string &operation);
};

#endif // CALCULATOR_H
