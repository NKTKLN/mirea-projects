#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <string>

using namespace std;

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
    void trigonometricOperationClicked();

private:
    Ui::Calculator *ui;
    double performOperation(double num1, double num2, const string &operation);
    double validateTrigonometricInput(double value, const string &function);
    double convertToRadians(double value);
    double convertToDegrees(double value);
    bool useRadians();
    double handleSpecialAngles(double value, const string &function);
};

#endif // CALCULATOR_H
