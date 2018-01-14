/********************************************************************************
** Form generated from reading UI file 'miscellaniousPage.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MISCELLANIOUSPAGE_H
#define UI_MISCELLANIOUSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferencesMiscellaniousPage
{
public:
    QGridLayout *gridLayout_4;
    QLabel *label_5;
    QFrame *frame_3;
    QGridLayout *gridLayout;
    QCheckBox *antialiasingCheckBox;
    QLabel *label_6;
    QFrame *frame_4;
    QGridLayout *gridLayout_2;
    QCheckBox *splashScreenCheckBox;
    QLabel *label_8;
    QComboBox *colorComboBox;
    QCheckBox *paintOldLineCheckBox;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QSpinBox *recentProjectsLimitSpinBox;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_7;
    QFrame *frame_5;
    QGridLayout *gridLayout_3;
    QPushButton *imagesPathBrowseButton;
    QLineEdit *imagesPathEdit;
    QLabel *label;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSlider *toolbarSizeSlider;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *PreferencesMiscellaniousPage)
    {
        if (PreferencesMiscellaniousPage->objectName().isEmpty())
            PreferencesMiscellaniousPage->setObjectName(QStringLiteral("PreferencesMiscellaniousPage"));
        PreferencesMiscellaniousPage->resize(561, 325);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PreferencesMiscellaniousPage->sizePolicy().hasHeightForWidth());
        PreferencesMiscellaniousPage->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(PreferencesMiscellaniousPage);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_5 = new QLabel(PreferencesMiscellaniousPage);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_4->addWidget(label_5, 0, 0, 1, 1);

        frame_3 = new QFrame(PreferencesMiscellaniousPage);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_3);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        antialiasingCheckBox = new QCheckBox(frame_3);
        antialiasingCheckBox->setObjectName(QStringLiteral("antialiasingCheckBox"));

        gridLayout->addWidget(antialiasingCheckBox, 0, 0, 1, 1);


        gridLayout_4->addWidget(frame_3, 1, 0, 1, 1);

        label_6 = new QLabel(PreferencesMiscellaniousPage);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_4->addWidget(label_6, 2, 0, 1, 1);

        frame_4 = new QFrame(PreferencesMiscellaniousPage);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_4);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        splashScreenCheckBox = new QCheckBox(frame_4);
        splashScreenCheckBox->setObjectName(QStringLiteral("splashScreenCheckBox"));

        gridLayout_2->addWidget(splashScreenCheckBox, 0, 0, 1, 1);

        label_8 = new QLabel(frame_4);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 3, 2, 1, 1);

        colorComboBox = new QComboBox(frame_4);
        colorComboBox->setObjectName(QStringLiteral("colorComboBox"));
        colorComboBox->setMinimumSize(QSize(170, 0));
        colorComboBox->setFrame(true);

        gridLayout_2->addWidget(colorComboBox, 3, 3, 1, 1);

        paintOldLineCheckBox = new QCheckBox(frame_4);
        paintOldLineCheckBox->setObjectName(QStringLiteral("paintOldLineCheckBox"));
        paintOldLineCheckBox->setEnabled(true);

        gridLayout_2->addWidget(paintOldLineCheckBox, 3, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 3, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(5);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_4->setContentsMargins(-1, 0, 0, -1);
        label_9 = new QLabel(frame_4);
        label_9->setObjectName(QStringLiteral("label_9"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);
        label_9->setWordWrap(true);

        horizontalLayout_4->addWidget(label_9);

        recentProjectsLimitSpinBox = new QSpinBox(frame_4);
        recentProjectsLimitSpinBox->setObjectName(QStringLiteral("recentProjectsLimitSpinBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(recentProjectsLimitSpinBox->sizePolicy().hasHeightForWidth());
        recentProjectsLimitSpinBox->setSizePolicy(sizePolicy2);
        recentProjectsLimitSpinBox->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_4->addWidget(recentProjectsLimitSpinBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout_4, 0, 2, 1, 2);


        gridLayout_4->addWidget(frame_4, 3, 0, 1, 1);

        label_7 = new QLabel(PreferencesMiscellaniousPage);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_4->addWidget(label_7, 4, 0, 1, 1);

        frame_5 = new QFrame(PreferencesMiscellaniousPage);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_5);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        imagesPathBrowseButton = new QPushButton(frame_5);
        imagesPathBrowseButton->setObjectName(QStringLiteral("imagesPathBrowseButton"));

        gridLayout_3->addWidget(imagesPathBrowseButton, 0, 1, 1, 1);

        imagesPathEdit = new QLineEdit(frame_5);
        imagesPathEdit->setObjectName(QStringLiteral("imagesPathEdit"));

        gridLayout_3->addWidget(imagesPathEdit, 0, 0, 1, 1);


        gridLayout_4->addWidget(frame_5, 5, 0, 1, 1);

        label = new QLabel(PreferencesMiscellaniousPage);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_4->addWidget(label, 6, 0, 1, 1);

        frame = new QFrame(PreferencesMiscellaniousPage);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        toolbarSizeSlider = new QSlider(frame);
        toolbarSizeSlider->setObjectName(QStringLiteral("toolbarSizeSlider"));
        toolbarSizeSlider->setMinimum(20);
        toolbarSizeSlider->setMaximum(50);
        toolbarSizeSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(toolbarSizeSlider);


        gridLayout_4->addWidget(frame, 7, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 8, 0, 1, 1);


        retranslateUi(PreferencesMiscellaniousPage);

        QMetaObject::connectSlotsByName(PreferencesMiscellaniousPage);
    } // setupUi

    void retranslateUi(QWidget *PreferencesMiscellaniousPage)
    {
        label_5->setText(QApplication::translate("PreferencesMiscellaniousPage", "Graphics", 0));
        antialiasingCheckBox->setText(QApplication::translate("PreferencesMiscellaniousPage", "Antialiasing", 0));
        label_6->setText(QApplication::translate("PreferencesMiscellaniousPage", "Other", 0));
        splashScreenCheckBox->setText(QApplication::translate("PreferencesMiscellaniousPage", "Show splashscreen", 0));
        label_8->setText(QApplication::translate("PreferencesMiscellaniousPage", "Color of old line:", 0));
        paintOldLineCheckBox->setText(QApplication::translate("PreferencesMiscellaniousPage", "Paint the old line", 0));
        label_9->setText(QApplication::translate("PreferencesMiscellaniousPage", "Limit recent projects list", 0));
        label_7->setText(QApplication::translate("PreferencesMiscellaniousPage", "Images", 0));
        imagesPathBrowseButton->setText(QApplication::translate("PreferencesMiscellaniousPage", "Browse", 0));
        label->setText(QApplication::translate("PreferencesMiscellaniousPage", "Toolbars", 0));
        label_2->setText(QApplication::translate("PreferencesMiscellaniousPage", "Size", 0));
        Q_UNUSED(PreferencesMiscellaniousPage);
    } // retranslateUi

};

namespace Ui {
    class PreferencesMiscellaniousPage: public Ui_PreferencesMiscellaniousPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MISCELLANIOUSPAGE_H
