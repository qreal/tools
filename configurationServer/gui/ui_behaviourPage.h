/********************************************************************************
** Form generated from reading UI file 'behaviourPage.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEHAVIOURPAGE_H
#define UI_BEHAVIOURPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferencesBehaviourPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QFrame *frame_2;
    QFormLayout *formLayout;
    QLabel *label_3;
    QComboBox *languageComboBox;
    QLabel *label_7;
    QFrame *frame_5;
    QGridLayout *gridLayout;
    QSpinBox *gestureDelaySpinBox;
    QLabel *autoSaveLabel;
    QLabel *gestureDelayTimeUnitLabel;
    QLabel *gestureDelayLabel;
    QCheckBox *paletteTabCheckBox;
    QSpinBox *autoSaveSpinBox;
    QCheckBox *autoSaveCheckBox;
    QCheckBox *collectErgonomicValuesCheckBox;
    QCheckBox *usabilityModeCheckBox;
    QLabel *label;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *touchModeCheckBox;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *PreferencesBehaviourPage)
    {
        if (PreferencesBehaviourPage->objectName().isEmpty())
            PreferencesBehaviourPage->setObjectName(QStringLiteral("PreferencesBehaviourPage"));
        PreferencesBehaviourPage->resize(500, 340);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PreferencesBehaviourPage->sizePolicy().hasHeightForWidth());
        PreferencesBehaviourPage->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(PreferencesBehaviourPage);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(PreferencesBehaviourPage);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        frame_2 = new QFrame(PreferencesBehaviourPage);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        formLayout = new QFormLayout(frame_2);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        languageComboBox = new QComboBox(frame_2);
        languageComboBox->setObjectName(QStringLiteral("languageComboBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, languageComboBox);


        verticalLayout->addWidget(frame_2);

        label_7 = new QLabel(PreferencesBehaviourPage);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        frame_5 = new QFrame(PreferencesBehaviourPage);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_5->sizePolicy().hasHeightForWidth());
        frame_5->setSizePolicy(sizePolicy1);
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_5);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gestureDelaySpinBox = new QSpinBox(frame_5);
        gestureDelaySpinBox->setObjectName(QStringLiteral("gestureDelaySpinBox"));
        gestureDelaySpinBox->setMaximum(100000);
        gestureDelaySpinBox->setSingleStep(10);

        gridLayout->addWidget(gestureDelaySpinBox, 2, 1, 1, 1);

        autoSaveLabel = new QLabel(frame_5);
        autoSaveLabel->setObjectName(QStringLiteral("autoSaveLabel"));

        gridLayout->addWidget(autoSaveLabel, 1, 2, 1, 1);

        gestureDelayTimeUnitLabel = new QLabel(frame_5);
        gestureDelayTimeUnitLabel->setObjectName(QStringLiteral("gestureDelayTimeUnitLabel"));

        gridLayout->addWidget(gestureDelayTimeUnitLabel, 2, 2, 1, 1);

        gestureDelayLabel = new QLabel(frame_5);
        gestureDelayLabel->setObjectName(QStringLiteral("gestureDelayLabel"));

        gridLayout->addWidget(gestureDelayLabel, 2, 0, 1, 1);

        paletteTabCheckBox = new QCheckBox(frame_5);
        paletteTabCheckBox->setObjectName(QStringLiteral("paletteTabCheckBox"));

        gridLayout->addWidget(paletteTabCheckBox, 0, 0, 1, 3);

        autoSaveSpinBox = new QSpinBox(frame_5);
        autoSaveSpinBox->setObjectName(QStringLiteral("autoSaveSpinBox"));
        autoSaveSpinBox->setMinimum(1);
        autoSaveSpinBox->setMaximum(10000);
        autoSaveSpinBox->setSingleStep(1);
        autoSaveSpinBox->setValue(600);

        gridLayout->addWidget(autoSaveSpinBox, 1, 1, 1, 1);

        autoSaveCheckBox = new QCheckBox(frame_5);
        autoSaveCheckBox->setObjectName(QStringLiteral("autoSaveCheckBox"));
        autoSaveCheckBox->setChecked(true);

        gridLayout->addWidget(autoSaveCheckBox, 1, 0, 1, 1);

        collectErgonomicValuesCheckBox = new QCheckBox(frame_5);
        collectErgonomicValuesCheckBox->setObjectName(QStringLiteral("collectErgonomicValuesCheckBox"));
        collectErgonomicValuesCheckBox->setChecked(true);

        gridLayout->addWidget(collectErgonomicValuesCheckBox, 3, 0, 1, 1);

        usabilityModeCheckBox = new QCheckBox(frame_5);
        usabilityModeCheckBox->setObjectName(QStringLiteral("usabilityModeCheckBox"));

        gridLayout->addWidget(usabilityModeCheckBox, 4, 0, 1, 1);


        verticalLayout->addWidget(frame_5);

        label = new QLabel(PreferencesBehaviourPage);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        frame = new QFrame(PreferencesBehaviourPage);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        touchModeCheckBox = new QCheckBox(frame);
        touchModeCheckBox->setObjectName(QStringLiteral("touchModeCheckBox"));

        verticalLayout_2->addWidget(touchModeCheckBox);


        verticalLayout->addWidget(frame);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(PreferencesBehaviourPage);

        QMetaObject::connectSlotsByName(PreferencesBehaviourPage);
    } // setupUi

    void retranslateUi(QWidget *PreferencesBehaviourPage)
    {
        label_2->setText(QApplication::translate("PreferencesBehaviourPage", "User Interface", 0));
        label_3->setText(QApplication::translate("PreferencesBehaviourPage", "Language", 0));
        label_7->setText(QApplication::translate("PreferencesBehaviourPage", "Automatics", 0));
        autoSaveLabel->setText(QApplication::translate("PreferencesBehaviourPage", "sec", 0));
        gestureDelayTimeUnitLabel->setText(QApplication::translate("PreferencesBehaviourPage", "msec", 0));
        gestureDelayLabel->setText(QApplication::translate("PreferencesBehaviourPage", "Delay after gesture", 0));
        paletteTabCheckBox->setText(QApplication::translate("PreferencesBehaviourPage", "Palette tab switching", 0));
        autoSaveCheckBox->setText(QApplication::translate("PreferencesBehaviourPage", "Autosave", 0));
        collectErgonomicValuesCheckBox->setText(QApplication::translate("PreferencesBehaviourPage", "Collect ergonomic values", 0));
        usabilityModeCheckBox->setText(QApplication::translate("PreferencesBehaviourPage", "Usability testing mode", 0));
        label->setText(QApplication::translate("PreferencesBehaviourPage", "Touch", 0));
        touchModeCheckBox->setText(QApplication::translate("PreferencesBehaviourPage", "Touch Mode", 0));
        Q_UNUSED(PreferencesBehaviourPage);
    } // retranslateUi

};

namespace Ui {
    class PreferencesBehaviourPage: public Ui_PreferencesBehaviourPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEHAVIOURPAGE_H
