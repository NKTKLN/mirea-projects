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
    connect(ui->loadDataButton, &QPushButton::clicked, this, &UserForm::loadData);
    connect(ui->radioButtonF, &QRadioButton::clicked, this, &UserForm::fIcon);
    connect(ui->radioButtonM, &QRadioButton::clicked, this, &UserForm::mIcon);

    ui->labelF->hide();
    ui->labelM->hide();
}

UserForm::~UserForm()
{
    delete ui;
}

void UserForm::fIcon()
{
    ui->labelM->hide();
    ui->labelF->show();
}

void UserForm::mIcon()
{
    ui->labelM->show();
    ui->labelF->hide();
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

    QString qtFileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Binary Files (*.bin)");
    if (qtFileName.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Неверный файл.");
        return;
    }

    string fileName = qtFileName.toStdString();
    string extension = ".bin";
    if (fileName.length() < extension.length() || fileName.compare(fileName.length() - extension.length(), extension.length(), extension) != 0) {
        fileName += extension;
    }

    QFile confFile(QString::fromStdString(fileName));
    if (!confFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, "Ошибка", "Проблемы с записью файла.");
        return;
    }

    QDataStream dataStream(&confFile);
    dataStream << username
                << fullName
                << QString::fromStdString(isMale ? "M" : "F")
                << passport
                << dob
                << phoneNumber
                << email;
    confFile.close();

    ostringstream messageStream;
    messageStream << "Вы успешно зарегистрировали аккаунт " << username.toStdString()
                  << ".\nВаше имя: " << fullNameMatch.captured(2).toStdString()
                  << ", ваша фамилия: " << fullNameMatch.captured(1).toStdString()
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
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Binary Files (*.bin);;All Files (*)");
    if (fileName.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Неверный файл.");
        return;
    }

    QFile confFile(fileName);
    if (!confFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Ошибка", "Проблемы с чтением файла.");
        return;
    }

    QDataStream dataStream(&confFile);

    QString username, fullName, gend, passport, dob, phoneNumber, email;

    dataStream >> username;
    dataStream >> fullName;
    dataStream >> gend;
    dataStream >> passport;
    dataStream >> dob;
    dataStream >> phoneNumber;
    dataStream >> email;

    if (gend == "M") mIcon();
    else fIcon();

    ui->username->setText(username);
    ui->fullName->setText(fullName);
    ui->radioButtonM->setChecked(gend == "M");
    ui->radioButtonF->setChecked(gend == "F");
    ui->passport->setText(passport);
    ui->dob->setText(dob);
    ui->phone->setText(phoneNumber);
    ui->email->setText(email);

    confFile.close();
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
