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
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void digitClicked();
    void dotClicked();
    void addClicked();
    void subtractClicked();
    void multiplyClicked();
    void divideClicked();
    void equalsClicked();
    void clearClicked();
    void changeSignClicked();
    void powClicked();
    void printDisplay();

private:
    Ui::Calculator *ui;
    double currentValue;
    double storedValue;
    int doubleDepth;
    QString pendingOperator;
};

#endif // CALCULATOR_H
