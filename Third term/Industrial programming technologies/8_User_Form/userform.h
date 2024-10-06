#ifndef USERFORM_H
#define USERFORM_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class UserForm;
}
QT_END_NAMESPACE

class UserForm : public QMainWindow
{
    Q_OBJECT

public:
    UserForm(QWidget *parent = nullptr);
    ~UserForm();

private slots:
    void registration();
    void loadData();

private:
    Ui::UserForm *ui;
    bool isValidDate(int day, int month, int year);
};
#endif // USERFORM_H
