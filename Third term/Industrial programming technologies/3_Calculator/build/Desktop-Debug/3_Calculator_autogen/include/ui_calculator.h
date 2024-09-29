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
#include <QtWidgets/QRadioButton>
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
    QLabel *label_1;
    QPushButton *buttonAdd;
    QPushButton *buttonSubtract;
    QPushButton *buttonMultiply;
    QPushButton *buttonDivide;
    QLineEdit *firstNumberInput;
    QLabel *label_3;
    QTextEdit *plainTextEdit;
    QPushButton *buttonCot;
    QPushButton *buttonTan;
    QPushButton *buttonCos;
    QPushButton *buttonSin;
    QPushButton *buttonArccos;
    QRadioButton *radioButtonRadians;
    QRadioButton *radioButtonDegrees;
    QLabel *label_4;
    QPushButton *buttonArcsin;
    QPushButton *buttonArctan;

    void setupUi(QMainWindow *Calculator)
    {
        if (Calculator->objectName().isEmpty())
            Calculator->setObjectName(QString::fromUtf8("Calculator"));
        Calculator->resize(350, 702);
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
        secondNumberInput->setGeometry(QRect(12, 118, 328, 60));
        QFont font;
        font.setPointSize(14);
        secondNumberInput->setFont(font);
        label_1 = new QLabel(centralwidget);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setGeometry(QRect(12, 6, 328, 31));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        label_1->setFont(font1);
        label_1->setTextFormat(Qt::TextFormat::AutoText);
        label_1->setAlignment(Qt::AlignmentFlag::AlignCenter);
        buttonAdd = new QPushButton(centralwidget);
        buttonAdd->setObjectName(QString::fromUtf8("buttonAdd"));
        buttonAdd->setGeometry(QRect(6, 356, 80, 80));
        buttonAdd->setFont(font);
        buttonSubtract = new QPushButton(centralwidget);
        buttonSubtract->setObjectName(QString::fromUtf8("buttonSubtract"));
        buttonSubtract->setGeometry(QRect(92, 356, 80, 80));
        buttonSubtract->setFont(font);
        buttonMultiply = new QPushButton(centralwidget);
        buttonMultiply->setObjectName(QString::fromUtf8("buttonMultiply"));
        buttonMultiply->setGeometry(QRect(178, 356, 80, 80));
        buttonMultiply->setFont(font);
        buttonDivide = new QPushButton(centralwidget);
        buttonDivide->setObjectName(QString::fromUtf8("buttonDivide"));
        buttonDivide->setGeometry(QRect(264, 356, 80, 80));
        buttonDivide->setFont(font);
        firstNumberInput = new QLineEdit(centralwidget);
        firstNumberInput->setObjectName(QString::fromUtf8("firstNumberInput"));
        firstNumberInput->setGeometry(QRect(12, 46, 328, 60));
        firstNumberInput->setFont(font);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(6, 320, 338, 30));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        plainTextEdit = new QTextEdit(centralwidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(12, 190, 328, 60));
        plainTextEdit->setFont(font);
        plainTextEdit->setAutoFillBackground(false);
        plainTextEdit->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        plainTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        plainTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        plainTextEdit->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);
        plainTextEdit->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);
        plainTextEdit->setReadOnly(true);
        buttonCot = new QPushButton(centralwidget);
        buttonCot->setObjectName(QString::fromUtf8("buttonCot"));
        buttonCot->setGeometry(QRect(264, 442, 80, 80));
        buttonCot->setFont(font);
        buttonTan = new QPushButton(centralwidget);
        buttonTan->setObjectName(QString::fromUtf8("buttonTan"));
        buttonTan->setGeometry(QRect(178, 442, 80, 80));
        buttonTan->setFont(font);
        buttonCos = new QPushButton(centralwidget);
        buttonCos->setObjectName(QString::fromUtf8("buttonCos"));
        buttonCos->setGeometry(QRect(92, 442, 80, 80));
        buttonCos->setFont(font);
        buttonSin = new QPushButton(centralwidget);
        buttonSin->setObjectName(QString::fromUtf8("buttonSin"));
        buttonSin->setGeometry(QRect(6, 442, 80, 80));
        buttonSin->setFont(font);
        buttonArccos = new QPushButton(centralwidget);
        buttonArccos->setObjectName(QString::fromUtf8("buttonArccos"));
        buttonArccos->setGeometry(QRect(178, 528, 166, 80));
        buttonArccos->setFont(font);
        radioButtonRadians = new QRadioButton(centralwidget);
        radioButtonRadians->setObjectName(QString::fromUtf8("radioButtonRadians"));
        radioButtonRadians->setGeometry(QRect(12, 294, 160, 20));
        radioButtonRadians->setFont(font);
        radioButtonRadians->setIconSize(QSize(20, 20));
        radioButtonRadians->setChecked(true);
        radioButtonDegrees = new QRadioButton(centralwidget);
        radioButtonDegrees->setObjectName(QString::fromUtf8("radioButtonDegrees"));
        radioButtonDegrees->setGeometry(QRect(184, 294, 160, 20));
        radioButtonDegrees->setFont(font);
        radioButtonDegrees->setIconSize(QSize(18, 18));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(6, 256, 338, 30));
        label_4->setFont(font1);
        label_4->setTextFormat(Qt::TextFormat::AutoText);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);
        buttonArcsin = new QPushButton(centralwidget);
        buttonArcsin->setObjectName(QString::fromUtf8("buttonArcsin"));
        buttonArcsin->setGeometry(QRect(6, 528, 166, 80));
        buttonArcsin->setFont(font);
        buttonArctan = new QPushButton(centralwidget);
        buttonArctan->setObjectName(QString::fromUtf8("buttonArctan"));
        buttonArctan->setGeometry(QRect(6, 614, 338, 80));
        buttonArctan->setFont(font);
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
        label_3->setText(QCoreApplication::translate("Calculator", "ACTIONS", nullptr));
        plainTextEdit->setHtml(QCoreApplication::translate("Calculator", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt;\">                        </span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:18pt;\"><br /></p></body></html>", nullptr));
        buttonCot->setText(QCoreApplication::translate("Calculator", "COT", nullptr));
