#include "tables.h"
#include "./ui_tables.h"
#include <time.h>
#include <cstdlib>
#include <algorithm>
#include <QMessageBox>
#include <QRegularExpression>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFileDialog>

using namespace std;

Tables::Tables(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Tables)
{
    ui->setupUi(this);

    connect(ui->tableWidget, &QTableWidget::cellChanged, this, &Tables::tableCellChanged);
    connect(ui->setRowsButton, &QPushButton::clicked, this, &Tables::setRowsClicked);
    connect(ui->setRandomDataButton, &QPushButton::clicked, this, &Tables::setRandomDataClicked);
    connect(ui->minButton, &QPushButton::clicked, this, &Tables::minClicked);
    connect(ui->avgButton, &QPushButton::clicked, this, &Tables::avgClicked);
    connect(ui->maxButton, &QPushButton::clicked, this, &Tables::maxClicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &Tables::searchClicked);
    connect(ui->sortButton, &QPushButton::clicked, this, &Tables::sortClicked);
    connect(ui->loadButton, &QPushButton::clicked, this, &Tables::loadDataFromJson);
    connect(ui->saveButton, &QPushButton::clicked, this, &Tables::saveDataToJson);

    ui->tableWidget->setColumnCount(6);
    QStringList headers = {"ID", "Фамилия", "Имя", "Отчество", "Телефон", "Email"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
}

Tables::~Tables()
{
    delete ui;
}

void Tables::tableCellChanged(int row, int column)
{
    QTableWidgetItem *item = ui->tableWidget->item(row, column);
    QString cellData = item->text();

    if (!dataMap.contains(row))
    {
        dataMap[row] = QMap<QString, QString>();
    }

    if (column == 0)
    {
        QRegularExpression pattern("\\d+");
        if (!pattern.match(cellData).hasMatch())
        {
            QMessageBox::warning(this, "Ошибка", "Некорректный id.");
            if (dataMap[row]["id"] == "") {
                dataMap[row]["id"] = "0";
            }
            item->setText(dataMap[row]["id"]);
        }
        else
        {
            dataMap[row]["id"] = cellData;
        }
    }
    if (column == 1)
    {
        QRegularExpression pattern("[А-Я][а-я]{3,14}");
        if (!pattern.match(cellData).hasMatch())
        {
            QMessageBox::warning(this, "Ошибка", "Некорректная фамилия.");
            if (dataMap[row]["surname"] == "") {
                dataMap[row]["surname"] = "Иванов";
            }
            item->setText(dataMap[row]["surname"]);
        }
        else
        {
            dataMap[row]["surname"] = cellData;
        }
    }
    if (column == 2)
    {
        QRegularExpression pattern("[А-Я][а-я]{3,14}");
        if (!pattern.match(cellData).hasMatch())
        {
            QMessageBox::warning(this, "Ошибка", "Некорректное имя.");
            if (dataMap[row]["name"] == "") {
                dataMap[row]["name"] = "Иван";
            }
            item->setText(dataMap[row]["name"]);
        }
        else
        {
            dataMap[row]["name"] = cellData;
        }
    }
    if (column == 3)
    {
        QRegularExpression pattern("[А-Я][а-я]{3,14}");
        if (!pattern.match(cellData).hasMatch() && cellData != "")
        {
            QMessageBox::warning(this, "Ошибка", "Некорректное отчество.");
            item->setText(dataMap[row]["patronymic"]);
        }
        else
        {
            dataMap[row]["patronymic"] = cellData;
        }
    }
    if (column == 4)
    {
        QRegularExpression pattern("\\+7-\\d{3}-\\d{3}-\\d{2}-\\d{2}");
        if (!pattern.match(cellData).hasMatch() && cellData != "")
        {
            QMessageBox::warning(this, "Ошибка", "Некорректный номер телефона.");
            item->setText(dataMap[row]["phone"]);
        }
        else
        {
            dataMap[row]["phone"] = cellData;
        }
    }
    if (column == 5)
    {
        QRegularExpression pattern("^[a-zA-Z0-9._%+-]{1,20}@[a-zA-Z0-9-]+\\.[a-zA-Z]{2,}$");
        if (!pattern.match(cellData).hasMatch() && cellData != "")
        {
            QMessageBox::warning(this, "Ошибка", "Некорректный адрес электронной почты.");
            item->setText(dataMap[row]["email"]);
        }
        else
        {
            dataMap[row]["email"] = cellData;
        }
    }
}

void Tables::setRowsClicked()
{
    QString rawRowsCount = ui->rowsCountInput->text();
    QRegularExpression rowsCountPattern("\\d+");
    QRegularExpressionMatch rowsCountMatch = rowsCountPattern.match(rawRowsCount);
    if (!rowsCountMatch.hasMatch())
    {
        QMessageBox::warning(this, "Ошибка", "Неверное число строк.");
        return;
    }
    int rowsCount = rawRowsCount.toInt();
    ui->tableWidget->setRowCount(rowsCount);
    ui->tableWidget->setColumnCount(6);
    for (int i = 0; i < rowsCount; i++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(i, 0);
        if (item == nullptr)
        {
            item = new QTableWidgetItem(QString::number(i + 1));
            ui->tableWidget->setItem(i, 0, item);
        }
    }
}

void Tables::setRandomDataClicked()
{
    srand(time(0));
    QStringList firstNames = {
        "Никита", "Александр", "Виктор", "Даниил", "Артем",
        "Дмитрий", "Иван", "Максим", "Роман", "Сергей",
        "Михаил", "Андрей", "Тимур", "Константин", "Станислав",
        "Алексей", "Юрий", "Павел", "Олег", "Евгений"};
    QStringList lastNames = {
        "Абрамов", "Иванов", "Дроздов", "Гусевский", "Петров",
        "Сидоров", "Кузнецов", "Смирнов", "Лебедев", "Морозов",
        "Николаев", "Попов", "Федоров", "Сухов", "Орлов",
        "Захаров", "Васильев", "Малышев", "Ковалев", "Зуев"};
    QStringList patronymics = {
        "Иванович", "Викторович", "Александрович", "Даниилович", "Артемович",
        "Дмитриевич", "Ивановна", "Максимович", "Романович", "Сергеевич",
        "Михайлович", "Андреевич", "Тимурович", "Константинович", "Станиславович",
        "Алексеевич", "Юрьевич", "Павлович", "Олегович", ""};
    QStringList emails = {
        "test1", "test2", "test3", "test4", "user1",
        "user2", "user3", "user4", "name1", "name2",
        "example1", "example2", "sample1", "sample2", "demo1",
        "demo2", "info1", "info2", "contact1", "contact2"};
    QStringList domains = {
        "gmail.com", "yahoo.com", "example.com", "hotmail.com", "mail.ru",
        "yandex.ru", "outlook.com", "icloud.com", "live.com", "protonmail.com",
        "zoho.com", "aol.com", "fastmail.com", "gmx.com", "tutanota.com",
        "inbox.ru", "rambler.ru", "bk.ru", "mail.com", "hushmail.com"};

    int rows = ui->tableWidget->rowCount();
    for (int i = 0; i < rows; ++i)
    {
        QString fullName = lastNames[rand() % lastNames.size()] + " " +
                           firstNames[rand() % firstNames.size()] + " " +
                           patronymics[rand() % patronymics.size()];
        QString phone = QString::fromStdString("+7-" + std::to_string(rand() % 100 + 900) + "-" +
                                               std::to_string(rand() % 900 + 100) + "-" +
                                               std::to_string(rand() % 90 + 10) + "-" +
                                               std::to_string(rand() % 90 + 10));
        QString email = emails[rand() % emails.size()].toLower() + "@" +
                        domains[rand() % domains.size()];

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(lastNames[rand() % lastNames.size()]));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(firstNames[rand() % firstNames.size()]));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(patronymics[rand() % patronymics.size()]));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(phone));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(email));
    }
}

