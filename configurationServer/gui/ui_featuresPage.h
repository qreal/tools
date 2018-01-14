/********************************************************************************
** Form generated from reading UI file 'featuresPage.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FEATURESPAGE_H
#define UI_FEATURESPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferencesFeaturesPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_1;
    QFrame *frame_1;
    QGridLayout *gridLayout;
    QCheckBox *gesturesCheckBox;
    QLabel *label;
    QLabel *label_2;
    QCheckBox *embeddedLinkersCheckBox;
    QLabel *label_3;
    QCheckBox *embeddedControlsCheckBox;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *PreferencesFeaturesPage)
    {
        if (PreferencesFeaturesPage->objectName().isEmpty())
            PreferencesFeaturesPage->setObjectName(QStringLiteral("PreferencesFeaturesPage"));
        PreferencesFeaturesPage->resize(500, 300);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PreferencesFeaturesPage->sizePolicy().hasHeightForWidth());
        PreferencesFeaturesPage->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(PreferencesFeaturesPage);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_1 = new QLabel(PreferencesFeaturesPage);
        label_1->setObjectName(QStringLiteral("label_1"));

        verticalLayout->addWidget(label_1);

        frame_1 = new QFrame(PreferencesFeaturesPage);
        frame_1->setObjectName(QStringLiteral("frame_1"));
        frame_1->setFrameShape(QFrame::StyledPanel);
        frame_1->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_1);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gesturesCheckBox = new QCheckBox(frame_1);
        gesturesCheckBox->setObjectName(QStringLiteral("gesturesCheckBox"));

        gridLayout->addWidget(gesturesCheckBox, 0, 0, 1, 1);

        label = new QLabel(frame_1);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        label_2 = new QLabel(frame_1);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        embeddedLinkersCheckBox = new QCheckBox(frame_1);
        embeddedLinkersCheckBox->setObjectName(QStringLiteral("embeddedLinkersCheckBox"));

        gridLayout->addWidget(embeddedLinkersCheckBox, 1, 0, 1, 1);

        label_3 = new QLabel(frame_1);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 1, 1, 1);

        embeddedControlsCheckBox = new QCheckBox(frame_1);
        embeddedControlsCheckBox->setObjectName(QStringLiteral("embeddedControlsCheckBox"));

        gridLayout->addWidget(embeddedControlsCheckBox, 2, 0, 1, 1);


        verticalLayout->addWidget(frame_1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(PreferencesFeaturesPage);

        QMetaObject::connectSlotsByName(PreferencesFeaturesPage);
    } // setupUi

    void retranslateUi(QWidget *PreferencesFeaturesPage)
    {
        label_1->setText(QApplication::translate("PreferencesFeaturesPage", "Element controls", 0));
        gesturesCheckBox->setText(QApplication::translate("PreferencesFeaturesPage", "Gestures", 0));
        label->setText(QApplication::translate("PreferencesFeaturesPage", "fast linking with mouse", 0));
        label_2->setText(QApplication::translate("PreferencesFeaturesPage", "fast linking with mouse", 0));
        embeddedLinkersCheckBox->setText(QApplication::translate("PreferencesFeaturesPage", "Embedded Linkers", 0));
        label_3->setText(QApplication::translate("PreferencesFeaturesPage", "fast property editing", 0));
        embeddedControlsCheckBox->setText(QApplication::translate("PreferencesFeaturesPage", "Embedded Controls", 0));
        Q_UNUSED(PreferencesFeaturesPage);
    } // retranslateUi

};

namespace Ui {
    class PreferencesFeaturesPage: public Ui_PreferencesFeaturesPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FEATURESPAGE_H
