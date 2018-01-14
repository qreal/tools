/********************************************************************************
** Form generated from reading UI file 'debuggerPage.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUGGERPAGE_H
#define UI_DEBUGGERPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferencesDebuggerPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_16;
    QFrame *frame_7;
    QGridLayout *gridLayout;
    QLabel *label_14;
    QLineEdit *timeoutLineEdit;
    QLabel *label_15;
    QComboBox *colorComboBox;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *PreferencesDebuggerPage)
    {
        if (PreferencesDebuggerPage->objectName().isEmpty())
            PreferencesDebuggerPage->setObjectName(QStringLiteral("PreferencesDebuggerPage"));
        PreferencesDebuggerPage->resize(407, 122);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PreferencesDebuggerPage->sizePolicy().hasHeightForWidth());
        PreferencesDebuggerPage->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(PreferencesDebuggerPage);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_16 = new QLabel(PreferencesDebuggerPage);
        label_16->setObjectName(QStringLiteral("label_16"));

        verticalLayout->addWidget(label_16);

        frame_7 = new QFrame(PreferencesDebuggerPage);
        frame_7->setObjectName(QStringLiteral("frame_7"));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_7);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_14 = new QLabel(frame_7);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout->addWidget(label_14, 0, 0, 1, 1);

        timeoutLineEdit = new QLineEdit(frame_7);
        timeoutLineEdit->setObjectName(QStringLiteral("timeoutLineEdit"));

        gridLayout->addWidget(timeoutLineEdit, 0, 1, 1, 1);

        label_15 = new QLabel(frame_7);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout->addWidget(label_15, 1, 0, 1, 1);

        colorComboBox = new QComboBox(frame_7);
        colorComboBox->setObjectName(QStringLiteral("colorComboBox"));

        gridLayout->addWidget(colorComboBox, 1, 1, 1, 1);


        verticalLayout->addWidget(frame_7);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(PreferencesDebuggerPage);

        QMetaObject::connectSlotsByName(PreferencesDebuggerPage);
    } // setupUi

    void retranslateUi(QWidget *PreferencesDebuggerPage)
    {
        label_16->setText(QApplication::translate("PreferencesDebuggerPage", "Presentation", 0));
        label_14->setText(QApplication::translate("PreferencesDebuggerPage", "Debug timeout (ms):", 0));
        label_15->setText(QApplication::translate("PreferencesDebuggerPage", "Color of highlighting:", 0));
        Q_UNUSED(PreferencesDebuggerPage);
    } // retranslateUi

};

namespace Ui {
    class PreferencesDebuggerPage: public Ui_PreferencesDebuggerPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGGERPAGE_H
