/********************************************************************************
** Form generated from reading UI file 'sudoku.ui'
**
** Created by: Qt User Interface Compiler version 5.15.14
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUDOKU_H
#define UI_SUDOKU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Sudoku
{
public:
    QWidget *centralwidget;
    QFrame *line_2;
    QPushButton *pushButton_draftMode;
    QSpinBox *spinBox_mainNumber;
    QLabel *label;
    QFrame *line_3;
    QLabel *label_739;
    QLabel *label_time;
    QPushButton *pushButton_restart;
    QWidget *field;
    QSpinBox *spinBox_difficulty;
    QLabel *label_2;
    QFrame *line_4;
    QPushButton *pushButton_check;

    void setupUi(QMainWindow *Sudoku)
    {
        if (Sudoku->objectName().isEmpty())
            Sudoku->setObjectName(QString::fromUtf8("Sudoku"));
        Sudoku->resize(599, 420);
        centralwidget = new QWidget(Sudoku);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setEnabled(true);
        line_2->setGeometry(QRect(440, 110, 141, 21));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        pushButton_draftMode = new QPushButton(centralwidget);
        pushButton_draftMode->setObjectName(QString::fromUtf8("pushButton_draftMode"));
        pushButton_draftMode->setEnabled(true);
        pushButton_draftMode->setGeometry(QRect(450, 180, 121, 31));
        QFont font;
        font.setPointSize(14);
        pushButton_draftMode->setFont(font);
        pushButton_draftMode->setCheckable(true);
        spinBox_mainNumber = new QSpinBox(centralwidget);
        spinBox_mainNumber->setObjectName(QString::fromUtf8("spinBox_mainNumber"));
        spinBox_mainNumber->setEnabled(true);
        spinBox_mainNumber->setGeometry(QRect(450, 150, 121, 22));
        spinBox_mainNumber->setFont(font);
        spinBox_mainNumber->setAlignment(Qt::AlignmentFlag::AlignCenter);
        spinBox_mainNumber->setMinimum(1);
        spinBox_mainNumber->setMaximum(9);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(true);
        label->setGeometry(QRect(450, 130, 121, 16));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        label->setFont(font1);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setEnabled(true);
        line_3->setGeometry(QRect(440, 210, 141, 21));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        label_739 = new QLabel(centralwidget);
        label_739->setObjectName(QString::fromUtf8("label_739"));
        label_739->setEnabled(true);
        label_739->setGeometry(QRect(450, 70, 121, 16));
        label_739->setFont(font1);
        label_739->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_time = new QLabel(centralwidget);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setEnabled(true);
        label_time->setGeometry(QRect(450, 90, 121, 16));
        QFont font2;
        font2.setPointSize(12);
        label_time->setFont(font2);
        label_time->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pushButton_restart = new QPushButton(centralwidget);
        pushButton_restart->setObjectName(QString::fromUtf8("pushButton_restart"));
        pushButton_restart->setEnabled(true);
        pushButton_restart->setGeometry(QRect(450, 280, 121, 31));
        pushButton_restart->setFont(font);
        field = new QWidget(centralwidget);
        field->setObjectName(QString::fromUtf8("field"));
        field->setGeometry(QRect(20, 20, 381, 381));
        spinBox_difficulty = new QSpinBox(centralwidget);
        spinBox_difficulty->setObjectName(QString::fromUtf8("spinBox_difficulty"));
        spinBox_difficulty->setEnabled(true);
        spinBox_difficulty->setGeometry(QRect(450, 250, 121, 22));
        spinBox_difficulty->setFont(font);
        spinBox_difficulty->setAlignment(Qt::AlignmentFlag::AlignCenter);
        spinBox_difficulty->setMinimum(1);
        spinBox_difficulty->setMaximum(4);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setEnabled(true);
        label_2->setGeometry(QRect(450, 230, 121, 16));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        line_4 = new QFrame(centralwidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setEnabled(true);
        line_4->setGeometry(QRect(440, 310, 141, 21));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        pushButton_check = new QPushButton(centralwidget);
        pushButton_check->setObjectName(QString::fromUtf8("pushButton_check"));
        pushButton_check->setEnabled(true);
        pushButton_check->setGeometry(QRect(450, 330, 121, 31));
        pushButton_check->setFont(font);
        Sudoku->setCentralWidget(centralwidget);

        retranslateUi(Sudoku);

        QMetaObject::connectSlotsByName(Sudoku);
    } // setupUi

    void retranslateUi(QMainWindow *Sudoku)
    {
        Sudoku->setWindowTitle(QCoreApplication::translate("Sudoku", "Sudoku", nullptr));
        pushButton_draftMode->setText(QCoreApplication::translate("Sudoku", "Draft mode", nullptr));
        label->setText(QCoreApplication::translate("Sudoku", "CURRENT NUM", nullptr));
        label_739->setText(QCoreApplication::translate("Sudoku", "TIME", nullptr));
        label_time->setText(QString());
        pushButton_restart->setText(QCoreApplication::translate("Sudoku", "Generate", nullptr));
        label_2->setText(QCoreApplication::translate("Sudoku", "DIFFICULTY", nullptr));
        pushButton_check->setText(QCoreApplication::translate("Sudoku", "Check", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Sudoku: public Ui_Sudoku {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUDOKU_H