void Tables::minClicked()
{
    if (ui->tableWidget->rowCount() == 0)
    {
        QMessageBox::warning(this, "Минимум", "Таблица пустая.");
        return;
    }

    int minSum = 999;
    QStringList minRows;

    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        QString phone = ui->tableWidget->item(i, 4)->text();
        int sum = 0;

        for (QChar digit : phone)
        {
            if (digit.isDigit())
            {
                sum += digit.digitValue();
            }
        }

        if (sum < minSum)
        {
            minSum = sum;
            minRows.clear();
            minRows.append(QString::number(i + 1));
        }
        else if (sum == minSum)
        {
            minRows.append(QString::number(i + 1));
        }
    }

    QString minRowsString = minRows.join(", ");
    QMessageBox::information(this, "Минимум", "Строки с минимальной суммой цифр в номере телефона: " + minRowsString);
}

void Tables::avgClicked()
{
    if (ui->tableWidget->rowCount() == 0)
    {
        QMessageBox::warning(this, "Среднее", "Таблица пустая.");
        return;
    }

    double totalSum = 0;
    int validEntries = 0;

    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        QString phone = ui->tableWidget->item(i, 4)->text();
        int sum = 0;

        for (QChar digit : phone)
        {
            if (digit.isDigit())
            {
                sum += digit.digitValue();
            }
        }

        totalSum += sum;
        if (sum > 0)
        {
            validEntries++;
        }
    }

    double avgSum = (validEntries > 0) ? totalSum / validEntries : 0;
    QMessageBox::information(this, "Среднее", "Среднее значение сумм цифр в номерах телефонов: " + QString::number(avgSum));
}

