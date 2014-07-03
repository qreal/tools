/********************************************************************************
** Form generated from reading UI file 'hotKeyManagerPage.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOTKEYMANAGERPAGE_H
#define UI_HOTKEYMANAGERPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "hotKeyManager/shortcutEdit.h"

QT_BEGIN_NAMESPACE

class Ui_hotKeyManagerPage
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *keyboardShortcutsGroupBox;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *importPushButton;
    QPushButton *exportPushButton;
    QTableWidget *hotKeysTable;
    QPushButton *resetAllPushButton;
    QGroupBox *shortcutGroupBox;
    QGridLayout *gridLayout_2;
    QPushButton *resetShortcutPushButton;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    ShortcutEdit *shortcutLineEdit;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *hotKeyManagerPage)
    {
        if (hotKeyManagerPage->objectName().isEmpty())
            hotKeyManagerPage->setObjectName(QStringLiteral("hotKeyManagerPage"));
        hotKeyManagerPage->resize(654, 350);
        verticalLayout_2 = new QVBoxLayout(hotKeyManagerPage);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        keyboardShortcutsGroupBox = new QGroupBox(hotKeyManagerPage);
        keyboardShortcutsGroupBox->setObjectName(QStringLiteral("keyboardShortcutsGroupBox"));
        gridLayout = new QGridLayout(keyboardShortcutsGroupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(381, 38, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 1, 1, 1);

        importPushButton = new QPushButton(keyboardShortcutsGroupBox);
        importPushButton->setObjectName(QStringLiteral("importPushButton"));

        gridLayout->addWidget(importPushButton, 1, 2, 1, 1);

        exportPushButton = new QPushButton(keyboardShortcutsGroupBox);
        exportPushButton->setObjectName(QStringLiteral("exportPushButton"));

        gridLayout->addWidget(exportPushButton, 1, 3, 1, 1);

        hotKeysTable = new QTableWidget(keyboardShortcutsGroupBox);
        if (hotKeysTable->columnCount() < 5)
            hotKeysTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        hotKeysTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        hotKeysTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        hotKeysTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        hotKeysTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        hotKeysTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        hotKeysTable->setObjectName(QStringLiteral("hotKeysTable"));
        hotKeysTable->setEnabled(true);
        hotKeysTable->setMinimumSize(QSize(0, 0));
        hotKeysTable->setFocusPolicy(Qt::WheelFocus);
        hotKeysTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        hotKeysTable->setProperty("showDropIndicator", QVariant(false));
        hotKeysTable->setSelectionMode(QAbstractItemView::SingleSelection);
        hotKeysTable->setSelectionBehavior(QAbstractItemView::SelectItems);
        hotKeysTable->setShowGrid(false);
        hotKeysTable->setWordWrap(true);
        hotKeysTable->setCornerButtonEnabled(true);
        hotKeysTable->setRowCount(0);
        hotKeysTable->setColumnCount(5);
        hotKeysTable->horizontalHeader()->setDefaultSectionSize(100);
        hotKeysTable->horizontalHeader()->setHighlightSections(true);
        hotKeysTable->verticalHeader()->setCascadingSectionResizes(false);
        hotKeysTable->verticalHeader()->setMinimumSectionSize(19);
        hotKeysTable->verticalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(hotKeysTable, 0, 0, 1, 4);

        resetAllPushButton = new QPushButton(keyboardShortcutsGroupBox);
        resetAllPushButton->setObjectName(QStringLiteral("resetAllPushButton"));

        gridLayout->addWidget(resetAllPushButton, 1, 0, 1, 1);


        verticalLayout_2->addWidget(keyboardShortcutsGroupBox);

        shortcutGroupBox = new QGroupBox(hotKeyManagerPage);
        shortcutGroupBox->setObjectName(QStringLiteral("shortcutGroupBox"));
        gridLayout_2 = new QGridLayout(shortcutGroupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        resetShortcutPushButton = new QPushButton(shortcutGroupBox);
        resetShortcutPushButton->setObjectName(QStringLiteral("resetShortcutPushButton"));

        gridLayout_2->addWidget(resetShortcutPushButton, 0, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        label = new QLabel(shortcutGroupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 1, 1, 1);

        shortcutLineEdit = new ShortcutEdit(shortcutGroupBox);
        shortcutLineEdit->setObjectName(QStringLiteral("shortcutLineEdit"));
        shortcutLineEdit->setEnabled(false);
        shortcutLineEdit->setDragEnabled(false);
        shortcutLineEdit->setReadOnly(false);

        gridLayout_2->addWidget(shortcutLineEdit, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(2, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 0, 1, 1);


        verticalLayout_2->addWidget(shortcutGroupBox);


        retranslateUi(hotKeyManagerPage);

        QMetaObject::connectSlotsByName(hotKeyManagerPage);
    } // setupUi

    void retranslateUi(QWidget *hotKeyManagerPage)
    {
        hotKeyManagerPage->setWindowTitle(QApplication::translate("hotKeyManagerPage", "Form", 0));
        keyboardShortcutsGroupBox->setTitle(QApplication::translate("hotKeyManagerPage", "Keyboard Shortcuts", 0));
        importPushButton->setText(QApplication::translate("hotKeyManagerPage", "Import...", 0));
        exportPushButton->setText(QApplication::translate("hotKeyManagerPage", "Export...", 0));
        QTableWidgetItem *___qtablewidgetitem = hotKeysTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("hotKeyManagerPage", "Command", 0));
        QTableWidgetItem *___qtablewidgetitem1 = hotKeysTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("hotKeyManagerPage", "Label", 0));
        QTableWidgetItem *___qtablewidgetitem2 = hotKeysTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("hotKeyManagerPage", "Shortcut 1", 0));
        QTableWidgetItem *___qtablewidgetitem3 = hotKeysTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("hotKeyManagerPage", "Shortcut 2", 0));
        QTableWidgetItem *___qtablewidgetitem4 = hotKeysTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("hotKeyManagerPage", "Shortcut 3", 0));
        resetAllPushButton->setText(QApplication::translate("hotKeyManagerPage", "Reset All", 0));
        shortcutGroupBox->setTitle(QApplication::translate("hotKeyManagerPage", "Shortcut", 0));
        resetShortcutPushButton->setText(QApplication::translate("hotKeyManagerPage", "Reset", 0));
        label->setText(QApplication::translate("hotKeyManagerPage", "Key sequence", 0));
    } // retranslateUi

};

namespace Ui {
    class hotKeyManagerPage: public Ui_hotKeyManagerPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOTKEYMANAGERPAGE_H
