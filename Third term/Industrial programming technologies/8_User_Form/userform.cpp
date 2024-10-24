#include "userform.h"
#include "./ui_userform.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <sstream>
#include <QJsonDocument>
#include <QJsonObject>

using namespace std;

UserForm::UserForm(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::UserForm)
{
    ui->setupUi(this);

    connect(ui->registButton, &QPushButton::clicked, this, &UserForm::registration);
    connect(ui->loadDataButton, &QPushButton::clicked, this, &UserForm::loadData);
}

UserForm::~UserForm()
{
    delete ui;
}

void UserForm::registration()
{
    QString username = ui->username->text();
    QString fullName = ui->fullName->text();
    bool isMale = ui->radioButtonM->isChecked();
    bool isFemale = ui->radioButtonF->isChecked();
    QString passport = ui->passport->text();
    QString dob = ui->dob->text();
    QString phoneNumber = ui->phone->text();
    QString email = ui->email->text();

    QRegularExpression usernamePattern("^[a-zA-Z0-9]{3,15}$");
    QRegularExpressionMatch usernameMatch = usernamePattern.match(username);
    if (!usernameMatch.hasMatch())
    {
        QMessageBox::warning(this, "Ошибка", "Неверное имя пользователя.");
        return;
    }

    QRegularExpression fullNamePattern("^([А-Я][а-я]{3,14}) ([А-Я][а-я]{3,14}) ([А-Я][а-я]{3,14})$");
    QRegularExpressionMatch fullNameMatch = fullNamePattern.match(fullName);
    if (!fullNameMatch.hasMatch())
    {
        QMessageBox::warning(this, "Ошибка", "Неверное ФИО.");
        return;
    }

    if (!(isMale || isFemale))
    {
        QMessageBox::warning(this, "Ошибка", "Неверный пол.");
        return;
    }

    QRegularExpression passportPattern("^(\\d{4}) (\\d{6})$");
    QRegularExpressionMatch passportMatch = passportPattern.match(passport);
    if (!passportMatch.hasMatch())
    {
        QMessageBox::warning(this, "Ошибка", "Неверный номер паспорта.");
        return;
    }

    QRegularExpression dobPattern("^(0[1-9]|[12][0-9]|3[01])\\.(0[1-9]|1[0-2])\\.(\\d{4})$");
    QRegularExpressionMatch dobMatch = dobPattern.match(dob);
    if (!dobMatch.hasMatch() || !isValidDate(dobMatch.captured(1).toInt(), dobMatch.captured(2).toInt(), dobMatch.captured(3).toInt()))
    {
        QMessageBox::warning(this, "Ошибка", "Неверная дата рождения.");
        return;
    }

    QRegularExpression phonePattern("^\\+7-\\d{3}-\\d{3}-\\d{2}-\\d{2}$");
    QRegularExpressionMatch phoneMatch = phonePattern.match(phoneNumber);
    if (!phoneMatch.hasMatch())
    {
        QMessageBox::warning(this, "Ошибка", "Неверный номер телефона.");
        return;
    }

    QRegularExpression emailPattern("^[a-zA-Z0-9._%+-]{1,20}@[a-zA-Z0-9-]+\\.[a-zA-Z]{2,}$");
    QRegularExpressionMatch emailMatch = emailPattern.match(email);
    if (!emailMatch.hasMatch())
    {
        QMessageBox::warning(this, "Ошибка", "Неверный e-mail.");
        return;
    }

    QString qtFileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "JSON (*.json)");
    if (qtFileName.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Неверный файл.");
        return;
    }

    string fileName = qtFileName.toStdString();
    string extension = ".json";
    if (fileName.length() < extension.length() || fileName.compare(fileName.length() - extension.length(), extension.length(), extension) != 0) {
        fileName += extension;
    }

    QFile confFile(QString::fromStdString(fileName));
    if (!confFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, "Ошибка", "Проблемы с записью файла.");
        return;
    }

    QJsonObject jsonObject;

    jsonObject["username"] = username;
    jsonObject["full_name"] = fullName;
    jsonObject["is_male"] = isMale;
    jsonObject["passport"] = passport;
    jsonObject["dob"] = dob;
    jsonObject["phone"] = phoneNumber;
    jsonObject["email"] = email;

    QJsonDocument jsonDoc(jsonObject);

    confFile.write(jsonDoc.toJson());
    confFile.close();

    ostringstream messageStream;
    messageStream << "Вы успешно зарегистрировали аккаунт " << username.toStdString()
                  << ".\nВаше имя: " << fullNameMatch.captured(1).toStdString()
                  << ", ваша фамилия: " << fullNameMatch.captured(2).toStdString()
                  << ", ваше отчество: " << fullNameMatch.captured(3).toStdString()
                  << ".\nВаш пол: " << (isMale ? "Мужской" : "Женский")
                  << ".\nСерия Вашего паспорта: " << passportMatch.captured(1).toStdString()
                  << ", номер: " << passportMatch.captured(2).toStdString()
                  << ".\nВы родились " << dobMatch.captured(1).toStdString()
                  << " " << dobMatch.captured(2).toStdString()
                  << " " << dobMatch.captured(3).toStdString()
                  << ".\nВаш номер телефона: " << phoneNumber.toStdString()
                  << ".\nВаш e-mail: " << email.toStdString()
                  << ".\nСпасибо за регистрацию.";

    QMessageBox::information(this, "Регистрация", QString::fromStdString(messageStream.str()));
}

void UserForm::loadData()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "JSON Files (*.json);;All Files (*)");
    if (fileName.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Неверный файл.");
        return;
    }

    QFile confFile(fileName);
    if (!confFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Ошибка", "Проблемы с чтением файла.");
        return;
    }

    QString jsonData = confFile.readAll();
    confFile.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData.toUtf8());
    if (jsonDoc.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Файл JSON некорректный.");
        return;
    }

    QJsonObject jsonObject = jsonDoc.object();

    QString username = jsonObject["username"].toString();
    QString fullName = jsonObject["full_name"].toString();
    bool isMale = jsonObject["is_male"].toBool();
    QString passport = jsonObject["passport"].toString();
    QString dob = jsonObject["dob"].toString();
    QString phoneNumber = jsonObject["phone"].toString();
    QString email = jsonObject["email"].toString();

    ui->username->setText(username);
    ui->fullName->setText(fullName);
    ui->radioButtonM->setChecked(isMale);
    ui->radioButtonF->setChecked(!isMale);
    ui->passport->setText(passport);
    ui->dob->setText(dob);
    ui->phone->setText(phoneNumber);
    ui->email->setText(email);
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
