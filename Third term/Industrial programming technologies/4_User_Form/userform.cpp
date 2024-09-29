#include "userform.h"
#include "./ui_userform.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <sstream>

using namespace std;

UserForm::UserForm(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::UserForm)
{
    ui->setupUi(this);

    connect(ui->registButton, &QPushButton::clicked, this, &UserForm::registration);
}

UserForm::~UserForm()
{
    delete ui;
}

void UserForm::registration() {
    QString username = ui->username->text();
    QString fullName = ui->fullName->text();
    bool isMale = ui->radioButtonM->isChecked();
    bool isFemale = ui->radioButtonF->isChecked();
    QString passport = ui->passport->text();
    QString dob = ui->dob->text();
    QString phoneNumber = ui->phone->text();
    QString email = ui->email->text();

    if (username.length() < 3 || username.length() > 15 || !username.toStdString().find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")) {
        QMessageBox::warning(this, "Ошибка", "Неверное имя пользователя.");
        return;
    }

    QStringList fullNameParts = fullName.split(" ");
    if (fullNameParts.size() != 3 || !isCorrectName(fullNameParts[0]) || !isCorrectName(fullNameParts[1]) || !isCorrectName(fullNameParts[2])) {
        QMessageBox::warning(this, "Ошибка", "Неверное ФИО.");
        return;
    }

    if (!(isMale || isFemale)) {
        QMessageBox::warning(this, "Ошибка", "Неверный пол.");
        return;
    }

    QStringList passportParts = passport.split(" ");
    if (passportParts.size() != 2 || passportParts[0].length() != 4 || passportParts[1].length() != 6 || !passportParts[0].toStdString().find_first_not_of("0123456789") || !passportParts[1].toStdString().find_first_not_of("0123456789")) {
        QMessageBox::warning(this, "Ошибка", "Неверный номер паспорта.");
        return;
    }

    QStringList dobParts = dob.split(".");
    if (dobParts.size() != 3 || !isValidDate(dobParts[0].toInt(), dobParts[1].toInt(), dobParts[2].toInt())) {
        QMessageBox::warning(this, "Ошибка", "Неверная дата рождения.");
        return;
    }

    if (phoneNumber.length() != 16 || !phoneNumber.startsWith("+7-") || phoneNumber.mid(3).toStdString().find_first_not_of("0123456789-") != std::string::npos) {
        QMessageBox::warning(this, "Ошибка", "Неверный номер телефона.");
        return;
    }

    if (!email.contains('@') || !email.contains('.') || email.split('@')[0].length() < 1 || email.split('.')[1].length() < 1 || email.split('@')[1].split('.')[0] < 1) {
        QMessageBox::warning(this, "Ошибка", "Неверный e-mail.");
        return;
    }

    ostringstream messageStream;
    messageStream << "Вы успешно зарегистрировали аккаунт " << username.toStdString()
                  << ".\nВаше имя: " << fullNameParts[1].toStdString()
                  << ", ваша фамилия: " << fullNameParts[2].toStdString()
                  << ", ваше отчество: " << fullNameParts[2].toStdString()
                  << ".\nВаш пол: " << (isMale ? "Мужской" : "Женский")
                  << ".\nСерия Вашего паспорта: " << passportParts[0].toStdString()
                  << ", номер: " << passportParts[1].toStdString()
                  << ".\nВы родились " << dobParts[0].toStdString()
                  << "." << dobParts[1].toStdString()
                  << "." << dobParts[2].toStdString()
                  << ".\nВаш номер телефона: " << phoneNumber.toStdString()
                  << ".\nВаш e-mail: " << email.toStdString()
                  << ".\nСпасибо за регистрацию.";

    QMessageBox::information(this, "Регистрация", QString::fromStdString(messageStream.str()));
}

bool UserForm::isCorrectName(const QString &name) {
    if (name.length() < 3 || name.length() > 14) {
        return false;
    }
    if (!name[0].isUpper() || name.mid(0).toStdString().find_first_not_of("йцукенгшщзхфывапролджэячсмитьбюъЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬ") != std::string::npos) {
        return false;
    }
    return true;
}

bool UserForm::isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12 || day < 1) {
        return false;
    }

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
        daysInMonth[1] = 29;
    }

    return day <= daysInMonth[month - 1];
}