#if QT_CONFIG(shortcut)
        buttonCot->setShortcut(QCoreApplication::translate("Calculator", "Backspace", nullptr));
#endif // QT_CONFIG(shortcut)
        buttonTan->setText(QCoreApplication::translate("Calculator", "TAN", nullptr));
#if QT_CONFIG(shortcut)
        buttonTan->setShortcut(QCoreApplication::translate("Calculator", "Backspace", nullptr));
#endif // QT_CONFIG(shortcut)
        buttonCos->setText(QCoreApplication::translate("Calculator", "COS", nullptr));
#if QT_CONFIG(shortcut)
        buttonCos->setShortcut(QCoreApplication::translate("Calculator", "Backspace", nullptr));
#endif // QT_CONFIG(shortcut)
        buttonSin->setText(QCoreApplication::translate("Calculator", "SIN", nullptr));
#if QT_CONFIG(shortcut)
        buttonSin->setShortcut(QCoreApplication::translate("Calculator", "Backspace", nullptr));
#endif // QT_CONFIG(shortcut)
        buttonArccos->setText(QCoreApplication::translate("Calculator", "ARCCOS", nullptr));
#if QT_CONFIG(shortcut)
        buttonArccos->setShortcut(QCoreApplication::translate("Calculator", "Backspace", nullptr));
#endif // QT_CONFIG(shortcut)
        radioButtonRadians->setText(QCoreApplication::translate("Calculator", "RADIANS", nullptr));
        radioButtonDegrees->setText(QCoreApplication::translate("Calculator", "DEGREES", nullptr));
        label_4->setText(QCoreApplication::translate("Calculator", "UNITS", nullptr));
        buttonArcsin->setText(QCoreApplication::translate("Calculator", "ARCSIN", nullptr));
#if QT_CONFIG(shortcut)
        buttonArcsin->setShortcut(QCoreApplication::translate("Calculator", "Backspace", nullptr));
#endif // QT_CONFIG(shortcut)
        buttonArctan->setText(QCoreApplication::translate("Calculator", "ARCTAN", nullptr));
#if QT_CONFIG(shortcut)
        buttonArctan->setShortcut(QCoreApplication::translate("Calculator", "Backspace", nullptr));
#endif // QT_CONFIG(shortcut)
    } // retranslateUi

};

namespace Ui {
    class Calculator: public Ui_Calculator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATOR_H
