/********************************************************************************
** Form generated from reading UI file 'userform.ui'
**
** Created by: Qt User Interface Compiler version 5.15.14
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERFORM_H
#define UI_USERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserForm
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *username;
    QLineEdit *fullName;
    QLineEdit *passport;
    QLineEdit *phone;
    QLineEdit *email;
    QLineEdit *dob;
    QRadioButton *radioButtonM;
    QRadioButton *radioButtonF;
    QPushButton *registButton;
    QPushButton *loadDataButton;

    void setupUi(QMainWindow *UserForm)
    {
        if (UserForm->objectName().isEmpty())
            UserForm->setObjectName(QString::fromUtf8("UserForm"));
        UserForm->resize(669, 388);
        centralwidget = new QWidget(UserForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(250, 20, 400, 30));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 60, 221, 30));
        QFont font1;
        font1.setPointSize(16);
        label_2->setFont(font1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 100, 221, 30));
        label_3->setFont(font1);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 140, 221, 30));
        label_4->setFont(font1);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 220, 221, 30));
        label_5->setFont(font1);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 180, 221, 30));
        label_6->setFont(font1);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 300, 221, 30));
        label_7->setFont(font1);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 260, 221, 30));
        label_8->setFont(font1);
        username = new QLineEdit(centralwidget);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(250, 60, 400, 30));
        username->setFont(font1);
        username->setInputMethodHints(Qt::InputMethodHint::ImhLatinOnly);
        fullName = new QLineEdit(centralwidget);
        fullName->setObjectName(QString::fromUtf8("fullName"));
        fullName->setGeometry(QRect(250, 100, 400, 30));
        fullName->setFont(font1);
        passport = new QLineEdit(centralwidget);
        passport->setObjectName(QString::fromUtf8("passport"));
        passport->setGeometry(QRect(250, 180, 400, 30));
        passport->setFont(font1);
        passport->setInputMethodHints(Qt::InputMethodHint::ImhDigitsOnly);
        phone = new QLineEdit(centralwidget);
        phone->setObjectName(QString::fromUtf8("phone"));
        phone->setGeometry(QRect(250, 260, 400, 30));
        phone->setFont(font1);
        phone->setInputMethodHints(Qt::InputMethodHint::ImhFormattedNumbersOnly);
        email = new QLineEdit(centralwidget);
        email->setObjectName(QString::fromUtf8("email"));
        email->setGeometry(QRect(250, 300, 400, 30));
        email->setFont(font1);
        email->setInputMethodHints(Qt::InputMethodHint::ImhEmailCharactersOnly);
        dob = new QLineEdit(centralwidget);
        dob->setObjectName(QString::fromUtf8("dob"));
        dob->setGeometry(QRect(250, 220, 400, 30));
        dob->setFont(font1);
        dob->setInputMethodHints(Qt::InputMethodHint::ImhDate);
        radioButtonM = new QRadioButton(centralwidget);
        radioButtonM->setObjectName(QString::fromUtf8("radioButtonM"));
        radioButtonM->setGeometry(QRect(250, 140, 190, 30));
        radioButtonM->setFont(font1);
        radioButtonM->setCheckable(true);
        radioButtonF = new QRadioButton(centralwidget);
        radioButtonF->setObjectName(QString::fromUtf8("radioButtonF"));
        radioButtonF->setGeometry(QRect(460, 140, 190, 30));
        radioButtonF->setFont(font1);
        registButton = new QPushButton(centralwidget);
        registButton->setObjectName(QString::fromUtf8("registButton"));
        registButton->setGeometry(QRect(250, 340, 400, 30));
        registButton->setFont(font1);
        loadDataButton = new QPushButton(centralwidget);
        loadDataButton->setObjectName(QString::fromUtf8("loadDataButton"));
        loadDataButton->setGeometry(QRect(20, 340, 221, 30));
        loadDataButton->setFont(font1);
        UserForm->setCentralWidget(centralwidget);

        retranslateUi(UserForm);

        QMetaObject::connectSlotsByName(UserForm);
    } // setupUi

    void retranslateUi(QMainWindow *UserForm)
    {
        UserForm->setWindowTitle(QCoreApplication::translate("UserForm", "UserForm", nullptr));
        label->setText(QCoreApplication::translate("UserForm", "\320\244\320\276\321\200\320\274\320\260 \321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\320\270", nullptr));
        label_2->setText(QCoreApplication::translate("UserForm", "\320\230\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217:", nullptr));
        label_3->setText(QCoreApplication::translate("UserForm", "\320\244\320\230\320\236:", nullptr));
        label_4->setText(QCoreApplication::translate("UserForm", "\320\237\320\276\320\273:", nullptr));
        label_5->setText(QCoreApplication::translate("UserForm", "\320\224\320\260\321\202\320\260 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217:", nullptr));
        label_6->setText(QCoreApplication::translate("UserForm", "\320\237\320\260\321\201\320\277\320\276\321\200\321\202:", nullptr));
        label_7->setText(QCoreApplication::translate("UserForm", "E-mail:", nullptr));
        label_8->setText(QCoreApplication::translate("UserForm", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275:", nullptr));
        username->setInputMask(QString());
        username->setText(QString());
        username->setPlaceholderText(QCoreApplication::translate("UserForm", "User123", nullptr));
        fullName->setPlaceholderText(QCoreApplication::translate("UserForm", "\320\230\320\262\320\260\320\275\320\276\320\262 \320\230\320\262\320\260\320\275 \320\230\320\262\320\260\320\275\320\276\320\262\320\270\321\207", nullptr));
        passport->setPlaceholderText(QCoreApplication::translate("UserForm", "4211 324521", nullptr));
        phone->setPlaceholderText(QCoreApplication::translate("UserForm", "+7-123-456-78-90", nullptr));
        email->setPlaceholderText(QCoreApplication::translate("UserForm", "example@mail.com", nullptr));
        dob->setPlaceholderText(QCoreApplication::translate("UserForm", "01.08.2005", nullptr));
        radioButtonM->setText(QCoreApplication::translate("UserForm", "\320\234\321\203\320\266\321\201\320\272\320\276\320\271", nullptr));
        radioButtonF->setText(QCoreApplication::translate("UserForm", "\320\226\320\265\320\275\321\201\320\272\320\270\320\271", nullptr));
        registButton->setText(QCoreApplication::translate("UserForm", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        loadDataButton->setText(QCoreApplication::translate("UserForm", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserForm: public Ui_UserForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERFORM_H
