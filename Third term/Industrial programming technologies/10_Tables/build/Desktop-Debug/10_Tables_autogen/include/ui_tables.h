/********************************************************************************
** Form generated from reading UI file 'tables.ui'
**
** Created by: Qt User Interface Compiler version 5.15.14
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLES_H
#define UI_TABLES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tables
{
public:
    QWidget *centralwidget;
    QTableWidget *tableWidget;
    QLabel *label;
    QLineEdit *rowsCountInput;
    QPushButton *setRowsButton;
    QPushButton *setRandomDataButton;
    QPushButton *minButton;
    QPushButton *avgButton;
    QPushButton *maxButton;
    QRadioButton *descendingRadio;
    QRadioButton *ascendingRadio;
    QPushButton *sortButton;
    QLabel *label_2;
    QLineEdit *searchInput;
    QPushButton *searchButton;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QFrame *line;
    QFrame *line_2;
    QLabel *label_3;
    QSpinBox *columnNumberInput;
    QFrame *line_3;

    void setupUi(QMainWindow *Tables)
    {
        if (Tables->objectName().isEmpty())
            Tables->setObjectName(QString::fromUtf8("Tables"));
        Tables->resize(1000, 600);
        centralwidget = new QWidget(Tables);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(20, 60, 771, 521));
        QFont font;
        font.setPointSize(14);
        tableWidget->setFont(font);
        tableWidget->horizontalHeader()->setDefaultSectionSize(120);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->verticalHeader()->setVisible(false);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 121, 30));
        label->setFont(font);
        rowsCountInput = new QLineEdit(centralwidget);
        rowsCountInput->setObjectName(QString::fromUtf8("rowsCountInput"));
        rowsCountInput->setGeometry(QRect(150, 20, 113, 30));
        rowsCountInput->setFont(font);
        rowsCountInput->setInputMethodHints(Qt::InputMethodHint::ImhPreferNumbers);
        setRowsButton = new QPushButton(centralwidget);
        setRowsButton->setObjectName(QString::fromUtf8("setRowsButton"));
        setRowsButton->setGeometry(QRect(270, 20, 80, 30));
        setRowsButton->setFont(font);
        setRandomDataButton = new QPushButton(centralwidget);
        setRandomDataButton->setObjectName(QString::fromUtf8("setRandomDataButton"));
        setRandomDataButton->setGeometry(QRect(370, 20, 291, 30));
        setRandomDataButton->setFont(font);
        minButton = new QPushButton(centralwidget);
        minButton->setObjectName(QString::fromUtf8("minButton"));
        minButton->setGeometry(QRect(810, 60, 171, 30));
        minButton->setFont(font);
        avgButton = new QPushButton(centralwidget);
        avgButton->setObjectName(QString::fromUtf8("avgButton"));
        avgButton->setGeometry(QRect(810, 100, 171, 30));
        avgButton->setFont(font);
        maxButton = new QPushButton(centralwidget);
        maxButton->setObjectName(QString::fromUtf8("maxButton"));
        maxButton->setGeometry(QRect(810, 140, 171, 30));
        maxButton->setFont(font);
        descendingRadio = new QRadioButton(centralwidget);
        descendingRadio->setObjectName(QString::fromUtf8("descendingRadio"));
        descendingRadio->setGeometry(QRect(810, 250, 171, 20));
        descendingRadio->setFont(font);
        descendingRadio->setChecked(true);
        ascendingRadio = new QRadioButton(centralwidget);
        ascendingRadio->setObjectName(QString::fromUtf8("ascendingRadio"));
        ascendingRadio->setGeometry(QRect(810, 280, 171, 20));
        ascendingRadio->setFont(font);
        sortButton = new QPushButton(centralwidget);
        sortButton->setObjectName(QString::fromUtf8("sortButton"));
        sortButton->setGeometry(QRect(810, 310, 171, 30));
        sortButton->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(810, 370, 171, 30));
        label_2->setFont(font);
        searchInput = new QLineEdit(centralwidget);
        searchInput->setObjectName(QString::fromUtf8("searchInput"));
        searchInput->setGeometry(QRect(810, 400, 171, 30));
        searchInput->setFont(font);
        searchButton = new QPushButton(centralwidget);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        searchButton->setGeometry(QRect(810, 440, 171, 30));
        searchButton->setFont(font);
        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setGeometry(QRect(810, 510, 171, 30));
        loadButton->setFont(font);
        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(810, 550, 171, 30));
        saveButton->setFont(font);
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(810, 180, 171, 16));
        line->setFont(font);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(810, 480, 171, 16));
        line_2->setFont(font);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(810, 200, 171, 30));
        label_3->setFont(font);
        columnNumberInput = new QSpinBox(centralwidget);
        columnNumberInput->setObjectName(QString::fromUtf8("columnNumberInput"));
        columnNumberInput->setGeometry(QRect(910, 200, 61, 30));
        columnNumberInput->setFont(font);
        columnNumberInput->setMinimum(1);
        columnNumberInput->setMaximum(6);
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(810, 350, 171, 16));
        line_3->setFont(font);
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        Tables->setCentralWidget(centralwidget);

        retranslateUi(Tables);

        QMetaObject::connectSlotsByName(Tables);
    } // setupUi

    void retranslateUi(QMainWindow *Tables)
    {
        Tables->setWindowTitle(QCoreApplication::translate("Tables", "Tables", nullptr));
        label->setText(QCoreApplication::translate("Tables", "\320\232\320\276\320\273-\320\262\320\276 \321\201\321\202\321\200\320\276\320\272:", nullptr));
        rowsCountInput->setText(QCoreApplication::translate("Tables", "0", nullptr));
        setRowsButton->setText(QCoreApplication::translate("Tables", "\320\227\320\260\320\264\320\260\321\202\321\214", nullptr));
        setRandomDataButton->setText(QCoreApplication::translate("Tables", "\320\240\320\260\320\275\320\264\320\276\320\274\320\275\320\276 \320\267\320\260\320\277\320\276\320\273\320\275\320\270\321\202\321\214", nullptr));
        minButton->setText(QCoreApplication::translate("Tables", "\320\234\320\270\320\275\320\270\320\274\321\203\320\274", nullptr));
        avgButton->setText(QCoreApplication::translate("Tables", "\320\241\321\200\320\265\320\264\320\275\320\265\320\265", nullptr));
        maxButton->setText(QCoreApplication::translate("Tables", "\320\234\320\260\320\272\321\201\320\270\320\274\321\203\320\274", nullptr));
        descendingRadio->setText(QCoreApplication::translate("Tables", "\320\237\320\276 \321\203\320\261\321\213\320\262\320\260\320\275\320\270\321\216", nullptr));
        ascendingRadio->setText(QCoreApplication::translate("Tables", "\320\237\320\276 \320\262\320\276\320\267\321\200\320\260\321\201\321\202\320\260\320\275\320\270\321\216", nullptr));
        sortButton->setText(QCoreApplication::translate("Tables", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\272\320\260", nullptr));
        label_2->setText(QCoreApplication::translate("Tables", "\320\230\321\201\320\272\320\276\320\274\320\276\320\265:", nullptr));
        searchButton->setText(QCoreApplication::translate("Tables", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        loadButton->setText(QCoreApplication::translate("Tables", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
        saveButton->setText(QCoreApplication::translate("Tables", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        label_3->setText(QCoreApplication::translate("Tables", "\320\241\321\202\320\276\320\273\320\261\320\265\321\206:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tables: public Ui_Tables {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLES_H
