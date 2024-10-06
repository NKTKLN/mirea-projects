#include "tables.h"
#include "./ui_tables.h"

#include <time.h>
#include <random>
#include <cstdlib>
#include <algorithm>
#include <QMessageBox>
#include <QRegularExpression>

using namespace std;

Tables::Tables(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tables)
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
}

Tables::~Tables()
{
    delete ui;
}

void Tables::tableCellChanged(int row, int collumn)
{
    QTableWidgetItem *item = ui->tableWidget->item(row, collumn);
    QString cellData= item->text();
    QRegularExpression cellPattern("\\d+");
    QRegularExpressionMatch cellMatch = cellPattern.match(cellData);
    if (!cellMatch.hasMatch() && cellData != "")
    {
        QMessageBox::warning(this, "Ошибка", "Неверное число.");
        if (dataList.size() > row)
        {
            item->setText(dataList[row]);
        }
        return;
    }

    if (cellData == "")
    {
        item->setText("0");
    }

    if (dataList.size() > row)
    {
        dataList[row] = item->text();
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
    ui->tableWidget->setColumnCount(1);

    for(int i = 0; i < rowsCount; i++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(i, 0);
        if(item == nullptr)
        {
            item = new QTableWidgetItem;
            ui->tableWidget->setItem(i, 0, item);
        }

        if (dataList.size() <= i)
        {
            dataList.append(item->text());
        } else
        {
            item->setText(dataList[i]);
        }
    }

    if (rowsCount >= 0 && rowsCount < dataList.size())
    {
        dataList = dataList.mid(0, rowsCount);
    }
}

void Tables::setRandomDataClicked()
{
    srand(time(0));

    int rows = ui->tableWidget->rowCount();
    for(int i = 0; i < rows; i++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(i, 0);
        if(item == nullptr)
        {
            item = new QTableWidgetItem;
            ui->tableWidget->setItem(i, 0, item);
        }

        item->setText(QString::fromStdString(to_string(rand() % 101)));

        dataList[i] = item->text();
    }
}

void Tables::minClicked()
{
    if (dataList.size() == 0)
    {
        QMessageBox::warning(this, "Минимум", "Таблица пустая.");
        return;
    }

    QString minNum = dataList[0];
    for(int i = 0; i < dataList.size(); i++)
    {
        if (dataList[i].toInt() < minNum.toInt())
        {
            minNum = dataList[i];
        }
    }

    QMessageBox::information(this, "Минимум", "Минимальное число: " + minNum);
}

void Tables::avgClicked()
{
    if (dataList.size() == 0)
    {
        QMessageBox::warning(this, "Среднее", "Таблица пустая.");
        return;
    }

    double sum = 0;
    for(int i = 0; i < dataList.size(); i++)
    {
        sum += dataList[i].toInt();
    }

    QMessageBox::information(this, "Среднее", "Среднее значение: " + QString::number(sum / dataList.size()));
}

void Tables::maxClicked()
{
    if (dataList.size() == 0)
    {
        QMessageBox::warning(this, "Максимум", "Таблица пустая.");
        return;
    }

    QString maxNum = dataList[0];
    for(int i = 0; i < dataList.size(); i++)
    {
        if (dataList[i].toInt() > maxNum.toInt())
        {
            maxNum = dataList[i];
        }
    }

    QMessageBox::information(this, "Максимум", "Максимальное число: " + maxNum);
}

void Tables::searchClicked()
{
    QStringList rows;
    QString searchData = ui->searchInput->text();
    for(int i = 0; i < dataList.size(); i++)
    {
        if (dataList[i] == searchData)
        {
            rows.append(QString::number(i + 1));
        }
    }

    if (!rows.isEmpty())
    {
        QString message = rows.join(", ");
        QMessageBox::information(this, "Позиция", "Позиции в списке:\n" + message);
    } else
    {
        QMessageBox::warning(this, "Позиция", "Данные не найдены.");
    }
}

void Tables::sortClicked()
{
    if (dataList.size() == 0)
    {
        QMessageBox::warning(this, "Максимум", "Таблица пустая.");
        return;
    }

    bool isDescending = ui->descendingRadio->isChecked() && !ui->ascendingRadio->isChecked();

    auto isSorted = [isDescending](const QList<QString>& list) {
        for (int i = 1; i < list.size(); ++i)
        {
            if ((isDescending && list[i - 1].toDouble() < list[i].toDouble()) ||
                (!isDescending && list[i - 1].toDouble() > list[i].toDouble()))
            {
                return false;
            }
        }
        return true;
    };

    const int maxIterations = 1000000;
    random_device rd;
    mt19937 g(rd());

    int iterationCount = 0;
    while (!isSorted(dataList) && iterationCount < maxIterations)
    {
        shuffle(dataList.begin(), dataList.end(), g);
        iterationCount++;
    }

    if (iterationCount >= maxIterations)
    {
        QMessageBox::critical(this, "Ошибка", "Не удалось отсортировать (" + QString::number(maxIterations) + " итераций).");
        return;
    }

    for(int i = 0; i < dataList.size(); i++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(i, 0);
        if(item == nullptr)
        {
            item = new QTableWidgetItem;
            ui->tableWidget->setItem(i, 0, item);
        }

        item->setText(dataList[i]);
    }

    QMessageBox::information(this, "Успех", "Таблица отсортирована (" + QString::number(iterationCount) + " итераций).");

}
