/********************************************************************************
** Form generated from reading UI file 'preferencesDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCESDIALOG_H
#define UI_PREFERENCESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferencesDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QPushButton *applyButton;
    QListWidget *listWidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QStackedWidget *pageContentWigdet;
    QWidget *pageContentWigdetPage1;
    QPushButton *exportButton;
    QPushButton *importButton;
    QPushButton *saveButton;

    void setupUi(QDialog *PreferencesDialog)
    {
        if (PreferencesDialog->objectName().isEmpty())
            PreferencesDialog->setObjectName(QStringLiteral("PreferencesDialog"));
        PreferencesDialog->resize(892, 593);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PreferencesDialog->sizePolicy().hasHeightForWidth());
        PreferencesDialog->setSizePolicy(sizePolicy);
        PreferencesDialog->setMinimumSize(QSize(0, 0));
        PreferencesDialog->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/qreal.png"), QSize(), QIcon::Normal, QIcon::Off);
        PreferencesDialog->setWindowIcon(icon);
        gridLayout = new QGridLayout(PreferencesDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        okButton = new QPushButton(PreferencesDialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        gridLayout->addWidget(okButton, 4, 1, 1, 1);

        cancelButton = new QPushButton(PreferencesDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        gridLayout->addWidget(cancelButton, 4, 2, 1, 1);

        applyButton = new QPushButton(PreferencesDialog);
        applyButton->setObjectName(QStringLiteral("applyButton"));

        gridLayout->addWidget(applyButton, 4, 3, 1, 1);

        saveButton = new QPushButton(PreferencesDialog);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        gridLayout->addWidget(saveButton, 3, 1, 1, 1);

        listWidget = new QListWidget(PreferencesDialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy1);
        listWidget->setMaximumSize(QSize(500, 16777215));
        listWidget->setFlow(QListView::TopToBottom);
        listWidget->setViewMode(QListView::ListMode);
        listWidget->setUniformItemSizes(true);
        listWidget->setWordWrap(true);

        gridLayout->addWidget(listWidget, 1, 0, 2, 1);

        scrollArea = new QScrollArea(PreferencesDialog);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setMinimumSize(QSize(0, 0));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 610, 509));
        sizePolicy1.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pageContentWigdet = new QStackedWidget(scrollAreaWidgetContents);
        pageContentWigdet->setObjectName(QStringLiteral("pageContentWigdet"));
        sizePolicy1.setHeightForWidth(pageContentWigdet->sizePolicy().hasHeightForWidth());
        pageContentWigdet->setSizePolicy(sizePolicy1);
        pageContentWigdetPage1 = new QWidget();
        pageContentWigdetPage1->setObjectName(QStringLiteral("pageContentWigdetPage1"));
        pageContentWigdet->addWidget(pageContentWigdetPage1);

        verticalLayout->addWidget(pageContentWigdet);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 2, 1, 1, 3);

        exportButton = new QPushButton(PreferencesDialog);
        exportButton->setObjectName(QStringLiteral("exportButton"));

        gridLayout->addWidget(exportButton, 3, 3, 1, 1);

        importButton = new QPushButton(PreferencesDialog);
        importButton->setObjectName(QStringLiteral("importButton"));

        gridLayout->addWidget(importButton, 3, 2, 1, 1);


        retranslateUi(PreferencesDialog);

        listWidget->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(PreferencesDialog);
    } // setupUi

    void retranslateUi(QDialog *PreferencesDialog)
    {
        PreferencesDialog->setWindowTitle(QApplication::translate("PreferencesDialog", "Preferences", 0));
        okButton->setText(QApplication::translate("PreferencesDialog", "OK", 0));
        cancelButton->setText(QApplication::translate("PreferencesDialog", "Cancel", 0));
        applyButton->setText(QApplication::translate("PreferencesDialog", "Apply", 0));
        exportButton->setText(QApplication::translate("PreferencesDialog", "Export", 0));
        importButton->setText(QApplication::translate("PreferencesDialog", "Import", 0));
        saveButton->setText(QApplication::translate("PreferenceDialog", "Save", 0));
    } // retranslateUi

};

namespace Ui {
    class PreferencesDialog: public Ui_PreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESDIALOG_H
