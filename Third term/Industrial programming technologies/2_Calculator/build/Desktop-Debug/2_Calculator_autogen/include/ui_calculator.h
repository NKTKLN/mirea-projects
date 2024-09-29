/********************************************************************************
** Form generated from reading UI file 'calculator.ui'
**
** Created by: Qt User Interface Compiler version 5.15.14
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATOR_H
#define UI_CALCULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Calculator
{
public:
    QAction *actionCalculator;
    QAction *actionProgramming;
    QWidget *centralwidget;
    QLineEdit *secondNumberInput;
    QSpinBox *secondNumberSystem;
    QLabel *label_1;
    QSpinBox *outNumberSystem;
    QPushButton *buttonAdd;
    QPushButton *buttonSubtract;
    QPushButton *buttonMultiply;
    QPushButton *buttonDivide;
    QLabel *label_2;
    QLineEdit *firstNumberInput;
    QSpinBox *firstNumberSystem;
    QLabel *label_3;
    QTextEdit *plainTextEdit;

    void setupUi(QMainWindow *Calculator)
    {
        if (Calculator->objectName().isEmpty())
            Calculator->setObjectName(QString::fromUtf8("Calculator"));
        Calculator->resize(350, 382);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Calculator->sizePolicy().hasHeightForWidth());
        Calculator->setSizePolicy(sizePolicy);
        actionCalculator = new QAction(Calculator);
        actionCalculator->setObjectName(QString::fromUtf8("actionCalculator"));
        actionProgramming = new QAction(Calculator);
        actionProgramming->setObjectName(QString::fromUtf8("actionProgramming"));
        centralwidget = new QWidget(Calculator);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        secondNumberInput = new QLineEdit(centralwidget);
        secondNumberInput->setObjectName(QString::fromUtf8("secondNumberInput"));
        secondNumberInput->setGeometry(QRect(12, 118, 214, 60));
        QFont font;
        font.setPointSize(18);
        secondNumberInput->setFont(font);
        secondNumberSystem = new QSpinBox(centralwidget);
        secondNumberSystem->setObjectName(QString::fromUtf8("secondNumberSystem"));
        secondNumberSystem->setGeometry(QRect(238, 118, 100, 60));
        secondNumberSystem->setFont(font);
        secondNumberSystem->setMinimum(2);
        secondNumberSystem->setMaximum(36);
        secondNumberSystem->setValue(10);
        label_1 = new QLabel(centralwidget);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setGeometry(QRect(12, 6, 214, 31));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        label_1->setFont(font1);
        label_1->setTextFormat(Qt::TextFormat::AutoText);
        label_1->setAlignment(Qt::AlignmentFlag::AlignCenter);
        outNumberSystem = new QSpinBox(centralwidget);
        outNumberSystem->setObjectName(QString::fromUtf8("outNumberSystem"));
        outNumberSystem->setGeometry(QRect(238, 190, 100, 60));
        outNumberSystem->setFont(font);
        outNumberSystem->setMinimum(2);
        outNumberSystem->setMaximum(36);
        outNumberSystem->setValue(10);
        buttonAdd = new QPushButton(centralwidget);
        buttonAdd->setObjectName(QString::fromUtf8("buttonAdd"));
        buttonAdd->setGeometry(QRect(6, 296, 80, 80));
        buttonAdd->setFont(font);
        buttonSubtract = new QPushButton(centralwidget);
        buttonSubtract->setObjectName(QString::fromUtf8("buttonSubtract"));
        buttonSubtract->setGeometry(QRect(92, 296, 80, 80));
        buttonSubtract->setFont(font);
        buttonMultiply = new QPushButton(centralwidget);
        buttonMultiply->setObjectName(QString::fromUtf8("buttonMultiply"));
        buttonMultiply->setGeometry(QRect(178, 296, 80, 80));
        buttonMultiply->setFont(font);
        buttonDivide = new QPushButton(centralwidget);
        buttonDivide->setObjectName(QString::fromUtf8("buttonDivide"));
        buttonDivide->setGeometry(QRect(264, 296, 80, 80));
        buttonDivide->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(238, 6, 100, 30));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        firstNumberInput = new QLineEdit(centralwidget);
        firstNumberInput->setObjectName(QString::fromUtf8("firstNumberInput"));
        firstNumberInput->setGeometry(QRect(12, 46, 214, 60));
        firstNumberInput->setFont(font);
        firstNumberSystem = new QSpinBox(centralwidget);
        firstNumberSystem->setObjectName(QString::fromUtf8("firstNumberSystem"));
        firstNumberSystem->setGeometry(QRect(238, 46, 100, 60));
        firstNumberSystem->setFont(font);
        firstNumberSystem->setMinimum(2);
        firstNumberSystem->setMaximum(36);
        firstNumberSystem->setValue(10);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(6, 256, 338, 30));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        plainTextEdit = new QTextEdit(centralwidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(12, 190, 214, 60));
        plainTextEdit->setFont(font);
        plainTextEdit->setAutoFillBackground(false);
        plainTextEdit->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        plainTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        plainTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        plainTextEdit->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);
        plainTextEdit->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);
        plainTextEdit->setReadOnly(true);
        Calculator->setCentralWidget(centralwidget);

        retranslateUi(Calculator);

        QMetaObject::connectSlotsByName(Calculator);
    } // setupUi

    void retranslateUi(QMainWindow *Calculator)
    {
        Calculator->setWindowTitle(QCoreApplication::translate("Calculator", "Programming", nullptr));
        actionCalculator->setText(QCoreApplication::translate("Calculator", "&Calculator", nullptr));
        actionProgramming->setText(QCoreApplication::translate("Calculator", "&Programming", nullptr));
        label_1->setText(QCoreApplication::translate("Calculator", "NUMBERS", nullptr));
        buttonAdd->setText(QCoreApplication::translate("Calculator", "+", nullptr));
#if QT_CONFIG(shortcut)
        buttonAdd->setShortcut(QCoreApplication::translate("Calculator", "Backspace", nullptr));
#endif // QT_CONFIG(shortcut)
        buttonSubtract->setText(QCoreApplication::translate("Calculator", "-", nullptr));
#if QT_CONFIG(shortcut)
        buttonSubtract->setShortcut(QCoreApplication::translate("Calculator", "Backspace", nullptr));
#endif // QT_CONFIG(shortcut)
        buttonMultiply->setText(QCoreApplication::translate("Calculator", "*", nullptr));
#if QT_CONFIG(shortcut)
        buttonMultiply->setShortcut(QCoreApplication::translate("Calculator", "Backspace", nullptr));
#endif // QT_CONFIG(shortcut)
        buttonDivide->setText(QCoreApplication::translate("Calculator", "/", nullptr));
#if QT_CONFIG(shortcut)
        buttonDivide->setShortcut(QCoreApplication::translate("Calculator", "Backspace", nullptr));
#endif // QT_CONFIG(shortcut)
        label_2->setText(QCoreApplication::translate("Calculator", "SYSTEM", nullptr));
        label_3->setText(QCoreApplication::translate("Calculator", "ACTIONS", nullptr));
        plainTextEdit->setHtml(QCoreApplication::translate("Calculator", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:18pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Calculator: public Ui_Calculator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATOR_H