void Tables::maxClicked()
{
    if (ui->tableWidget->rowCount() == 0)
    {
        QMessageBox::warning(this, "Максимум", "Таблица пустая.");
        return;
    }

    int maxSum = -1;
    QStringList maxRows;

    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        QString phone = ui->tableWidget->item(i, 4)->text();
        int sum = 0;

        for (QChar digit : phone)
        {
            if (digit.isDigit())
            {
                sum += digit.digitValue();
            }
        }

        if (sum > maxSum)
        {
            maxSum = sum;
            maxRows.clear();
            maxRows.append(QString::number(i + 1));
        }
        else if (sum == maxSum)
        {
            maxRows.append(QString::number(i + 1));
        }
    }

    QString maxRowsString = maxRows.join(", ");
    QMessageBox::information(this, "Максимум", "Строки с максимальной суммой цифр в номерах телефонов: " + maxRowsString);
}

void Tables::searchClicked()
{
    QString searchData = ui->searchInput->text();
    QString message;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j)
        {
            if (ui->tableWidget->item(i, j)->text().contains(searchData, Qt::CaseInsensitive))
            {
                message += "Найдено на строке: " + QString::number(i + 1) + " (столбец " + QString::number(j + 1) + ")\n";
            }
        }
    }
    if (message.isEmpty())
    {
        QMessageBox::warning(this, "Результаты поиска", "Данные не найдены.");
    }
    else
    {
        QMessageBox::information(this, "Результаты поиска", message);
    }
}

void Tables::sortClicked()
{
    if (dataMap.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Нет данных для сортировки.");
        return;
    }

    int column = ui->columnNumberInput->text().toInt() - 1;
    bool isDescending = ui->descendingRadio->isChecked();

    QVector<QMap<QString, QString>> dataList;

    for (const auto &entry : dataMap)
    {
        dataList.append(entry);
    }

    std::sort(dataList.begin(), dataList.end(), [column, isDescending](const QMap<QString, QString> &a, const QMap<QString, QString> &b)
              {
        QString valueA, valueB;

        switch (column) {
        case 0:
            if (isDescending) {
                return a["id"].toInt() > b["id"].toInt();
            }
            return a["id"].toInt() < b["id"].toInt();
        case 1:
            valueA = a["surname"];
            valueB = b["surname"];
            break;
        case 2:
            valueA = a["name"];
            valueB = b["name"];
            break;
        case 3:
            valueA = a["patronymic"];
            valueB = b["patronymic"];
            break;
        case 4:
            valueA = a["phone"];
            valueB = b["phone"];
            break;
        case 5:
            valueA = a["email"];
            valueB = b["email"];
            break;
        default:
            return false;
        }

        if (isDescending) {
            return valueA > valueB;
        }
        return valueA < valueB; });

    ui->tableWidget->setRowCount(0);
    for (const auto &data : dataList)
    {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(data["id"]));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(data["surname"]));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(data["name"]));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(data["patronymic"]));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(data["phone"]));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(data["email"]));
    }
}

void Tables::loadDataFromJson()
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

    QJsonArray jsonArray = jsonDoc.array();
    ui->tableWidget->setRowCount(jsonArray.size());
    ui->tableWidget->setColumnCount(6);

    dataMap.clear();

    for (int i = 0; i < jsonArray.size(); ++i)
    {
        QJsonObject jsonObject = jsonArray[i].toObject();

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(jsonObject["surname"].toString()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(jsonObject["name"].toString()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(jsonObject["patronymic"].toString()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(jsonObject["phone"].toString()));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(jsonObject["email"].toString()));
    }
}

void Tables::saveDataToJson()
{

    QString qtFileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "JSON (*.json)");
    if (qtFileName.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Неверный файл.");
        return;
    }

    string fileName = qtFileName.toStdString();
    string extension = ".json";
    if (fileName.length() < extension.length() || fileName.compare(fileName.length() - extension.length(), extension.length(), extension) != 0)
    {
        fileName += extension;
    }

    QFile confFile(QString::fromStdString(fileName));
    if (!confFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, "Ошибка", "Проблемы с записью файла.");
        return;
    }

    QJsonArray jsonArray;
    for (int i = 0; i < dataMap.size(); ++i)
    {
        QJsonObject jsonObject;
        jsonObject["id"] = dataMap[i]["id"];
        jsonObject["surname"] = dataMap[i]["surname"];
        jsonObject["name"] = dataMap[i]["name"];
        jsonObject["patronymic"] = dataMap[i]["patronymic"];
        jsonObject["phone"] = dataMap[i]["phone"];
        jsonObject["email"] = dataMap[i]["email"];

        jsonArray.append(jsonObject);
    }

    QJsonDocument jsonDoc(jsonArray);
    confFile.write(jsonDoc.toJson());
    confFile.close();

    QMessageBox::information(this, "Успех", "Данные успешно сохранены в файл.");
}
