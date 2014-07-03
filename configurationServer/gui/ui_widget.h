/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QListWidget *widgetListOfNames;
    QWidget *widgetSettings;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1003, 429);
        horizontalLayout_2 = new QHBoxLayout(Widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        widgetListOfNames = new QListWidget(Widget);
        widgetListOfNames->setObjectName(QStringLiteral("widgetListOfNames"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetListOfNames->sizePolicy().hasHeightForWidth());
        widgetListOfNames->setSizePolicy(sizePolicy);
        widgetListOfNames->setMinimumSize(QSize(200, 0));
        widgetListOfNames->setMaximumSize(QSize(200, 16777215));
        widgetListOfNames->setFlow(QListView::TopToBottom);
        widgetListOfNames->setViewMode(QListView::ListMode);
        widgetListOfNames->setUniformItemSizes(true);
        widgetListOfNames->setWordWrap(true);

        horizontalLayout_2->addWidget(widgetListOfNames);

        widgetSettings = new QWidget(Widget);
        widgetSettings->setObjectName(QStringLiteral("widgetSettings"));
        verticalLayout = new QVBoxLayout(widgetSettings);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        horizontalLayout_2->addWidget(widgetSettings);


        retranslateUi(Widget);

        widgetListOfNames->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
