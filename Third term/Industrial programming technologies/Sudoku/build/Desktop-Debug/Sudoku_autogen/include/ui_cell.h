/********************************************************************************
** Form generated from reading UI file 'cell.ui'
**
** Created by: Qt User Interface Compiler version 5.15.14
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CELL_H
#define UI_CELL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Cell
{
public:
    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_main;

    void setupUi(QWidget *Cell)
    {
        if (Cell->objectName().isEmpty())
            Cell->setObjectName(QString::fromUtf8("Cell"));
        Cell->resize(38, 38);
        QFont font;
        font.setPointSize(1);
        Cell->setFont(font);
        Cell->setStyleSheet(QString::fromUtf8(""));
        label_1 = new QLabel(Cell);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setEnabled(true);
        label_1->setGeometry(QRect(2, 2, 10, 10));
        QFont font1;
        font1.setPointSize(12);
        label_1->setFont(font1);
        label_1->setStyleSheet(QString::fromUtf8("color: rgb(138, 208, 255)"));
        label_1->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        label_1->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_2 = new QLabel(Cell);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setEnabled(true);
        label_2->setGeometry(QRect(14, 2, 10, 10));
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(138, 208, 255)"));
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_3 = new QLabel(Cell);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setEnabled(true);
        label_3->setGeometry(QRect(26, 2, 10, 10));
        label_3->setFont(font1);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(138, 208, 255)"));
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_4 = new QLabel(Cell);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setEnabled(true);
        label_4->setGeometry(QRect(2, 14, 10, 10));
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(138, 208, 255)"));
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_5 = new QLabel(Cell);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setEnabled(true);
        label_5->setGeometry(QRect(14, 14, 10, 10));
        label_5->setFont(font1);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(138, 208, 255)"));
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_6 = new QLabel(Cell);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setEnabled(true);
        label_6->setGeometry(QRect(26, 14, 10, 10));
        label_6->setFont(font1);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(138, 208, 255)"));
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_7 = new QLabel(Cell);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setEnabled(true);
        label_7->setGeometry(QRect(2, 26, 10, 10));
        label_7->setFont(font1);
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(138, 208, 255)"));
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_8 = new QLabel(Cell);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setEnabled(true);
        label_8->setGeometry(QRect(14, 26, 10, 10));
        label_8->setFont(font1);
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(138, 208, 255)"));
        label_8->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_9 = new QLabel(Cell);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setEnabled(true);
        label_9->setGeometry(QRect(26, 26, 10, 10));
        label_9->setFont(font1);
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(138, 208, 255)"));
        label_9->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_main = new QLabel(Cell);
        label_main->setObjectName(QString::fromUtf8("label_main"));
        label_main->setEnabled(true);
        label_main->setGeometry(QRect(2, 2, 34, 34));
        QFont font2;
        font2.setPointSize(32);
        label_main->setFont(font2);
        label_main->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        label_main->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(Cell);

        QMetaObject::connectSlotsByName(Cell);
    } // setupUi

    void retranslateUi(QWidget *Cell)
    {
        Cell->setWindowTitle(QCoreApplication::translate("Cell", "Form", nullptr));
        label_1->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
        label_5->setText(QString());
        label_6->setText(QString());
        label_7->setText(QString());
        label_8->setText(QString());
        label_9->setText(QString());
        label_main->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Cell: public Ui_Cell {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CELL_H
