/********************************************************************************
** Form generated from reading UI file 'registeradmindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERADMINDIALOG_H
#define UI_REGISTERADMINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RegisterAdminDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *userLineEdit;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *passwordLineEdit;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLineEdit *repeatPasswordLineEdit;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QLineEdit *emailLineEdit;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_5;
    QLineEdit *phoneLineEdit;
    QCheckBox *adminCheckBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *RegisterAdminDialog)
    {
        if (RegisterAdminDialog->objectName().isEmpty())
            RegisterAdminDialog->setObjectName(QString::fromUtf8("RegisterAdminDialog"));
        RegisterAdminDialog->resize(300, 354);
        RegisterAdminDialog->setMinimumSize(QSize(300, 325));
        RegisterAdminDialog->setMaximumSize(QSize(300, 354));
        gridLayout = new QGridLayout(RegisterAdminDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(RegisterAdminDialog);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        userLineEdit = new QLineEdit(RegisterAdminDialog);
        userLineEdit->setObjectName(QString::fromUtf8("userLineEdit"));

        verticalLayout->addWidget(userLineEdit);


        verticalLayout_6->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(RegisterAdminDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        passwordLineEdit = new QLineEdit(RegisterAdminDialog);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));

        verticalLayout_2->addWidget(passwordLineEdit);


        verticalLayout_6->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(RegisterAdminDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        repeatPasswordLineEdit = new QLineEdit(RegisterAdminDialog);
        repeatPasswordLineEdit->setObjectName(QString::fromUtf8("repeatPasswordLineEdit"));

        verticalLayout_3->addWidget(repeatPasswordLineEdit);


        verticalLayout_6->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_4 = new QLabel(RegisterAdminDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_4->addWidget(label_4);

        emailLineEdit = new QLineEdit(RegisterAdminDialog);
        emailLineEdit->setObjectName(QString::fromUtf8("emailLineEdit"));

        verticalLayout_4->addWidget(emailLineEdit);


        verticalLayout_6->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_5 = new QLabel(RegisterAdminDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_5->addWidget(label_5);

        phoneLineEdit = new QLineEdit(RegisterAdminDialog);
        phoneLineEdit->setObjectName(QString::fromUtf8("phoneLineEdit"));

        verticalLayout_5->addWidget(phoneLineEdit);


        verticalLayout_6->addLayout(verticalLayout_5);

        adminCheckBox = new QCheckBox(RegisterAdminDialog);
        adminCheckBox->setObjectName(QString::fromUtf8("adminCheckBox"));

        verticalLayout_6->addWidget(adminCheckBox);

        buttonBox = new QDialogButtonBox(RegisterAdminDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_6->addWidget(buttonBox);


        gridLayout->addLayout(verticalLayout_6, 0, 0, 1, 1);


        retranslateUi(RegisterAdminDialog);

        QMetaObject::connectSlotsByName(RegisterAdminDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterAdminDialog)
    {
        RegisterAdminDialog->setWindowTitle(QApplication::translate("RegisterAdminDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("RegisterAdminDialog", "User", nullptr));
        label_2->setText(QApplication::translate("RegisterAdminDialog", "Password", nullptr));
        label_3->setText(QApplication::translate("RegisterAdminDialog", "repeat Password", nullptr));
        label_4->setText(QApplication::translate("RegisterAdminDialog", "Email", nullptr));
        label_5->setText(QApplication::translate("RegisterAdminDialog", "Phone", nullptr));
        adminCheckBox->setText(QApplication::translate("RegisterAdminDialog", "Add as an administrator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserDTO: public Ui_RegisterAdminDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERADMINDIALOG_H
